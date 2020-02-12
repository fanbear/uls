#include "uls.h"

int main(int argc, char **argv) {
	t_args *args = mx_sort_args(argc, argv);
	t_dirs *dirs = mx_get_dir_entry(args);
	bool symbol_l = false;
	bool symbol_m = false;
	bool symbol_g = false;

	if (args->flags) {
		for (int i = 0; args->flags[i]; i++) {
			if (args->flags[i] == 'l')
				symbol_l = true;
			if (args->flags[i] == 'm')
				symbol_m = true;
			if (args->flags[i] == 'g')
   				symbol_g = true;
		}
	}

	if (isatty(1)) {
		if (symbol_g)
			mx_print_ls_g(args, dirs);
		else if (!symbol_l)
			if (symbol_m)
				mx_print_flag_m(args, dirs);
			else
				mx_print(args, dirs, mx_print_ls_multy_colomn);
		else {
			mx_print_ls_l(args, dirs);
		}
	} else {
		if (!symbol_l)
			if (symbol_m)
				mx_print_flag_m(args, dirs);
			else
			mx_print(args, dirs, mx_print_ls_monocolomn);
		else {
			mx_print_ls_l(args, dirs);
		}
	}

	mx_del_dirs_struct(dirs);
	mx_del_args_struct(args, NOT_VALID);
	//system("leaks -q uls");
	//exit(1);
}
