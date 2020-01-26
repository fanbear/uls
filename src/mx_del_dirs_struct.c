#include "uls.h"
void lll(t_dirs *dirs);
static void del_entry_dir(t_dirs_entry *entry_dir);

void mx_del_dirs_struct(t_dirs *dirs) {
    t_dirs *temp = dirs;
    while (dirs) {
        t_dirs *temp_dir = dirs->next;

        del_entry_dir(dirs->entry_dir);
        mx_strdel(&dirs->dir);
        dirs = temp_dir;
    }
    printf("%p == %p\n", (void *)dirs, (void *)temp);
    printf("malloc_size = %zu\n",malloc_size((void *)temp));
    fflush(stdout);
    // free(temp);
    // exit(1);

}

static void del_entry_dir(t_dirs_entry *entry_dir) {

    while (entry_dir) {
        t_dirs_entry *temp_entry = entry_dir->next;

        // printf("%p == %p\n", (void *)entry_dir, (void *)temp_entry);
        // printf("%s != %s\n", entry_dir->d_name, temp_entry->d_name);
        mx_strdel(&entry_dir->d_name);
        // if (entry_dir->next) {
        //     free(entry_dir->next);
        //     entry_dir->next = NULL;
        // }
        free(entry_dir);
        entry_dir = temp_entry;
        // printf("%p == %p\n", (void *)entry_dir, (void *)temp_entry);
    }
}

void lll(t_dirs *dirs) {
    while (true) {
        printf("%s\n", dirs->dir);
        fflush(stdout);
        if (!dirs->next)
            break;
        dirs = dirs->next;
    }
}
