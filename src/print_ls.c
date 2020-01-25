#include "uls.h"

static int max_d_namlen(t_dirs_entry *entry_dir, char symbol);
static char **sort_data(t_dirs *dirs, char symbol);
static void add_tabs(int max_size, int size);

void print_ls(t_dirs *dirs, char symbol) {
    int max_size = mx_get_window_size();
    char **data = sort_data(dirs, symbol);
    int max_d_len = max_d_namlen(dirs->entry_dir, symbol);
    int cols = max_size / (max_d_len);
    int rows = (mx_arr_size(data) % cols) ? mx_arr_size(data) / cols + 1 : mx_arr_size(data) / cols;

    // printf("cols = %d\n", cols);
    // printf("rows = %d\n", rows);
    for (int i = 0; i < rows; i++) {
        for (int k = i; k < mx_arr_size(data); k += rows) {
                printf("%s", data[k]);
                if (!(--cols) || k + rows >= mx_arr_size(data)) {
                    printf("\n");
                    cols = max_size / (max_d_len);
                    break;
                }
                if (mx_strlen(data[k]) % 8)
                    printf("\t");
                add_tabs(max_d_len, mx_strlen(data[k]));
        }
    }
}

static int max_d_namlen(t_dirs_entry *entry_dir, char symbol) {
    t_dirs_entry **temp = &entry_dir;
    int max_len = 0;

    while (*temp) {
        if ((*temp)->d_name[0] != symbol) {
            max_len = ((*temp)->d_namlen > max_len) ? (*temp)->d_namlen : max_len;
        }
        temp = &(*temp)->next;
    }
    if (max_len % 8) 
        max_len += 8 - (max_len % 8);
    else
        max_len += 8;
    
    return max_len;
}

static char **sort_data(t_dirs *dirs, char symbol) {
    char **data = mx_get_data_from_struct(dirs, symbol);

    for (int i = 0; i < mx_arr_size(data); i++) {
        for (int j = 0; j < mx_arr_size(data) - i - 1; j++) {
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

static void add_tabs(int max_size, int size) {
    if ((max_size - size) % 8 == 0)
        printf("\t");
    while ((max_size - size) > 8) {
        printf("\t");
        size += 8 - (size % 8);
    }
}
