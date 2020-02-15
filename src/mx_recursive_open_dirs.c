#include "uls.h"

static void get_entry_dirs(t_args *args, char *dir_n, char **res, int *index);

void mx_recursive_open_dirs(t_args *args) {
    int index = 0;
    char **res = (char **)malloc(sizeof(char *) * 30000000);

    for (int i = 0; args->dirs[i]; i++) {
        res[index++] = mx_strdup(args->dirs[i]);
        get_entry_dirs(args, args->dirs[i], res, &index);
    }
    res[index] = NULL;
    mx_del_str_arr(args->dirs);
    args->dirs = (char **)malloc(sizeof(char *) * (index + 1));
    for (int i = 0; res[i]; i++) {
        args->dirs[i] = mx_strdup(res[i]);
    }
    args->dirs[index] = NULL;
    mx_del_str_arr(res);
}

static void get_entry_dirs(t_args *args, char *dir_n, char **res, int *index) {
    DIR *dir;
    struct dirent *entry;

    if (!(dir = opendir(dir_n)))
        return;
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_DIR) {
            if ((!args->fl[3] && entry->d_name[0] == '.')
                || !mx_strcmp(entry->d_name, ".")
                || !mx_strcmp(entry->d_name, ".."))
                continue;
            char *d_name = mx_strjoin(dir_n, "/");

            res[*index] = mx_strjoin(d_name, entry->d_name);
            mx_strdel(&d_name);
            *index = *index + 1;
            if (res[*index - 1])
                get_entry_dirs(args, res[*index - 1], res, index);
        }
    }
    closedir(dir);
}
