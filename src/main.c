#include "uls.h"

static t_args *mx_sort_args(int argc, char **argv);
static char **sort_data(int size, char **data);
static t_dirs *mx_get_dir_entry(t_args *args, int amount);
static void add_dirs_entry(t_dirs_entry *dirs_entry, struct dirent *entry, int *count);
static t_dirs_entry *mx_pushing_data(struct dirent *entry, int *count);

int main(int argc, char **argv) {
	t_args *args = mx_sort_args(argc, argv);
	t_dirs *dirs_entry = mx_get_dir_entry(args, mx_arr_size(args->dirs));
	char symbol = '.';
	char **data;

	if (args->flags) {
		for (int i = 0; args->flags[i]; i++) {
			if (args->flags[i] == 'a')
				symbol = '\0';
		}
	}
	data = mx_sort_data(dirs_entry, symbol);
	if (dirs_entry->next) {
		dirs_entry = dirs_entry->next;
		data = mx_sort_data(dirs_entry, symbol);
		if (mx_arr_size(args->not_valid) + mx_arr_size(args->dirs) - 1 > 1) {
			while (dirs_entry) {
				data = mx_sort_data(dirs_entry, symbol);
				mx_printstr(dirs_entry->dir);
				mx_printchar('\n');
				mx_print_ls_multy_colomn(data);
				dirs_entry = dirs_entry->next;
				if (dirs_entry)
					mx_printchar('\n');
				}
		}
		else
			mx_print_ls_multy_colomn(data);
	}
	else if (args->not_valid[0] == NULL)
		mx_print_ls_multy_colomn(data);
}

static t_args *mx_sort_args(int argc, char **argv) {
	t_args *args = (t_args *)malloc(sizeof(t_args));
	int index = 1;

	args->flags = mx_get_flags(&index, argc, argv);
	mx_args_to_struct(index, argc, argv, args);
	args->files = sort_data(mx_arr_size(args->files), args->files);
	args->dirs = sort_data(mx_arr_size(args->dirs), args->dirs);
	args->not_valid = sort_data(mx_arr_size(args->not_valid), args->not_valid);
	mx_print_not_valid(mx_arr_size(args->not_valid), args->not_valid);
	if (args->files[0] != NULL) {
		mx_print_ls_multy_colomn(args->files);
		mx_printchar('\n');
	}
	return args;
}

static t_dirs *mx_get_dir_entry(t_args *args, int amount) {
	if (args && amount > 0) {
		t_dirs *dirs_entry = (t_dirs *)malloc(sizeof(t_dirs) * amount);

		for(int i = 0; i < amount; i++) {
			DIR *dir = opendir(args->dirs[i]);
			struct dirent *entry = NULL;
			int count = 0;

			dirs_entry[i].dir = args->dirs[i];
			dirs_entry[i].entry_dir = mx_pushing_data(readdir(dir), &count);
			while ((entry = readdir(dir)) != NULL)
				add_dirs_entry(dirs_entry[i].entry_dir, entry, &count);
			dirs_entry[i].amount_d_data = count;
			if (i != amount - 1)
				dirs_entry[i].next = &dirs_entry[i + 1];
			else
				dirs_entry[i].next = NULL;
		}
		return dirs_entry;
	}
	return NULL;
}

static void add_dirs_entry(t_dirs_entry *dirs_entry, struct dirent *entry, int *count) {
	t_dirs_entry *current = dirs_entry;

	while (current->next != NULL)
		current = current->next;
	current->next = mx_pushing_data(entry, count);
}

static t_dirs_entry *mx_pushing_data(struct dirent *entry, int *count) {
	t_dirs_entry *temp = malloc(sizeof(t_dirs_entry));

	*count = *count + 1;
	temp->d_name = mx_strdup(entry->d_name);
	temp->d_namlen = (int)entry->d_namlen;
	temp->d_type = (int)entry->d_type;
	temp->next = NULL;
	return temp;
}

static char **sort_data(int size, char **data) {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size - i - 1; j++) {
			if (mx_strcmp(data[j], data[j + 1]) > 0) {
				char *temp = mx_strdup(data[j + 1]);

				free(data[j + 1]);
				data[j + 1] = mx_strdup(data[j]);
				free(data[j]);
				data[j] = temp;
			}
		}
	}
	return data;
}
