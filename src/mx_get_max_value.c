#include "uls.h"

static void max_value(int *value, struct file *stat) {
    int j = mx_strlen(stat->nlink);

	if(*value < j)
        *value = j;
}

void mx_get_max_value(t_dirs *dir) {
    t_dirs_entry *temp = dir->entry_dir;

    // printf("1\n");
    // fflush(stdout);
    dir->max_group = 0;
    dir->max_user = 0;
    dir->max_size = 0;
    dir->max_link = 0;

    while (temp) {
        max_value(&dir->max_group, temp->stat);
        max_value(&dir->max_user, temp->stat);
        max_value(&dir->max_size, temp->stat);
        max_value(&dir->max_link, temp->stat);
        temp = temp->next;
    }
}

