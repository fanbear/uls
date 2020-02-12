#include "uls.h"

char **mx_sort_data(t_dirs *dirs) {
    char **data = mx_get_data_from_struct(dirs);
    int size = mx_arr_size(data);


    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (mx_strcmp(data[j], data[j + 1]) > 0) {
                char *temp = mx_strdup(data[j + 1]);

                free(data[j + 1]);
                data[j + 1] = mx_strdup(data[j]);
                free(data[j]);
                data[j] = temp;
            }
        }
    }
    return data;
}
