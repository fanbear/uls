#include "uls.h"

void mx_del_struct(t_dirs *dirs_entry) {
    // while (dirs) {
    //     t_dirs *temp_next = dirs->next;
    //     mx_strdel(&dirs->dir);
        while (dirs_entry->entry_dir) {
			t_dirs_entry *temp_entry = dirs_entry->entry_dir->next;
            printf("%p == %p\n", (void *)dirs_entry->entry_dir, (void *)temp_entry);
			mx_strdel(&dirs_entry->entry_dir->d_name);
			if (dirs_entry->entry_dir->next) {
				free(dirs_entry->entry_dir->next);
				dirs_entry->entry_dir->next = NULL;
			}
			dirs_entry->entry_dir = temp_entry;
		}
    //     free(dirs->next);
    //     dirs->next = NULL;
    //     dirs = temp_next;
    // }
    
}
