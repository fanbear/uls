#include "uls.h"

static char **clear_d_str(st_general *gnr);
static void b_sort(char **arr, int size);

void mx_print_no_flag(int argc, char *argv[], st_general *gnr) {
	char **temp = clear_d_str(gnr);
	argc += 0;
	printf("%s\n", argv[1]);
	b_sort(temp, 5);
	for (int i = 0; temp[i]; ++i) {
		mx_printstr(temp[i]);
		mx_printstr("\t");
	}
}

static char **clear_d_str(st_general *gnr) {
	char **temp = NULL;
	int count = 0;

	for (int i = 0; gnr->d_str[i]; ++i)
		count++;
	temp = (char**)malloc(sizeof(char**) * count);
	for (int i = 0, n = 0; gnr->d_str[i]; ++i) {
		temp[n] = (char*)malloc(sizeof(char*) * 200);
		if (mx_strcmp(gnr->d_str[i], ".") == 0) {
			i++;
		}
		temp[n] = gnr->d_str[i];
		n++;
	}
	return temp;
}


