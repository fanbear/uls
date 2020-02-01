#include "uls.h"

void mx_print(t_args *args, t_dirs *dirs, char symbol, void (*print_ls)(char **)) {
    if (args->files[0]) {
        (*print_ls)(args->files);
        if (dirs)
            mx_printchar('\n');
    }
    if (dirs) {
        char **data = mx_sort_data(dirs, symbol);

        if (dirs->next || args->not_valid[0])
            while (dirs) {
                data = mx_sort_data(dirs, symbol);
                mx_printstr(dirs->dir);
                mx_printstr(":\n");
                (*print_ls)(data);
                dirs = dirs->next;
                if (dirs)
                    mx_printchar('\n');
            }
        else
            (*print_ls)(data);
    }
}
