#include "uls.h"

char **mx_sort_data_s(char **data, t_dirs_entry *temp) {
    int size = mx_arr_size(data);
    printf("%s\n", temp->stat->file_size);
    mx_quicksort_r(data, 0, size - 1);
    return data;
}
