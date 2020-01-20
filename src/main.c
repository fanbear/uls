#include "uls.h"

static t_args *mx_sort_args(int argc, char **argv);
static t_dirs *mx_get_dir_entry(t_args *args, int amount);
static void add_dirs_entry(t_dirs_entry *dirs_entry, struct dirent *entry);
static t_dirs_entry *mx_pushing_data(struct dirent *entry);

int main(int argc, char **argv) {
	t_args *args = mx_sort_args(argc, argv);
	t_dirs *dirs_entry = NULL;

	if (args && args->dirs)
		 dirs_entry = mx_get_dir_entry(args, mx_arr_size(args->dirs));

	// t_dirs **temp = &dirs_entry;
	// for (int i = 0; temp[i]; i++) {
	//
	// 	printf("%s :\n", temp[i]->dir);
	// 	temp[i]
		// t_dirs_entry **temp_entry = &temp[i]->entry_dir;
		// for (int j = 0; temp_entry[j]; j++) {
		// 	printf("\t%d\t%s\n", temp_entry[j]->d_type, temp_entry[j]->d_name);
			// printf("\t%d\t%s\n", dirs_entry->entry_dir->d_type, dirs_entry->entry_dir->d_name);
		// }
	// }

	// exit(1);
	// t_dirs *temp = NULL;
	// while (dirs_entry) {
	// 	temp = dirs_entry->next
	// 	mx_strdel(&dirs_entry->dir);

		t_dirs_entry *temp_entry = NULL;

		while (dirs_entry->entry_dir) {
			temp_entry = dirs_entry->entry_dir->next;
			mx_strdel(&dirs_entry->entry_dir->d_name);
			if (dirs_entry->entry_dir->next) {
				free(dirs_entry->entry_dir->next);
				dirs_entry->entry_dir->next = NULL;
			}
			dirs_entry->entry_dir = temp_entry;
		}
	// }

	// system("leaks -q uls");
	// st_general *gnr = (st_general*)malloc(sizeof(st_general));
	// if (isatty(1)) {
	//
	// }
	//
	// if (isatty(1)) {
	// 	if (argc == 1)
	// 		mx_uls_only(gnr);
	// 	if (argc > 1) {
	// 		gnr->d_str = mx_uls_no_flag(argc, argv);
	// 		mx_print_directory(gnr);
	// 	}
	// }
	// else {
	// 	printf("asd\n");
	// }
}

static t_args *mx_sort_args(int argc, char **argv) {
	t_args *args = NULL;
	int index = 1;

	if (argc > 1) {
		args = (t_args *)malloc(sizeof(t_args));
		args->flags = mx_get_flags(&index, argc, argv);
		mx_args_to_struct(index, argc, argv, args);
		mx_print_not_valid(mx_arr_size(args->not_valid), args->not_valid);
	}
	return args;
}

static t_dirs *mx_get_dir_entry(t_args *args, int amount) {
	if (args && amount > 0) {
		t_dirs *dirs_entry = (t_dirs *)malloc(sizeof(t_dirs) * amount);

		for(int i = 0; i < amount; i++) {
			DIR *dir = opendir(args->dirs[i]);
			struct dirent *entry = NULL;

			dirs_entry[i].dir = args->dirs[i];
			dirs_entry[i].entry_dir = mx_pushing_data(readdir(dir));
			while ((entry = readdir(dir)) != NULL)
				add_dirs_entry(dirs_entry[i].entry_dir, entry);
			if (i != amount - 1)
				dirs_entry[i].next = &dirs_entry[i + 1];
			else
				dirs_entry[i].next = NULL;
		}
		return dirs_entry;
	}
	return NULL;
}

static void add_dirs_entry(t_dirs_entry *dirs_entry, struct dirent *entry) {
	t_dirs_entry *current = dirs_entry;

	while (current->next != NULL)
		current = current->next;
	current->next = mx_pushing_data(entry);
}

static t_dirs_entry *mx_pushing_data(struct dirent *entry) {
	t_dirs_entry *temp = malloc(sizeof(t_dirs_entry));

	temp->d_name = mx_strdup(entry->d_name);
	temp->d_type = (int)entry->d_type;
	temp->next = NULL;
	return temp;
}
