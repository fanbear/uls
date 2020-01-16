#include "uls.h"

int main(int argc, char *argv[]) {
	st_general *gnr = (st_general*)malloc(sizeof(st_general));

	if (argc == 1)
		mx_opendir(gnr);
	if (argc > 1) {
		gnr->d_str = mx_uls_no_flag(argc, argv);
		mx_print_no_flag(argc, argv, gnr);
	}
	// mx_del_strarr(&gnr->d_str);
	// mx_del_strarr(&gnr->no_point);
	// free(gnr);
	// system("leaks -q uls");
}

