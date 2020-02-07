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
#include <grp.h>

#define LEGAL "al"

typedef struct s_args {
	char  *flags;
	int    fl[2];
	char **files;
	char **dirs;
	char **not_valid;
} t_args;

typedef struct s_dirs {
	char                *dir;
	struct s_dirs_entry *entry_dir;
    int                  max_group; // максимальная длина имени группы (нужно для рассчета расстояния между файлами)
    int                  max_user; // максимальная длина имени юзера (нужно для рассчета расстояния между файлами)
    int                  max_size;// максимальная длина байт (нужно для рассчета расстояния между файлами)
    int                  max_link; // максимальное количетсво линки(нужно для рассчета расстояния между файлами)
	int                  max_time;
	int                  total;
    int                  amount_d_data;
	struct s_dirs       *next;
} t_dirs;

typedef struct s_dirs_entry {
	char                *d_name;
	int                  d_namlen;
	struct file         *stat;
	struct s_dirs_entry *next;
} t_dirs_entry;


typedef struct s_files {
	struct s_file_entry *entry_file;
    int                  max_group; // максимальная длина имени группы (нужно для рассчета расстояния между файлами)
    int                  max_user; // максимальная длина имени юзера (нужно для рассчета расстояния между файлами)
    int                  max_size; // максимальная длина байт (нужно для рассчета расстояния между файлами)
    int                  max_link; // максимальное количетсво линки(нужно для рассчета расстояния между файлами)
	int                  max_time;
} t_files;

typedef struct s_file_entry {
	char                *files;
	struct file         *stat;
	struct s_file_entry *next;
} t_file_entry;


typedef enum s_del_args_struct {
	NOTHING,
	FLAGS,
	FILES,
	DIRS,
	NOT_VALID
} t_del_args_struct;

typedef struct file { //структура для файлов
    char          *permiss;
	char          *file_name;
	char          *user_name;
	char          *group_name;
	char          *time1;
	char          *nlink; //кл-во линков
	char          *file_size;
	char          *time2;
	char          *name_link; //  если файл = линк для принта //пока не пользуюсь
    time_t         a_time; //*временные данные, для реализации разных флагов*/
    time_t         m_time;
    time_t         c_time;
	blkcnt_t       blocks;
	struct stat    buf;
	struct passwd *pw;
} t_file;

t_args        *mx_sort_args(int argc, char **argv);
t_dirs        *mx_get_dir_entry(t_args *args);
void           mx_get_max_value_in_dirs(t_dirs *dir);
void           mx_get_max_value_in_files(t_files *files);
char          *mx_get_flags(t_args *args, int *index, int argc, char **argv);
void           mx_args_to_struct(int index, int argc, char **argv, t_args *args);
void           mx_print_not_valid(char *data);
void           mx_del_str_arr(char **arr);
void           mx_del_args_struct(t_args *args, int item);
int            mx_check_on_access(int mult, char *data);
void           mx_del_dirs_struct(t_dirs *dirs);
int            mx_arr_size(char **arr);
void           mx_print_ls_multy_colomn(char **data);
char         **mx_get_data_from_struct(t_dirs *dirs);
int            mx_get_window_size();
char         **mx_sort_data(t_dirs *dirs);
void           mx_print_ls_monocolomn(char **data);
void           mx_print(t_args *args, t_dirs *dirs, void (*print_ls)(char **));
t_file        *mx_get_stat(char *data);
void           mx_get_data_info(t_file *stat, char* file);
void           mx_print_ls_l(t_args *args, t_dirs *dirs);
t_dirs_entry  *mx_sort_content(t_dirs_entry *entry_dir);
char          *mx_permission(char* file, t_file *file_st);

#endif
