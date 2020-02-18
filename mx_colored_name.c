#include "uls.h"

static t_file *get_stat(char *data, char *path);

void mx_colored_name(int flag_g, char *name, char *path) {
    t_file *stat = get_stat(name, path);

    if (flag_g) {
        mx_printstr(stat->color);
        mx_printstr(name);
        mx_printstr(COLOR_RESET);
    }
    else
        mx_printstr(name);
}


static t_file *get_stat(char *data, char *path) {
    if (path) {
        path = mx_strjoin(path, "/");
        data = mx_strjoin(path, data);
    }
    return mx_get_stat(data);
}
