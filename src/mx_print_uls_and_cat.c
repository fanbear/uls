#include "uls.h"

void mx_print_uls_and_cat(int argc, char **argv) {
	st_general *gnr = (st_general*)malloc(sizeof(st_general));

	if (isatty(1)) {
		if (argc == 1)
			mx_uls_only(gnr);
		if (argc > 1)
			mx_print_directory(gnr, argc, argv);
	}
	else
		if (argc == 1)
			mx_output_cat(gnr, argc,argv);
		if (argc > 1)
			mx_print_directory(gnr, argc, argv);

	// mx_del_strarr(&gnr->d_str);
	free(gnr);
}
