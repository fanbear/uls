#include "uls.h"

static void print_dir(t_dirs *dirs) {
	if (mx_check_on_access(1, dirs->dir))
		dirs = dirs->next;
	else {
		mx_printstr(dirs->dir);
		mx_printstr(":\n");
		mx_sort_content(dirs->entry_dir);
		mx_print_dirs_ls(dirs);
		dirs = dirs->next;
	}
}

void mx_print_ls_l(t_args *args, t_dirs *dirs) {
	if (args->files[0]) {
		mx_print_file_ls(args);
		if (dirs)
			mx_printchar('\n');
	}
    if (dirs) {
        if (dirs->next || args->not_valid[0] || args->files[0])
            while (dirs) {
				print_dir(dirs);
				if (dirs)
					mx_printchar('\n');
            }
        else {
			if (!mx_check_on_access(0, dirs->dir)) {
				mx_sort_content(dirs->entry_dir);
				mx_print_dirs_ls(dirs);
			}
		}
    }
}
