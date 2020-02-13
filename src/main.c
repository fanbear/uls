#include "uls.h"

static void uls_print(t_args *args, t_dirs *dirs);
static void print_one_flag(t_args *args, t_dirs *dirs);

int main(int argc, char **argv) {
	t_args *args = mx_sort_args(argc, argv);
	t_dirs *dirs = mx_get_dir_entry(args);

	if (mx_struct_flag(argc, argv, args) == 0) // печать без флагов
		uls_print(args, dirs);
	if (mx_struct_flag(argc, argv, args) == 1) // печать одного флага
		print_one_flag(args, dirs);	
	if (mx_struct_flag(argc, argv, args) == 2) // печать комбо флагов
		printf("flag is more thet one\n");
	mx_del_dirs_struct(dirs);
	mx_del_args_struct(args, NOT_VALID);
	//system("leaks -q uls");
	//exit(1);
}

static void uls_print(t_args *args, t_dirs *dirs) {
	if (isatty(1))
		mx_print(args, dirs, mx_print_ls_multy_colomn); // обычный принт
	else 
		mx_print(args, dirs, mx_print_ls_monocolomn); // обычный принт | cat -e 
}

static void print_one_flag(t_args *args, t_dirs *dirs) {
	if (isatty(1)) {
		if (args->print == 6) // если -g
			printf("-1\n");
		if (args->print == 5) // если -g
			mx_print_ls_g(args, dirs);
		if (args->print == 4) // если -m
			mx_print_flag_m(args, dirs);
		if (args->print == 3) // если -C
			mx_print(args, dirs, mx_print_ls_multy_colomn);
		if (args->print == 2) // если -l
			mx_print_ls_l(args, dirs);
		if (args->print == 1) // если -R
			mx_recursive_open_dirs(args);

	} else {
		if (args->print == 6) // если -g
			printf("-1\n");
		if (args->print == 5) // если -g
			mx_print_ls_g(args, dirs);
		if (args->print == 4) // если -m
			mx_print_flag_m(args, dirs);
		if (args->print == 3) // если -C
			mx_print(args, dirs, mx_print_ls_multy_colomn);
		if (args->print == 2)  // если -l
			mx_print_ls_l(args, dirs);
		if (args->print == 1)  // если -R
			mx_recursive_open_dirs(args);

	}
}
