#ifndef ULS_H
#define ULS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <errno.h>
#include <wchar.h>
#include <fcntl.h>
#include <malloc/malloc.h>
#include <dirent.h>
#include "libmx/inc/libmx.h"

//***************************** Utils pack *******************************


#define LEGAL "ABCFGHLOPRSTUWabcdefghiklmnopqrstuwx1"

typedef struct s_args {
	char *flags;
	char **files;
	char **dirs;
	char **not_valid;
} t_args;

char *mx_get_flags(int *index, int argc, char **argv);
void mx_args_to_struct(int index, int argc, char **argv, t_args *args);
void mx_print_not_valid(int amount, char **argv);
void mx_del_str_arr(char **arr);
int mx_arr_size(char **arr);


typedef struct general{
	char **d_str; // данные с точками
	char **no_point; // данные без точек
} st_general;

char **mx_uls_no_flag(int argc, char *argv[]);
void mx_print_directory(st_general *gnr);
void mx_uls_only(st_general *gnr);
void mx_output(char **src, int size);
//-----------------------------------------------------------------------

#endif
