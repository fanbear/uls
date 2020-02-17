#include "uls.h"

void mx_print_G(t_args *args, t_dirs *dirs) {
    if (args->files[0]) {
        if (args->fl[1])
            mx_print_multy_colomn_g(args->files, args, NULL);
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
                        mx_print_multy_colomn_g(data, args, dirs->dir);
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
                if (data) {
                    mx_print_multy_colomn_g(data, args, dirs->dir);
                    mx_del_str_arr(data);
                }
            }
        }
}
