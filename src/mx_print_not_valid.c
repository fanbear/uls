#include "uls.h"

void mx_print_not_valid(int amount, char **argv) {
	for (int i = 0; i < amount; i++) {
		write(2, "uls: ", 5);
		perror(argv[i]);
	}
}
