#include "uls.h"

static int max_d_namlen(char **data);
static void add_tabs(int max_size, int size);
static void multi_clm_print(char **data, int max_size, int max_d_len, char *dir);
static t_file *get_stat(char *data, char *dir);

void mx_print_multy_colomn_g(char **data,  t_args *args, char *dir) {
    int max_size = mx_get_window_size(args);
    int max_d_len = max_d_namlen(data);

    multi_clm_print(data, max_size, max_d_len, dir);
}

static void multi_clm_print(char **data, int max_size, int max_d_len, char *dir) {
    int arr_size = mx_arr_size(data);
    int cols = max_size / (max_d_len);
    int rows = (arr_size % cols) ? arr_size / cols + 1 : arr_size / cols;

    for (int i = 0; i < rows; i++) {
        for (int k = i; k < arr_size; k += rows) {
                t_file *stat = get_stat(data[k], dir);

                mx_colored_name(1, stat->color, data[k]);
                if (!(--cols) || k + rows >= arr_size) {
                    mx_printstr("\n");
                    cols = max_size / (max_d_len);
                    break;
                }
                add_tabs(max_d_len, mx_strlen(data[k]));
                if (data[k + 1]) {
                    mx_printstr(" ");
                }
        }
    }
}

static int max_d_namlen(char **data) {
    int max_len = 0;

    while (*data) {
        max_len = (mx_strlen(*data) > max_len) ? mx_strlen(*data) : max_len;
        (data)++;
    }
    return max_len;
}

static void add_tabs(int max_size, int size) {
    int count = max_size - size;

    while (count != 0) {
        mx_printstr(" ");
        count--;
    }
}

static t_file *get_stat(char *data, char *dir) {
    if (dir) {
        dir = mx_strjoin(dir, "/");
        data = mx_strjoin(dir, data);
    }
    return mx_get_stat(data);
}
