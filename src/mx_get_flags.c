#include "uls.h"

static int amount_of_flags(t_args *args, int *amount, char *flag);
static char *parse_to_arr(int index, char **argv, int amount);
static char *del_dub(char *flags, int size);
static int sort_flags(int size, char *flags);

char *mx_get_flags(t_args *args, int *index, int argc, char **argv) {
	int amount = 0;
	char *flags = NULL;

	while (*index < argc && argv[*index][0] == '-' ) {
		if (amount_of_flags(args, &amount, argv[*index]))
			break;
		(*index)++;
	}
	if (*index > 1)
		flags = del_dub(parse_to_arr(*index, argv, amount), amount);
	if (flags)
		for (int j = 0; j < 2; j++) {
			for (int i = 0; flags[i]; i++) {
				if (LEGAL[j] == flags[i]) {
					args->fl[j] = 1;
					break;
				}
				else
					args->fl[j] = 0;
			}
		}
	return flags;
}


static int amount_of_flags(t_args *args, int *amount, char *flag) {
	for (int i = 1; flag[i]; i++) {
		if (mx_get_char_index(LEGAL, flag[i]) == -1) {
			write(2, "uls: illegal option -- ", 23);
			write(2, &flag[i], 1);
			write(2, "\nusage: uls [-", 14);
			write(2, LEGAL, mx_strlen(LEGAL));
			write(2, "] [file ...]\n", 13);
			mx_del_args_struct(args, NOTHING);
			exit(-1);
		}
	}
	*amount += mx_strlen(flag) - 1;
	if (mx_strlen(flag) == 1)
		return -1;
	return 0;
}

static char *parse_to_arr(int index, char **argv, int amount) {
	char *flags = NULL;
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

static char *del_dub(char *flags, int size) {
	int count = sort_flags(size, flags);
	char *res = mx_strnew(size - count + 1);
	int j = 0;

	for (int i = 0; i < mx_strlen(flags); i++) {
		if (flags[i] != flags[i + 1])
			res[j++] = flags[i];
	}
	mx_strdel(&flags);
	return res;
}

static int sort_flags(int size, char *flags) {
	int count = 0;

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size - 1; j++) {
			if (i == size - 1 && flags[j] == flags[j + 1])
				count++;
			if (flags[j] > flags[j + 1]) {
				char temp = flags[j];

				flags[j] = flags[j + 1];
				flags[j + 1] = temp;
			}
		}
	}
	return count;
}
