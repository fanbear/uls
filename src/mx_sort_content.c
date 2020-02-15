#include "uls.h"

static void swap(t_dirs_entry *a, t_dirs_entry *b) {
	char *d_name_t = a->d_name;
	t_file *stat_t = a->stat;

	a->d_name = b->d_name;
	a->stat = b->stat;
	b->d_name = d_name_t;
	b->stat = stat_t;
}

t_dirs_entry *mx_sort_content(t_dirs_entry *entry_dir) {
	t_dirs_entry *temp_i;
	t_dirs_entry *temp_j;

	for (temp_i = entry_dir; temp_i != NULL; temp_i = temp_i->next) {
		for (temp_j = temp_i; temp_j->next != NULL; temp_j = temp_j->next) {
			if (mx_strcmp(temp_i->d_name, temp_j->next->d_name) > 0) {
				swap(temp_i, temp_j->next);
			}
		}
	}
	return entry_dir;
}
