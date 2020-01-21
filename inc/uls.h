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
#include <sys/types.h>
#include <sys/stat.h>

//***************************** Utils pack *******************************

typedef struct general{
	char **d_str; // данные с точками
	char **no_point; // данные без точек
} st_general;

typedef struct file { //структура для файлов
	char* permiss;
	struct stat buf;
	char *file_name;
    struct stat stat;
    char *uid_name;
    char *gid_name;
    short   nlink;        //number hard links
    blkcnt_t blocks;
    off_t file_size;
    time_t a_time;        /* [XSI] Time of last access */
    time_t m_time;
    time_t c_time;
    char *absolute_name;      //if link
    char   *name_link;        //  if  file = link for print
} t_file

char **mx_uls_no_flag(int argc, char *argv[]);
void mx_print_directory(st_general *gnr);
void mx_uls_only(st_general *gnr);
void mx_output(char **src, int size);
//-----------------------------------------------------------------------                                       

#endif
