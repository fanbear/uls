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

#define LEGAL "a"

typedef struct s_args {
	char *flags;
	char **files;
	char **dirs;
	char **not_valid;
} t_args;

typedef struct s_dirs {
	char *dir;
	struct s_dirs_entry *entry_dir;
	int amount_d_data;
	struct s_dirs *next;
} t_dirs;

typedef struct s_dirs_entry {
	char *d_name;
	int d_namlen;
	int d_type;
	struct s_dirs_entry *next;
} t_dirs_entry;

char *mx_get_flags(int *index, int argc, char **argv);
void mx_args_to_struct(int index, int argc, char **argv, t_args *args);
void mx_print_not_valid(int amount, char **argv);
void mx_del_str_arr(char **arr);
int mx_arr_size(char **arr);
void mx_print_ls_multy_colomn(char **data);
void mx_del_struct(t_dirs *dirs);
char **mx_get_data_from_struct(t_dirs *dirs, char symbol);
int mx_get_window_size();
char **mx_sort_data(t_dirs *dirs, char symbol);
void mx_print_ls_monocolomn(char **data);
void mx_print(t_args *args, t_dirs *dirs_entry, char symbol, void (*print_ls)(char **));

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
