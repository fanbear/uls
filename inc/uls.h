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

typedef struct s_flags {
	char *flags;
} t_flags;

void mx_check_dirs(int index, int argc, char **argv);
char *mx_get_flags(int *index, int argc, char **argv);


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
