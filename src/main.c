#include "uls.h"

int main(int argc, char **argv) {
	t_args *args = mx_sort_args(argc, argv);
	t_dirs *dirs = mx_get_dir_entry(args);
	char symbol = '.';
	bool symbol_l = false;

	if (args->flags) {
		for (int i = 0; args->flags[i]; i++) {
			if (args->flags[i] == 'a')
				symbol = '\0';
			if (args->flags[i] == 'l')
				symbol_l = true;
		}
	}

	if (isatty(1)) {
		if (!symbol_l)
			mx_print(args, dirs, symbol, mx_print_ls_multy_colomn);
		else {
			mx_print_ls_l(args, dirs);
		}
	} else {
		if (!symbol_l)
			mx_print(args, dirs, symbol, mx_print_ls_monocolomn);
		else {
			mx_print_ls_l(args, dirs);
		}
	}

	mx_del_dirs_struct(dirs);
	mx_del_args_struct(args, NOT_VALID);
	// system("leaks -q uls");
}
