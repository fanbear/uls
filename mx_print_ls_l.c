#include "uls.h"

// static void print_dir(t_dirs *dirs, int *toggle) {
// 	if (!mx_check_on_access(1, dirs->dir)) {
// 		mx_printstr(dirs->dir);
// 		mx_printstr(":\n");
// 		mx_print_dirs_ls(dirs);
// 	}
// }

void mx_print_ls_l(t_args *args, t_dirs *dirs) {
	int toggle = 0;

	if (args->files[0]) {
		mx_print_file_ls(args);
		if (dirs) {
			mx_printchar('\n');
		}
	}
	if (dirs) {
    	if (dirs->next || args->not_valid[0] || args->files[0])
        	while (dirs) {
				if (!mx_check_on_access(1, dirs->dir)) {
					if (args->fl[2] && !toggle)
					toggle = 1;
					else {
						mx_printstr(dirs->dir);
						mx_printstr(":\n");
					}

					mx_print_dirs_ls(dirs, args);
				}
				dirs = dirs->next;
				if (dirs)
					mx_printchar('\n');
        	}
    	else if (!mx_check_on_access(0, dirs->dir))
				mx_print_dirs_ls(dirs, args);
	}
}
