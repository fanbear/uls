#include "uls.h"

static int check_one_flag(int argc, char **argv, t_args *args);
static void this_flag(t_args *args, char **argv);

int mx_struct_flag(int argc, char **argv, t_args *args) {
	for (int i = 0; i < argc; i++) {
		if (argv[i][0] == '-') { //  проверка на наличие флагов
			if (check_one_flag(argc, argv, args) == 1) { // проверка на кол-во флаго
				return 1; // если флаг всего 1
			}else
				return 2; // если флаго несколько или переданы через несколько аргрументов
		}
	}
	return 0; // если флагов нет, вернет один и будет стандартный вывод
}

static int check_one_flag(int argc, char **argv, t_args *args) {
	for (int i = 1; i < argc; i++) {
		if (argv[i][0] == '-') { // проверяем что бы был флаг (-) и только 2 аргумента
			if (mx_strlen(argv[i]) < 3){ //  если длина больше чем 2 то флагов несколько
				this_flag(args, argv); // проверяем какой именно флаг передали и пишем в print, sort, data;
				return 1;
			} else
				return 2;
		}
	}
	return 0;
}

static void this_flag(t_args *args, char **argv) {
		if (mx_strcmp(argv[1], "-1") == 0)
			args->print = 6; //если -1
		if (mx_strcmp(argv[1], "-g") == 0)
			args->print = 5; //если -g
		if (mx_strcmp(argv[1], "-m") == 0)
			args->print = 4; //если -m
		if (mx_strcmp(argv[1], "-C") == 0)
			args->print = 3; //если -C
		if (mx_strcmp(argv[1], "-l") == 0)
			args->print = 2; //если -l
		if (mx_strcmp(argv[1], "-R") == 0)
			args->print = 1; //если -R
}
