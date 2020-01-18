#include "uls.h"

int main(int argc, char *argv[]) {
	st_general *gnr = (st_general*)malloc(sizeof(st_general));

	// if (isatty(1)) {
		
	// }
	// else {
	// 	printf("asd\n");
	// }
	if (argc == 1)
			mx_uls_only(gnr);
		if (argc > 1) {
			gnr->d_str = mx_uls_no_flag(argc, argv);
			mx_print_directory(gnr);
		}
	// system("leaks -q uls");
}

