#include "uls.h"

void mx_print_ls_monocolomn(char **data) {
    int arr_size = mx_arr_size(data);

    for (int i = 0; i < arr_size; i++) {
        mx_printstr(data[i]);
        mx_printchar('\n');
    }
}
