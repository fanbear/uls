#include "uls.h"

void mx_print_not_valid(int amount, char **argv) {
	for (int i = 0; i < amount; i++) {
		errno = 2;
		write(2, "uls: ", 5);
		perror(argv[i]);
	}
}
