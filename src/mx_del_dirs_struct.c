#include "uls.h"

static void del_entry_dir(t_dirs_entry *entry_dir);

void mx_del_dirs_struct(t_dirs *dirs) {
    while (dirs) {
        t_dirs *temp_dir = dirs->next;

        mx_strdel(&dirs->dir);
        del_entry_dir(dirs->entry_dir);
        free(dirs);
        dirs = NULL;
        dirs = temp_dir;
    }
}

static void del_entry_dir(t_dirs_entry *entry_dir) {
    while (entry_dir) {
        t_dirs_entry *temp_entry = entry_dir->next;

        mx_strdel(&entry_dir->d_name);

        mx_strdel(&entry_dir->stat->permiss);
        mx_strdel(&entry_dir->stat->file_name);
        mx_strdel(&entry_dir->stat->user_name);
        mx_strdel(&entry_dir->stat->group_name);
        mx_strdel(&entry_dir->stat->time1);
        mx_strdel(&entry_dir->stat->nlink);
        mx_strdel(&entry_dir->stat->file_size);
        mx_strdel(&entry_dir->stat->time2);
        mx_strdel(&entry_dir->stat->name_link);

        free(entry_dir->stat);
        entry_dir->stat = NULL;
        free(entry_dir);
        entry_dir = temp_entry;
    }
}
