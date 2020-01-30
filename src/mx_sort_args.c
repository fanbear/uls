#include "uls.h"

static char **sort_data(int size, char **data, int index);

t_args *mx_sort_args(int argc, char **argv) {
	t_args *args = (t_args *)malloc(sizeof(t_args));
	int index = 1;

	args->flags = mx_get_flags(args, &index, argc, argv);
	mx_args_to_struct(index, argc, argv, args);
	args->files = sort_data(mx_arr_size(args->files), args->files, 0);
	args->dirs = sort_data(mx_arr_size(args->dirs), args->dirs, 1);
	args->not_valid = sort_data(mx_arr_size(args->not_valid), args->not_valid, 2);
	return args;
}

static char **sort_data(int size, char **data, int index) {
	for (int i = 0; i < size; i++) {
		for (int j = i + 1; j < size; j++) {
			if (mx_strcmp(data[i], data[j]) > 0) {
				char *temp = mx_strdup(data[i]);

				free(data[i]);
				data[i] = mx_strdup(data[j]);
				free(data[j]);
				data[j] = temp;
			}
		}
		if (index == 2)
			mx_print_not_valid(data[i]);
	}
	return data;
}
