#include "uls.h"

void mx_print_uls_and_cat(int argc, char **argv) {
	st_general *gnr = (st_general*)malloc(sizeof(st_general));

	if (isatty(1)) {
		if (argc == 1)
			mx_uls_only(gnr);
		if (argc > 1){
			gnr->d_str = mx_uls_no_flag(argc, argv);
			mx_print_directory(gnr);
		}
	}
	else {
		mx_output_cat(gnr, argc,argv);
	}
}
