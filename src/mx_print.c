#include "uls.h"

void mx_print(t_args *args, t_dirs *dirs_entry, char symbol, void (*print_ls)(char **)) {
    char **data = mx_sort_data(dirs_entry, symbol);
	
    if (dirs_entry->next || args->not_valid[0]) {
        while (dirs_entry) {
            data = mx_sort_data(dirs_entry, symbol);
            mx_printstr(dirs_entry->dir);
            mx_printstr(":\n");
            (*print_ls)(data);
            dirs_entry = dirs_entry->next;
            if (dirs_entry)
                mx_printchar('\n');
        }
    }
    else
        (*print_ls)(data);
}
