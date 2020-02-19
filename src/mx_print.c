#include "uls.h"

static void many_dirs(char **data, t_args *args, t_dirs *dirs,
    void (*print)(char **, t_args *, char *dir));
static void print_file(t_args *args, t_dirs *dirs, 
    void (*print)(char **, t_args *, char *dir));
static void file_and_dir(char **data, t_args *args, t_dirs *dirs,
    void (*print)(char **, t_args *, char *dir));

void mx_print(t_args *args, t_dirs *dirs, 
    void (*print_ls)(char **, t_args *, char *dir)) {
    print_file(args, dirs, print_ls);
    if (dirs) {
        char **data = NULL;

        if (dirs->next || args->not_valid[0] || args->files[0]) {
            while (dirs) {
                if (!mx_check_on_access(1, dirs->dir, args))
                    many_dirs(data, args, dirs, print_ls);
                dirs = dirs->next;
                if (dirs)
                    mx_printchar('\n');
            }
        }
        else
            file_and_dir(data, args, dirs, print_ls);
        }
}

static void many_dirs(char **data, t_args *args, t_dirs *dirs,
    void (*print)(char **, t_args *, char *dir)) {
    data = mx_get_data_from_struct(dirs);

    if (args->fl[2] && args->dirs_num == 1) {
        args->dirs_num = 0;
    } else {
        mx_printstr(dirs->dir);
        mx_printstr(":\n");
    }
    if (data) {
        print(data, args, dirs->dir);
        mx_del_str_arr(data);
    }

}

static void print_file(t_args *args, t_dirs *dirs, 
    void (*print)(char **, t_args *, char *dir)) {
    if (args->files[0]) {
        (*print)(args->files, args, NULL);
        if (dirs)
            mx_printchar('\n');
    }
}

static void file_and_dir(char **data, t_args *args, t_dirs *dirs,
    void (*print)(char **, t_args *, char *dir)) {
    if (!mx_check_on_access(0, dirs->dir, args)) {
        data = mx_get_data_from_struct(dirs);
        if (data) {
            (*print)(data, args, dirs->dir);
            mx_del_str_arr(data);
        }
    }
}


