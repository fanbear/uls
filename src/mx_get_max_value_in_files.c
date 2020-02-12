#include "uls.h"

static void max_value(int *value, char *data) {
    int j = mx_strlen(data);

	if(*value < j)
        *value = j;
}

void mx_get_max_value_in_files(t_files *files) {
    t_file_entry *temp = files->entry_file;

    files->max_group = 0;
    files->max_user = 0;
    files->max_size = 0;
    files->max_link = 0;
    files->max_time = 0;

    while (temp) {
        max_value(&files->max_group, temp->stat->group_name);
        max_value(&files->max_user, temp->stat->user_name);
        if (temp->stat->permiss[0] == 'b' ||  temp->stat->permiss[0] == 'c') {
            files->max_size = 8;
        }
        else 
            max_value(&files->max_size, temp->stat->file_size);
        max_value(&files->max_link, temp->stat->nlink);
        max_value(&files->max_time, temp->stat->time2);
        temp = temp->next;
    }
}
