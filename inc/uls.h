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
#include <sys/acl.h>
#include <sys/types.h>
#include <sys/xattr.h>
#include <pwd.h>

//***************************** Utils pack *******************************

typedef struct file { //структура для файлов
    char* permiss;
    struct stat buf;
    char *file_name;
    struct stat stat;
    struct passwd *pw;
    char *user_name;
    char *group_name;
    char *time1;
    char   *nlink;        //кл-во линков
    blkcnt_t blocks;
    char *file_size;
    time_t a_time;        /*временные данные, для реализации разных флагов*/
    time_t m_time;
    time_t c_time;
    char *absolute_name;      //для линки, пока не пользуюсь
    char   *name_link;        //  если файл = линк для принта //пока не пользуюсь
} t_file;

typedef struct general{
     t_file  *array_p; // указатель на массив структур
     //int max_file; // максимальная длина имени файла (нужно для рассчета расстояния между файлами)
     int max_group; // максимальная длина имени группы (нужно для рассчета расстояния между файлами)
     int max_user; // максимальная длина имени юзера (нужно для рассчета расстояния между файлами)
     int max_size;// максимальная длина байт (нужно для рассчета расстояния между файлами)
     int max_link; // максимальное количетсво линки(нужно для рассчета расстояния между файлами)
     int sum_blocks; // количество выделнных блоков, принтуется в самом начале флага -л
} st_general;

void mx_output_l(st_general *gnr, int argc);
char* mx_permission(char* file, t_file *file_st);
void mx_get_inform(st_general *gnr, char* file, int i);
//-----------------------------------------------------------------------                                       

#endif
