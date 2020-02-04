#include "uls.h"

static char* get_time(t_file *file_st);

t_file *mx_get_stat(char *data) {
    t_file *stat = malloc(sizeof(t_file));
    struct group *group;

    // mx_check_on_access(data);
    lstat(data, &stat->buf);
	stat->permiss = mx_permission(data, stat);
	stat->nlink = mx_itoa(stat->buf.st_nlink);
	stat->pw = getpwuid(stat->buf.st_uid);
	stat->user_name = mx_strdup(stat->pw->pw_name);
    group = getgrgid(stat->buf.st_gid);
    if (group != NULL)
        stat->group_name = mx_strdup(group->gr_name);
    else
        stat->group_name = mx_itoa(stat->buf.st_gid);
	stat->file_size = mx_itoa(stat->buf.st_size);
	stat->time1 = get_time(stat);
	stat->file_name = mx_strdup(data);
    return stat;
}

static char* get_time(t_file *file_st) {
	char* str = ctime(&file_st->buf.st_mtime);
	char* tmp_str= NULL;
	char *time1 = NULL;
	char* res = NULL;
	time_t current = time(0);

	if (current - file_st->buf.st_atime >= 31536000 / 2) {
		str += 4;
		time1 = mx_strndup(str, 6);
		str += 14;
		str = mx_strndup(str, 6);
		res = mx_strjoin(time1, str);
	}
	else {
		str += 4;
		res = mx_strndup(str, 12);
	}
	mx_strdel(&time1);
	mx_strdel(&tmp_str);
	return res;
}
