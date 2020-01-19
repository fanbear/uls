#include "uls.h"

static void print_err_exist(char *arg);

void mx_print_not_valid(int amount, char **argv) {
	int i;

	for (i = 0; i < amount; i++) {
		print_err_exist(argv[i]);
	}
}

static void print_err_exist(char *arg) {
	write(2, "uls: ", 5);
	perror(arg);
	return ;
}
