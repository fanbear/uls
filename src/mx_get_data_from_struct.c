#include "uls.h"

static bool filter(const char *data, char symbol);

char **mx_get_data_from_struct(t_dirs *dirs, char symbol) {
    t_dirs_entry *temp = dirs->entry_dir;
    char *data = mx_strdup(" ");

    while (temp) {
        if (filter(temp->d_name, symbol)) {
            data = mx_strjoin(data, temp->d_name);
            data = mx_strjoin(data, " ");
        }
        temp = temp->next;
    }
    return mx_strsplit(data, ' ');
}

static bool filter(const char *data, char symbol) {
    if (data[0] != symbol) {
        return true;
    }
    return false;
}
