#include "uls.h"

static void many_dir(t_args *args, t_dirs *dirs, char *delim, char **data);
static void file_a_dir(t_args *args, t_dirs *dirs, char *delim, char **data);

void mx_print_flag_mp(t_args *args, t_dirs *dirs, char *delim) {
	if (dirs) {
        char **data = NULL;
        if (dirs->next || args->not_valid[0] || args->files[0])
            while (dirs) {
                if (mx_check_on_access(1, dirs->dir))
                    dirs = dirs->next;
                else {
                    many_dir(args, dirs, delim, data);
                 	dirs = dirs->next;
                }
				if (dirs)
					mx_printchar('\n');
            }
        else
	        file_a_dir(args, dirs, delim, data);
    }
}
static void many_dir(t_args *args, t_dirs *dirs, char *delim, char **data) {
	int count = 0;
	data = mx_get_data_from_struct(dirs);
	mx_printstr(dirs->dir);
	mx_printstr(":\n");
	for(int i = 0; data[i] != NULL; i++) {
		if (mx_get_window_size(args) <= count + mx_strlen(data[i]) + 2) {
			mx_printstr("\n");
			count = 0;
		}
		mx_printstr(data[i]);
		if (data[i + 1])
			mx_printstr(delim);
		else
			mx_printstr("\n");
		count += (mx_strlen(data[i]) + 2);
	}
	mx_del_str_arr(data);
}
static void file_a_dir(t_args *args, t_dirs *dirs, char *delim, char **data) {
	int count = 0;
	if (!mx_check_on_access(0, dirs->dir)) { // принтуем даныые ./ && директирию
		data = mx_get_data_from_struct(dirs);
		for(int i = 0; data[i] != NULL; i++) {
			if (mx_get_window_size(args) <= count + mx_strlen(data[i]) + 2) {
				mx_printstr("\n");
				count = 0;
			}
			mx_printstr(data[i]);
			if (data[i + 1])
				mx_printstr(delim);
			else
				mx_printstr("\n");
			count += (mx_strlen(data[i]) + 2);
		}
		mx_del_str_arr(data);
	}
}
