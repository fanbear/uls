#include "uls.h"

void mx_print_flag_m(t_args *args, t_dirs *dirs) {

	if (dirs) {
        char **data = NULL;

        int count = 0;

        if (dirs->next || args->not_valid[0] || args->files[0])
            while (dirs) {
                if (mx_check_on_access(1, dirs->dir)) {
                    dirs = dirs->next;
                }
                else {
                    data = mx_sort_data(dirs, args);
                    mx_printstr(dirs->dir);
                    mx_printstr(":\n");
	                for(int i = 0; data[i] != NULL; i++) {
						mx_printstr(data[i]);
						if (data[i + 1])
							mx_printstr(", ");
						else
							mx_printstr("\n");
						count += (mx_strlen(data[i]) + 4);
						if (mx_get_window_size(args) <= count) {
							mx_printstr("\n");
							count = 0;
						}
					 }
                    mx_del_str_arr(data);
                    dirs = dirs->next;
                    if (dirs)
                        mx_printchar('\n');
                }
            }
        else
	        if (!mx_check_on_access(0, dirs->dir)) { // принтуем даныые ./ && директирию
	        	data = mx_sort_data(dirs, args);
	        	for(int i = 0; data[i] != NULL; i++) {
					mx_printstr(data[i]);
					if (data[i + 1])
						mx_printstr(", ");
					else
						mx_printstr("\n");
					count += (mx_strlen(data[i]) + 3);
					if (data[i + 1] && mx_get_window_size(args) <= count + mx_strlen(data[i + 1])) {
						mx_printstr("\n");
						count = 0;
					}
				}
	        	mx_del_str_arr(data);
	        }
    }
}
