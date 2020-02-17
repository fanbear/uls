#include "uls.h"

static int max_d_namlen(t_args *args, char **data);
static void add_tabs(t_args *args, int max_size, int size);
static void multi_clm_print(t_args *args, char **data, int max_size, int max_d_len);

void mx_print_ls_multy_colomn(char **data, t_args *args) {
    int max_size = mx_get_window_size(args);
    int max_d_len = max_d_namlen(args, data);

    multi_clm_print(args, data, max_size, max_d_len);
}

static void multi_clm_print(t_args *args, char **data, int max_size, int max_d_len) {
    int arr_size = mx_arr_size(data);
    int cols = max_size / (max_d_len);
    int rows = (arr_size % cols) ? arr_size / cols + 1 : arr_size / cols;

    for (int i = 0; i < rows; i++) {
        for (int k = i; k < arr_size; k += rows) {
                mx_printstr(data[k]);
                if (!(--cols) || k + rows >= arr_size) {
                    mx_printstr("\n");
                    cols = max_size / (max_d_len);
                    break;
                }
                if (args->fl[1]) {
                    for (int i = 0; i <= max_d_len - mx_strlen(data[k]); i++)
                        mx_printchar(' ');
                }
                else if (mx_strlen(data[k]) % 8) {
                    mx_printstr("\t");
                }
                add_tabs(args, max_d_len, mx_strlen(data[k]));
        }
    }
}

static int max_d_namlen(t_args *args, char **data) {
    int max_len = 0;

    while (*data) {
        max_len = (mx_strlen(*data) > max_len) ? mx_strlen(*data) : max_len;
        (data)++;
    }
    if (args->fl[1]) {
        return max_len;
    }
    if (max_len % 8)
        max_len += 8 - (max_len % 8);
    else
        max_len += 8;
    return max_len;
}

static void add_tabs(t_args *args, int max_size, int size) {
    if (!args->fl[1] && (max_size - size) % 8 == 0)
        mx_printstr("\t");
    while (!args->fl[1] && (max_size - size) > 8) {
        mx_printstr("\t");
        size += 8 - (size % 8);
    }
}
