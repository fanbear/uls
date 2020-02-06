#include "uls.h"

static void max_value(int *value, char *data) {
    int j = mx_strlen(data);

	if(*value < j)
        *value = j;
}

void mx_get_max_value(t_dirs *dir) {
    t_dirs_entry *temp = dir->entry_dir;

    dir->max_group = 0;
    dir->max_user = 0;
    dir->max_size = 0;
    dir->max_link = 0;
    dir->max_time = 0;

    while (temp) {
        max_value(&dir->max_group, temp->stat->group_name);
        max_value(&dir->max_user, temp->stat->user_name);
        max_value(&dir->max_size, temp->stat->file_size);
        max_value(&dir->max_link, temp->stat->nlink);
        max_value(&dir->max_time, temp->stat->time2);
        dir->total += temp->stat->buf.st_blocks;
        temp = temp->next;
    }
}
