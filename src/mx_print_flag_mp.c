#include "uls.h"

static void many_dir(t_args *args, t_dirs *dirs, char *delim);
static void file_a_dir(t_args *args, t_dirs *dirs, char *delim);
static void print_files(t_args *args, char **data, char *delim);

void mx_print_flag_mp(t_args *args, t_dirs *dirs, char *delim) {
	int toggle = 0;

	if (args->files[0]) {
		print_files(args, args->files, delim);
		if (dirs) {
			mx_printchar('\n');
		}
	}
	if (dirs) {
        if (dirs->next || args->not_valid[0] || args->files[0])
            while (dirs) {
                if (!mx_check_on_access(1, dirs->dir)) {
					if (args->fl[2] && !toggle)
						toggle = 1;
					else {
						mx_printstr(dirs->dir);
						mx_printstr(":\n");
					}
					many_dir(args, dirs, delim);
                }
				dirs = dirs->next;
				if (dirs)
					mx_printchar('\n');
            }
        else
	        file_a_dir(args, dirs, delim);
    }
}

static void many_dir(t_args *args, t_dirs *dirs, char *delim) {
	char **data = mx_get_data_from_struct(dirs);
	int count = 0;

	for(int i = 0; data[i] != NULL; i++) {
		if (mx_get_window_size(args) <= count + mx_strlen(data[i]) + 2) {
			mx_printstr("\n");
			count = 0;
		}
		mx_colored_name(args, data[i], dirs->dir);
		if (data[i + 1])
			mx_printstr(delim);
		else
			mx_printstr("\n");
		count += (mx_strlen(data[i]) + 2);
	}
	mx_del_str_arr(data);
}

static void file_a_dir(t_args *args, t_dirs *dirs, char *delim) {
	int count = 0;
	if (!mx_check_on_access(0, dirs->dir)) {
		char **data = mx_get_data_from_struct(dirs);

		for(int i = 0; data[i] != NULL; i++) {
			if (mx_get_window_size(args) <= count + mx_strlen(data[i]) + 2) {
				mx_printstr("\n");
				count = 0;
			}
			mx_colored_name(args, data[i], dirs->dir);
			if (data[i + 1])
				mx_printstr(delim);
			else
				mx_printstr("\n");
			count += (mx_strlen(data[i]) + 2);
		}
		mx_del_str_arr(data);
	}
}

static void print_files(t_args *args, char **data, char *delim) {
	int count = 0;

	for(int i = 0; data[i] != NULL; i++) {
		if (mx_get_window_size(args) <= count + mx_strlen(data[i]) + 2) {
			mx_printstr("\n");
			count = 0;
		}
		mx_colored_name(args, data[i], NULL);
		if (data[i + 1])
			mx_printstr(delim);
		else
			mx_printstr("\n");
		count += (mx_strlen(data[i]) + 2);
	}
}
