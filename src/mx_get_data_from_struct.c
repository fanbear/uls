#include "uls.h"

char **mx_get_data_from_struct(t_dirs_entry *entry_dir) {
    t_dirs_entry **temp = &entry_dir;
    char *data = mx_strdup(" ");

    while (true) {
        data = mx_strjoin(data, (*temp)->d_name);
        data = mx_strjoin(data, " ");
        if ((*temp)->next)
            temp = &(*temp)->next;
        else
            break;
    }
    return mx_strsplit(data, ' ');
}
