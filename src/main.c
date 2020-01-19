#include "uls.h"

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
			struct dirent *entry;

			dirs_entry[i].dir = args->dirs[i];
			while ((entry = readdir(dir)) != NULL);
			dirs_entry[i].entry_dir = entry;
			if (i != amount - 1)
				dirs_entry[i].next = &dirs_entry[i + 1];
			else
				dirs_entry[i].next = NULL;
		}
		return dirs_entry;
	}
	return NULL;
}

int main(int argc, char **argv) {
	t_args *args = mx_sort_args(argc, argv);
	mx_arr_size(args->dirs);
	exit(1);
	t_dirs *dirs_entry = mx_get_dir_entry(args, mx_arr_size(args->dirs));

	// st_general *gnr = (st_general*)malloc(sizeof(st_general));

	while (dirs_entry) {
		exit(-1);
		dirs_entry = dirs_entry->next;
	}
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
