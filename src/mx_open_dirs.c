#include "uls.h"

static void get_rec_entry_dirs(t_args *args, char *dir_n);
static int count_el(t_args *args, char *dir_n);
static char **data_in_dir(t_args *args, char *dir_n);

void mx_open_dirs(t_args *args) {
    for (int i = 0; args->dirs[i]; i++) {
        t_dirs *dirs = mx_data_to_dirs_struct(args, args->dirs[i]);
        if (mx_arr_size(args->dirs) > 1
            || args->not_valid[0] || args->files[0]) {
            mx_karetka_files(dirs->dir);
            mx_printstr(dirs->dir);
            mx_printstr(":\n");
        }
        mx_filter_print(args, dirs);
        if (args->fl[2])
            get_rec_entry_dirs(args, args->dirs[i]);
        if (args->dirs[i + 1])
            mx_printstr("\n");
        mx_del_dirs_struct(dirs);
    }
}

static void get_rec_entry_dirs(t_args *args, char *dir_n) {
    DIR *dir = opendir(dir_n);

    if (dir) {
        char **res_data = data_in_dir(args, dir_n);

        mx_sort_data(args, res_data);
        for (int j = 0; res_data[j]; j++) {
            dir = opendir(dir_n);
            t_dirs *dirs = mx_data_to_dirs_struct(args, res_data[j]);

            mx_printstr("\n");
            mx_karetka_files(dirs->dir);
            mx_printstr(dirs->dir);
            mx_printstr(":\n");
            mx_filter_print(args, dirs);
            mx_del_dirs_struct(dirs);
            if (dirs->entry_dir)
                get_rec_entry_dirs(args, res_data[j]);
            mx_strdel(&res_data[j]);
        }
        closedir(dir);
        free(res_data);
        res_data = NULL;

    }
}

static char **data_in_dir(t_args *args, char *dir_n) {
    DIR *dir = opendir(dir_n);
    struct dirent *entry;
    char **res = (char **)malloc(sizeof (char *) * (count_el(args, dir_n) + 1));
    struct stat buf;

    while ((entry = readdir(dir)) != NULL) {
        char *path = mx_create_path(dir_n, entry->d_name);

        lstat(path, &buf);
        mx_strdel(&path);
        if (S_ISDIR(buf.st_mode)) {
            if ((!args->fl[3] && entry->d_name[0] == '.')
                || !mx_strcmp(entry->d_name, ".")
                || !mx_strcmp(entry->d_name, ".."))
                continue ;
            char *path1 = mx_create_path(dir_n, entry->d_name);

            *res++ = mx_strdup(path1);
            mx_strdel(&path1);
        }
    }
    *res = NULL;
    closedir(dir);
    return res - count_el(args, dir_n);
}

static int count_el(t_args *args, char *dir_n) {
    int count = 0;
    DIR *dir = opendir(dir_n);
    struct dirent *entry;
    struct stat buf;

    while ((entry = readdir(dir)) != NULL) {
        char *path = mx_create_path(dir_n, entry->d_name);

        lstat(path, &buf);
        mx_strdel(&path);
        if (S_ISDIR(buf.st_mode)) {
            if ((!args->fl[3] && entry->d_name[0] == '.')
            || !mx_strcmp(entry->d_name, ".")
            || !mx_strcmp(entry->d_name, ".."))
            continue ;
            count++;
        }
    }
    closedir(dir);
    return count;
}
