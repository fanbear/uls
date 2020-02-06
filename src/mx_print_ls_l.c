#include "uls.h"

static void print_dirs(t_dirs *dirs);

static void print_space(int max_elem, char* str) {
	for(int j = 0; j < max_elem - mx_strlen(str); j++) {
		mx_printchar(' ');
	}
}

static void print_total(int sum_total) {
	mx_printstr("total ");
	mx_printint(sum_total);
	mx_printchar('\n');
}



void mx_print_ls_l(t_args *args, t_dirs *dirs) {
    // if (args->files[0]) {
    //     mx_print(args->files);
    //     if (dirs)
    //         mx_printchar('\n');
    // }
	// printf("dirs = %d\n", mx_arr_size(args->dirs));
	// exit(1);
    if (dirs) {
        if (dirs->next || args->not_valid[0] || args->files[0])
            while (dirs) {
				if (mx_check_on_access(1, dirs->dir)) {
					dirs = dirs->next;
				}
				else {
					mx_printstr(dirs->dir);
					mx_printstr(":\n");
					mx_sort_content(dirs->entry_dir);
		            print_dirs(dirs);
					dirs = dirs->next;
				}
				if (dirs)
					mx_printchar('\n');
            }
        else {
			if (!mx_check_on_access(0, dirs->dir)) {
				mx_sort_content(dirs->entry_dir);
				print_dirs(dirs);
			}
		}
    }
}

static void print_dirs(t_dirs *dirs) {
    t_dirs_entry *temp = dirs->entry_dir;


	print_total(dirs->total);
    while (temp) {
		// printf("dirs->max_time = %d, temp->stat->time = %d\n", dirs->max_time, mx_strlen(temp->stat->time));
        mx_printstr(temp->stat->permiss);
        mx_printchar(' ');
        print_space(dirs->max_link, temp->stat->nlink);
        mx_printstr(temp->stat->nlink);
        mx_printchar(' ');
        mx_printstr(temp->stat->user_name);
        print_space(dirs->max_user, temp->stat->user_name);
        mx_printchar(' ');
        mx_printchar(' ');
        mx_printstr(temp->stat->group_name);
        print_space(dirs->max_group, temp->stat->group_name);
        mx_printchar(' ');
        mx_printchar(' ');
		print_space(dirs->max_size, temp->stat->file_size);
        mx_printstr(temp->stat->file_size);
        mx_printchar(' ');
        mx_printstr(temp->stat->time1);
		print_space(dirs->max_time, temp->stat->time2);
		mx_printstr(temp->stat->time2);
        mx_printchar(' ');
        mx_printstr(temp->d_name);
		if (temp->stat->name_link[0]) {
			mx_printstr(" -> ");
			mx_printstr(temp->stat->name_link);
		}
		mx_printchar('\n');
        temp = temp->next;
    }
}
