#include "uls.h"

static t_args *mx_sort_args(int argc, char **argv);
static char **sort_data(int size, char **data);
static t_dirs *mx_get_dir_entry(t_args *args, int amount);
static t_dirs_entry *add_dirs_entry(t_dirs_entry *dirs_entry, struct dirent *entry, int *count);
static t_dirs_entry *mx_pushing_data(struct dirent *entry, int *count);
static t_dirs *piwpiw(t_dirs *dirs, char *dir_name);
static t_dirs *mx_pushing_data_to_dir(char *dir_name);

int main(int argc, char **argv) {
	t_args *args = mx_sort_args(argc, argv);
	t_dirs *dirs = mx_get_dir_entry(args, mx_arr_size(args->dirs));
	char symbol = '.';
	if (args->flags) {
		for (int i = 0; args->flags[i]; i++) {
			if (args->flags[i] == 'a')
				symbol = '\0';
		}
	}
	if (args->dirs[0]) {
		if (isatty(1)) {
			if (args->files[0] != NULL) {
				mx_print_ls_multy_colomn(args->files);
				mx_printchar('\n');
			}
			mx_print(args, dirs, symbol, mx_print_ls_multy_colomn);
		} else {
			if (args->files[0] != NULL) {
				mx_print_ls_monocolomn(args->files);
				mx_printchar('\n');
			}
			mx_print(args, dirs, symbol, mx_print_ls_monocolomn);
		}
	}
	mx_del_dirs_struct(dirs);
	mx_del_args_struct(args, NOT_VALID);
	// system("leaks -q uls");
}

static t_args *mx_sort_args(int argc, char **argv) {
	t_args *args = (t_args *)malloc(sizeof(t_args));
	int index = 1;

	args->flags = mx_get_flags(args, &index, argc, argv);
	mx_args_to_struct(index, argc, argv, args);
	args->files = sort_data(mx_arr_size(args->files), args->files);
	args->dirs = sort_data(mx_arr_size(args->dirs), args->dirs);
	args->not_valid = sort_data(mx_arr_size(args->not_valid), args->not_valid);
	mx_print_not_valid(mx_arr_size(args->not_valid), args->not_valid);

	return args;
}

static t_dirs *mx_get_dir_entry(t_args *args, int amount) {
	t_dirs *dirs = NULL;

	for(int i = 0; i < amount; i++) {
		dirs = piwpiw(dirs, args->dirs[i]);
	}

	return dirs;
}

static t_dirs_entry *add_dirs_entry(t_dirs_entry *dirs_entry, struct dirent *entry, int *count) {
	t_dirs_entry *current = dirs_entry;

	if (!dirs_entry)
		return mx_pushing_data(entry, count);
	while (current->next != NULL)
		current = current->next;
	current->next = mx_pushing_data(entry, count);
	return dirs_entry;
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

static t_dirs *piwpiw(t_dirs *dirs, char *dir_name) {
	t_dirs *temp = dirs;

	if (!dirs)
		return mx_pushing_data_to_dir(dir_name);
	while (temp->next != NULL) {
		temp = temp->next;
	}
	temp->next = mx_pushing_data_to_dir(dir_name);
	return dirs;
}

static t_dirs *mx_pushing_data_to_dir(char *dir_name) {
	t_dirs *temp = malloc(sizeof(t_dirs));
	DIR *dir = opendir(dir_name);
	struct dirent *entry = NULL;
	int count = 0;

	temp->entry_dir = NULL;
	while ((entry = readdir(dir)) != NULL)
		temp->entry_dir = add_dirs_entry(temp->entry_dir, entry, &count);
	closedir(dir);
	temp->dir = mx_strdup(dir_name);
	temp->amount_d_data = count;
	temp->next = NULL;
	return temp;
}
