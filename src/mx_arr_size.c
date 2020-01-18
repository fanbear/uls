#include "uls.h"

int mx_arr_size(char **arr) {
    int i = 0;
    while (arr[i])
        i++;
    return i;
}
