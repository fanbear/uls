#include "uls.h"

char **mx_sort_data(t_dirs *dirs, t_args *args) {
    char **data = mx_get_data_from_struct(dirs);
    int size = mx_arr_size(data);
    if (args->fl[7] == 0)
        mx_quicksort(data, 0, size - 1);
    else{
        mx_quicksort_r(data, 0, size - 1);
    }
    return data;
}
