#ifndef ULS_H
#define ULS_H

#include <stdint.h>
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
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/acl.h>
#include <sys/types.h>
#include <sys/xattr.h>
#include <pwd.h>

#define LEGAL "al"

typedef struct s_args {
	char *flags;
	char **files;
	char **dirs;
	char **not_valid;
} t_args;

typedef struct s_dirs {
	char *dir;
	struct s_dirs_entry *entry_dir;
    int max_group; // максимальная длина имени группы (нужно для рассчета расстояния между файлами)
    int max_user; // максимальная длина имени юзера (нужно для рассчета расстояния между файлами)
    int max_size;// максимальная длина байт (нужно для рассчета расстояния между файлами)
    int max_link; // максимальное количетсво линки(нужно для рассчета расстояния между файлами)
	int total;
    int amount_d_data;
	struct s_dirs *next;
} t_dirs;

typedef struct s_dirs_entry {
	char *d_name;
	int d_namlen;
	int d_type;
    struct file *stat;
	struct s_dirs_entry *next;
} t_dirs_entry;

typedef enum s_del_args_struct {
	NOTHING,
	FLAGS,
	FILES,
	DIRS,
	NOT_VALID
} t_del_args_struct;

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

t_args *mx_sort_args(int argc, char **argv);
t_dirs *mx_get_dir_entry(t_args *args);
void mx_get_max_value(t_dirs *dir);
char *mx_get_flags(t_args *args, int *index, int argc, char **argv);
void mx_args_to_struct(int index, int argc, char **argv, t_args *args);
void mx_print_not_valid(char *data);
void mx_del_str_arr(char **arr);
void mx_del_args_struct(t_args *args, int item);
DIR *mx_check_on_access(char *data);
void mx_del_dirs_struct(t_dirs *dirs);
int mx_arr_size(char **arr);
void mx_print_ls_multy_colomn(char **data);
char **mx_get_data_from_struct(t_dirs *dirs, char symbol);
int mx_get_window_size();
char **mx_sort_data(t_dirs *dirs, char symbol);
void mx_print_ls_monocolomn(char **data);
void mx_print(t_args *args, t_dirs *dirs_entry, char symbol, void (*print_ls)(char **));
t_file *mx_get_stat(char *data, int *total);
void mx_get_data_info(t_file *stat, char* file, int *total);
void mx_print_ls_l(t_args *args, t_dirs *dirs);

//***************************** Utils pack *******************************


typedef struct general{
    t_file  *array_p; // указатель на массив структур
    //int max_file; // максимальная длина имени файла (нужно для рассчета расстояния между файлами)
    int max_group; // максимальная длина имени группы (нужно для рассчета расстояния между файлами)
    int max_user; // максимальная длина имени юзера (нужно для рассчета расстояния между файлами)
    int max_size;// максимальная длина байт (нужно для рассчета расстояния между файлами)
    int max_link; // максимальное количетсво линки(нужно для рассчета расстояния между файлами)
    int sum_blocks; // количество выделнных блоков, принтуется в самом начале флага -л
} st_general;

//-----------------------------------------------------------------------
void print_ls_l(char **data);
void mx_output_l(st_general *gnr, int argc);
char* mx_permission(char* file, t_file *file_st);
void mx_get_inform(st_general *gnr, char* file, int i);
//-----------------------------------------------------------------------                                       

#endif
