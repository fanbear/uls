#include "uls.h"

static void push_arg_to_arr(char **arr, char *arg);
static int get_arg_info(char **argv, int index);
static void parsing(char **files, char **dirs, char **n_valid, t_args *args);
static void mem_alloc_struct(t_args *args, char **files,
char **dirs, char **n_valid);

void mx_args_to_struct(int index, int argc, char **argv, t_args *args) {
    char **files = (char **)malloc(sizeof(char *) * (argc - 1));
    char **dirs = (char **)malloc(sizeof(char *) * (argc + 1));
    char **not_valid = (char **)malloc(sizeof(char *) * (argc - 1));

    files[0] = NULL;
    dirs[0] = (argc == 1) ? mx_strdup(".") : NULL;
    dirs[1] = NULL;
    not_valid[0] = NULL;
    for (; index < argc; index++) {
        if (get_arg_info(argv, index) == -1)
            push_arg_to_arr(not_valid, argv[index]);
        else if (get_arg_info(argv, index) == 0)
            push_arg_to_arr(files, argv[index]);
        else
            push_arg_to_arr(dirs, argv[index]);
    }
    parsing(files, dirs, not_valid, args);
    mx_del_str_arr(files);
    mx_del_str_arr(dirs);
    mx_del_str_arr(not_valid);
}

static void push_arg_to_arr(char **arr, char *arg) {
    int i = 0;

    while(arr[i]) {
        i++;
    }
    arr[i] = mx_strdup(arg);
    arr[i + 1] = NULL;
}

static int get_arg_info(char **argv, int index) {
    DIR *dir = opendir(argv[index]);

    if (!dir) {
        int fd = open(argv[index], O_RDONLY);

        if (fd < 0)
            return -1;
        else {
            close(fd);
            return 0;
        }
    }
    else {
        closedir(dir);
        return 1;
    }
}

static void parsing(char **files, char **dirs, char **n_valid, t_args *args) {
    int i = 0;
    int j = 0;
    int k = 0;

    mem_alloc_struct(args, files, dirs, n_valid);
    for (; files[i] || dirs[j] || n_valid[k];) {
        if (files[i]) {
            push_arg_to_arr(args->files, files[i]);
            i++;
        }
        if (dirs[j]) {
            push_arg_to_arr(args->dirs, dirs[j]);
            j++;
        }
        if (n_valid[k]) {
            push_arg_to_arr(args->not_valid, n_valid[k]);
            k++;
        }
    }
}

static void mem_alloc_struct(t_args *args, char **files,
char **dirs, char **n_valid) {
    args->files = malloc(sizeof(char *) * (mx_arr_size(files) + 1));
    args->dirs = malloc(sizeof(char *) * (mx_arr_size(dirs) + 1));
    args->not_valid = malloc(sizeof(char *) * (mx_arr_size(n_valid) + 1));
    args->files[0] = NULL;
    args->dirs[0] = NULL;
    args->not_valid[0] = NULL;
}
