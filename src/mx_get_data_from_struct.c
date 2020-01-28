#include "uls.h"

static bool filter(const char *data, char symbol);

char **mx_get_data_from_struct(t_dirs *dirs, char symbol) {
    t_dirs_entry *temp = dirs->entry_dir;
    char *data = mx_strdup(" ");
    char **res = NULL;

    while (temp) {
        if (filter(temp->d_name, symbol)) {
            char *tmp = mx_strjoin(data, temp->d_name);
            
            mx_strdel(&data);
            data = mx_strdup(tmp); 
            tmp = mx_strjoin(data, " ");
            mx_strdel(&data);
            data = mx_strdup(tmp); 
            mx_strdel(&tmp);
        }
        temp = temp->next;
    }
    res = mx_strsplit(data, ' ');
    mx_strdel(&data);
    return res;
}

static bool filter(const char *data, char symbol) {
    if (data[0] != symbol) {
        return true;
    }
    return false;
}
