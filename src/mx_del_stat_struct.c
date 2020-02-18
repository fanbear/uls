#include "uls.h"

void mx_del_stat_struct(t_file *stat) {
    if (stat) {
        mx_strdel(&stat->permiss);
        mx_strdel(&stat->file_name);
        mx_strdel(&stat->user_name);
        mx_strdel(&stat->group_name);
        mx_strdel(&stat->time1);
        mx_strdel(&stat->nlink);
        mx_strdel(&stat->file_size);
        mx_strdel(&stat->time2);
        mx_strdel(&stat->name_link);
        mx_strdel(&stat->rdev);
        free(stat->pw);
        free(stat);
        stat = NULL;
    }
}
