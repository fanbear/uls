#include "uls.h"

void mx_output(st_general *gnr, int size) {
	for (int i = 0; i < size; ++i) {
    	mx_printstr(gnr->no_point[i]);
    }
    mx_printstr("\n");
}
