#include "uls.h"

void mx_print(t_args *args, t_dirs *dirs, void (*print_ls)(char **, t_args *)) {
    if (args->files[0]) {
        (*print_ls)(args->files, args);
        if (dirs)
            mx_printchar('\n');
    }
    if (dirs) {
        char **data = NULL;

        if (dirs->next || args->not_valid[0] || args->files[0]) {
            while (dirs) {
                if (!mx_check_on_access(1, dirs->dir)) {
                    data = mx_get_data_from_struct(dirs);
                    if (args->fl[2] && args->dirs_num == 1)
                        args->dirs_num = 0;
                    else {
                        mx_printstr(dirs->dir);
                        mx_printstr(":\n");
                    }
                    if (data) {
                        (*print_ls)(data, args);
                        mx_del_str_arr(data);
                    }
                }
                dirs = dirs->next;
                if (dirs)
                    mx_printchar('\n');
            }
        }
        else
            if (!mx_check_on_access(0, dirs->dir)) {
                data = mx_get_data_from_struct(dirs);
                (*print_ls)(data, args);
                mx_del_str_arr(data);
            }
        }
}
