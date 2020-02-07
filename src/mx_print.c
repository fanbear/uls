#include "uls.h"

void mx_print(t_args *args, t_dirs *dirs, void (*print_ls)(char **)) {
    if (args->files[0]) {
        (*print_ls)(args->files);
        if (dirs)
            mx_printchar('\n');
    }
    if (dirs) {
        char **data = NULL;


        if (dirs->next || args->not_valid[0] || args->files[0])
            while (dirs) {
                if (mx_check_on_access(1, dirs->dir)) {
                    dirs = dirs->next;
                }
                else {
                    data = mx_sort_data(dirs);
                    mx_printstr(dirs->dir);
                    mx_printstr(":\n");
                    (*print_ls)(data);
                    mx_del_str_arr(data);
                    dirs = dirs->next;
                    if (dirs)
                        mx_printchar('\n');
                }
            }
        else
            if (!mx_check_on_access(0, dirs->dir)) {
                data = mx_sort_data(dirs);
                (*print_ls)(data);
                mx_del_str_arr(data);
            }
    }
}
