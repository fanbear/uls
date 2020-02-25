#include "uls.h"

static int count_el(t_args *args, char *dir_n) {
    int count = 0;
    DIR *dir = opendir(dir_n);
    struct dirent *entry;

    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_DIR) {
            if ((!args->fl[3] && entry->d_name[0] == '.')
            || !mx_strcmp(entry->d_name, ".")
            || !mx_strcmp(entry->d_name, ".."))
            continue;
            count++;
        }
    }
    closedir(dir);
    return count;
}

static char **data_in_dir(DIR *dir, t_args *args, char *dir_n) {
    struct dirent *entry;
    char **res = (char**)malloc(sizeof(char*) * (count_el(args, dir_n) + 1));

    dir = opendir(dir_n);
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_DIR) {
            if ((!args->fl[3] && entry->d_name[0] == '.')
                || !mx_strcmp(entry->d_name, ".")
                || !mx_strcmp(entry->d_name, ".."))
                continue;
            char *path1 = mx_create_path(dir_n, entry->d_name);

            *res++ = mx_strdup(path1);
            mx_strdel(&path1);
        }
    }
    *res = NULL;
    closedir(dir);
    return res - count_el(args, dir_n);
}

static void get_rec_entry_dirs(t_args *args, char *dir_n) {
    DIR *dir = NULL;
    char **res_data = data_in_dir(dir, args, dir_n);

    mx_sort_data(args, res_data);
    for (int j = 0; res_data[j]; j++) {
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
    free(res_data);
    res_data = NULL;
}

void mx_open_dirs(t_args *args) {
    for (int i = 0; args->dirs[i]; i++) {
        DIR *dir = opendir(args->dirs[i]);
        t_dirs *dirs = mx_data_to_dirs_struct(args, args->dirs[i]);

        if (mx_arr_size(args->dirs) > 1
            || args->not_valid[0] || args->files[0]) {
            mx_karetka_files(dirs->dir);
            mx_printstr(dirs->dir);
            mx_printstr(":\n");
        }
        mx_filter_print(args, dirs);
        if (args->fl[2] && dir)
            get_rec_entry_dirs(args, args->dirs[i]);
        if (args->dirs[i + 1])
            mx_printstr("\n");
        mx_del_dirs_struct(dirs);
        if (dir)
            closedir(dir);
    }
}

