#include "uls.h"

static bool is_flag(char *flag);
static void amount_of_flags(int *amount, char *flag);
static char *parse_to_arr(int index, char **argv, int amount);
static char *del_dub_and_sort_flags(char *flags, int size);

char *mx_get_flags(int *index, int argc, char **argv) {
	int amount = 0;
	char *flags = NULL;
	if (argc > 1) {
		while (*index < argc && argv[*index][0] == '-' ) {
			if (is_flag(argv[*index])) {
				amount_of_flags(&amount, argv[*index]);
				(*index)++;
			}
			else
				break;
		}
		if (*index > 1)
			flags = del_dub_and_sort_flags(parse_to_arr(*index, argv, amount), amount);
	}
	return flags;
}

static bool is_flag(char *flag) {
	for (int i = 1; flag[i]; i++) {
		if (flag[i] == '-')
			return false;
	}
	return true;
}

static void amount_of_flags(int *amount, char *flag) {
	for (int i = 1; flag[i]; i++) {
		if (mx_get_char_index(LEGAL, flag[i]) == -1) {
			write(2, "uls: illegal option -- ", 23);
			write(2, &flag[i], 1);
			write(2, "\nusage: uls [-a] [file ...]\n", 28);
			exit(1);
		}
	}
	*amount += mx_strlen(flag) - 1;
}

static char *parse_to_arr(int index, char **argv, int amount) {
	char *flags = NULL;
	if (index != 1) {
		int k = 0;
		int i;
		int j;

		flags = mx_strnew(amount + 1);
		for (i = 1; i < index; i++) {
			for (j = 1; argv[i][j]; j++) {
				flags[k++] = argv[i][j];
			}
		}
		return flags;
	}
	return NULL;
}

static char *del_dub_and_sort_flags(char *flags, int size) {
	int count = 0;
	char *res = NULL;
	int i = 0;
	int j = 0;

	for (; i < size; i++) {
		for (; j < size - 1; j++) {
			if (i == size - 1 && flags[j] == flags[j + 1])
				count++;
			if (flags[j] > flags[j + 1]) {
				char temp = flags[j];

				flags[j] = flags[j + 1];
				flags[j + 1] = temp;
			}
		}
	}
	res = mx_strnew(size - count + 1);
	j = 0;
	for (i = 0; i < mx_strlen(flags); i++) {
		if (flags[i] != flags[i + 1])
			res[j++] = flags[i];
	}
	return res;
}
