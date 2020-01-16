#include "uls.h"

void mx_uls_no_flag(int argc, char *argv[]) {

	DIR            *dptr;
    struct dirent  *ds;
    dptr = opendir(argv[1]);
    for (int i = 1; i < argc; ++i) {
    	while ((ds = readdir(dptr)) != 0)
    		mx_print_strarr(ds->d_name);
    }
    mx_printchar('\n');
    closedir(dptr);
}