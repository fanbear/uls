#include "uls.h"

static t_file *get_stat(t_args *args, char *data, char *path);

void mx_colored_name(t_args *args, char *name, char *path) {
    if (isatty(1) && args->fl[1]) {
        t_file *stat = get_stat(args, name, path);

        mx_color_output(stat);
        mx_printstr(name);
        mx_printstr(COLOR_RESET);
        mx_del_stat_struct(stat);
    }
    else
        mx_printstr(name);
}


static t_file *get_stat(t_args *args, char *data, char *path) {
    t_file *stat = NULL;

    if (path) {
        path = mx_strjoin(path, "/");
        data = mx_strjoin(path, data);
    }
    stat = mx_get_stat(args, data);
    mx_strdel(&path);
    mx_strdel(&data);
    return stat;
}
