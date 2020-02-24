#include "uls.h"

char **mx_sort_data(t_args *args, char **data) {
    int size = mx_arr_size(data);
    // t_dirs_entry *temp = dirs->entry_dir;

    if (args->fl[9] == 1) {
    	return data;
    }
    if (args->fl[7] == 0)
        mx_quicksort(data, 0, size - 1);
    else{
        mx_quicksort_r(data, 0, size - 1);
    }
    return data;
}
