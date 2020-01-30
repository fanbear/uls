#include "uls.h"

t_file *mx_get_stat(char *data, int *total) {
    t_file *stat = malloc(sizeof(t_file));

    mx_check_on_access(data);
    mx_get_data_info(stat, data, total);
    return stat;
}
