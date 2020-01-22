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
#include <sys/ioctl.h>

//***************************** Utils pack *******************************

typedef struct general{
	char **d_str; // данные с точками
	char **no_point; // данные без точек
	char **sort_f; // сортированые папки

} st_general;

void mx_print_uls_and_cat(int argc, char **argv);
char **mx_open_folder(char *str);
void mx_print_directory(st_general *gnr, int argc, char **argv);
void mx_uls_only(st_general *gnr);
void mx_output(char **src, int size);
void mx_output_cat(st_general *gnr, int argc, char **argv);
void mx_b_sort(char **arr, int size);
int window_size(); // ширыни терминала

//-----------------------------------------------------------------------                                       

#endif
