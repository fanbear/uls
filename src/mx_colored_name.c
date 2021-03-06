#include "uls.h"

static t_file *get_stat(t_args *args, char *data, char *path) {
    t_file *stat = NULL;
    char *temp_path = (path) ? mx_create_path(path, data) : mx_strdup(data);

    stat = mx_get_stat(args, temp_path);
    mx_strdel(&temp_path);
    return stat;
}

void mx_colored_name(t_args *args, char *name, char *path) {
    if (isatty(1) && args->fl[1]) {
        t_file *stat = get_stat(args, name, path);

        mx_color_output(stat);
        mx_karetka_files(name);
        mx_printstr(name);
        mx_printstr(MX_COLOR_RESET);
        mx_del_stat_struct(stat);
    }
    else {
        mx_karetka_files(name);
        mx_printstr(name);
    }
}
