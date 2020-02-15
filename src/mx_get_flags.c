#include "uls.h"

static int amount_of_flags(t_args *args, int *amount, char *flag);
static char *parse_to_arr(int index, char **argv, int amount);
static void sort_flags(t_args *args, char *flags);

void mx_get_flags(t_args *args, int *index, int argc, char **argv) {
	int amount = 0;
	char *flags = NULL;

	while (*index < argc && argv[*index][0] == '-' ) {
		if (amount_of_flags(args, &amount, argv[*index]))
			break;
		(*index)++;
	}
	for (int i = 0; i < 9; i++) {
		args->fl[i] = 0;
	}
	if (*index > 1) {
		flags = parse_to_arr(*index, argv, amount);
		args->flags = mx_strdup(flags);
		sort_flags(args, flags);
	}
	if (!flags)
		args->flags = mx_strnew(0);
	mx_strdel(&flags);
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
			exit(1);
		}
	}
	*amount += mx_strlen(flag) - 1;
	if (mx_strlen(flag) == 1)
		return -1;
	return 0;
}

static char *parse_to_arr(int index, char **argv, int amount) {
	char *flags = mx_strnew(amount + 1);
	int k = 0;
	int i;
	int j;

	for (i = 1; i < index; i++) {
		for (j = 1; argv[i][j]; j++) {
			flags[k++] = argv[i][j];
		}
	}
	return flags;
}

static void sort_flags(t_args *args, char *flags) {
	int index = -1;

	for (int i = 0; flags[i]; i++) {
		if (flags[i] == '1' || flags[i] == 'C' || flags[i] == 'm' ||
			flags[i] == 'l' || flags[i] == 'g')
			index = i;
		else if (flags[i] == 'G')
			args->fl[1] = 1;
		else if (flags[i] == 'R')
			args->fl[2] = 1;
		else if (flags[i] == 'a')
			args->fl[3] = 1;
		else if (flags[i] == 'r')
			args->fl[7] = 1;
	}
	if (index != -1)
		args->fl[mx_get_char_index(LEGAL, flags[index])] = 1;
}
