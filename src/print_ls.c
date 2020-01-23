#include "uls.h"

static int max_d_namlen(t_dirs_entry *entry_dir);
static char **sort_data(t_dirs *dirs);

void print_ls(t_dirs *dirs) {
    int max_size = mx_get_window_size();
    char **data = sort_data(dirs);
    int max_d_len = max_d_namlen(dirs->entry_dir);
    int cols = max_size / (max_d_len + 1);

    printf("cols = %d\n", cols);
    printf("rows = %d\n", dirs->amount_d_data / cols);

    for (int i = 0; i < dirs->amount_d_data; i++) {
        for (int j = 0; j < cols && i < dirs->amount_d_data - 1; j++) {
            printf("%s", data[i]);
            if (j == cols - 1) {
                printf("\n");
                break;
            }
            if (mx_strlen(data[i]) % 8)
                printf("\t");
            if (max_d_len - mx_strlen(data[i]) >= 8 )
                printf("\t");
            i += dirs->amount_d_data / cols + 1;
        }
    }
}

static int max_d_namlen(t_dirs_entry *entry_dir) {
    t_dirs_entry **temp = &entry_dir;
    int max_len = 0;

    // printf("address of entry_dir: %p\taddress of temp: %p\n", (void*)entry_dir, (void*)temp);

    while (*temp) {
        // printf("d_name = \"%s\"d_namlen = %d\n", (*temp)->d_name, (*temp)->d_namlen);
        max_len = ((*temp)->d_namlen > max_len) ? (*temp)->d_namlen : max_len;
        temp = &(*temp)->next;
    }
    // printf("address of entry_dir: %p\taddress of temp: %p\n", (void*)entry_dir, (void*)temp);
    if (max_len % 8) 
        max_len += 8 - (max_len % 8);
    else
        max_len += 8;
    
    return max_len;
}

static char **sort_data(t_dirs *dirs) {
    t_dirs_entry **temp = &dirs->entry_dir;
    char **data = mx_get_data_from_struct(*temp);

    for (int i = 0; i < dirs->amount_d_data; i++) {
        for (int j = 0; j < dirs->amount_d_data - i - 1; j++) {
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
