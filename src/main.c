#include "uls.h"

static void uls_print(t_args *args, t_dirs *dirs);
// static void print_one_flag(t_args *args, t_dirs *dirs);

int main(int argc, char **argv) {
	t_args *args = mx_sort_args(argc, argv);
	t_dirs *dirs = mx_get_dir_entry(args);
	// mx_del_dirs_struct(dirs);
	// mx_del_args_struct(args, NOT_VALID);
	//
	//
	// system("leaks -q uls");
	// exit(1);


	if (args->fl[4]) // печать одного флага
		mx_print_ls_g(args, dirs);
	else if (args->fl[5]) // печать одного флага
		mx_print_ls_l(args, dirs);
	else if (args->fl[6]) // печать одного флага
		mx_print_flag_mp(args, dirs);
	else
		uls_print(args, dirs);


}


static void uls_print(t_args *args, t_dirs *dirs) {
	if ((isatty(1) || args->fl[0]) && !args->fl[8]) {
		mx_print(args, dirs, mx_print_ls_multy_colomn); // обычный принт
	}
	else
		mx_print(args, dirs, mx_print_ls_monocolomn); // обычный принт | cat -e
}
