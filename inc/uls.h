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

#define NO_FLAG "."
//***************************** Utils pack *******************************

typedef struct general{
	char **d_str; // данные с точками
	char **no_point; // данные без точек
} st_general;

char **mx_uls_no_flag(int argc, char *argv[]);
void mx_print_no_flag(int argc, char *argv[], st_general *gnr);
void mx_opendir(st_general *gnr);
void mx_output(st_general *gnr, int size);
//-----------------------------------------------------------------------                                       

#endif
