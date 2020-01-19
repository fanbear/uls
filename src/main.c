#include "uls.h"

static void mx_sort_args(t_args *args, int argc, char **argv) {
	int index = 1;

	args->flags = mx_get_flags(&index, argc, argv);
	if (argc > 1) {
		mx_args_to_struct(index, argc, argv, args);
		mx_print_not_valid(mx_arr_size(args->not_valid), args->not_valid);
	}
}

int main(int argc, char **argv) {
	t_args *args = (t_args *)malloc(sizeof(t_args));

	mx_sort_args(args, argc, argv);

	// st_general *gnr = (st_general*)malloc(sizeof(st_general));

	// if (isatty(1)) {
	//
	// }
	// else {
	// 	printf("asd\n");
	// }
	// if (argc == 1)
	// 		mx_uls_only(gnr);
	// 	if (argc > 1) {
	// 		gnr->d_str = mx_uls_no_flag(argc, argv);
	// 		mx_print_directory(gnr);
	// 	}
	system("leaks -q uls");
}
