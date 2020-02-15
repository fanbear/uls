#include "uls.h"

static void get_time(t_file *file_st);
static int chislo(int c);
static char* major_minor_size(t_file *file_st);

t_file *mx_get_stat(char *data) {
    t_file *stat = malloc(sizeof(t_file));
    struct group *group;

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
   	stat->rdev = major_minor_size(stat);
	stat->file_size = mx_itoa(stat->buf.st_size);
	get_time(stat);
	stat->file_name = mx_strdup(data);
    stat->name_link = mx_strnew(stat->buf.st_size);
    readlink(data, stat->name_link, 1024);
    return stat;
}

static void get_time(t_file *file_st) {
	char* str = ctime(&file_st->buf.st_mtime);
	time_t current = time(NULL);

    str += 4;
	if (current - file_st->buf.st_mtime >= 31536000 / 2) {
        file_st->time1 = mx_strndup(str, 6);
		file_st->time2 = mx_strndup(str + 15, 5);
	}
	else {
		file_st->time1 = mx_strndup(str, 6);
        file_st->time2 = mx_strndup(str + 6, 6);
	}
}

static char* major_minor_size(t_file *file_st) {
	char* minor_major = malloc(8);
    char* lol = ", ";
    char* tmp = NULL;
    char* hex = NULL;
    int min = 0;
    int maj = 0;

	maj = chislo(MAJOR(file_st->buf.st_rdev));
	for (int y = 0; y < 3 - maj; y++)
		minor_major[y] = ' ';
	minor_major = mx_strcat(minor_major, mx_itoa(MAJOR(file_st->buf.st_rdev)));
	minor_major = mx_strcat(minor_major, lol);

	if (MINOR(file_st->buf.st_rdev) < 255) {
		min = chislo(MINOR(file_st->buf.st_rdev));
		tmp = malloc(3);
		for (int m = 0; m < 3 - min; m++)
			tmp[m] = ' ';
		tmp = mx_strcat(tmp, mx_itoa(MINOR(file_st->buf.st_rdev)));
	}
	else {
		tmp = malloc(8);
		int i = 2;
		tmp[0] = '0';
		tmp[1] = 'x';
		hex = mx_nbr_to_hex(MINOR(file_st->buf.st_rdev));
		for (int y = 0; y < 8 - mx_strlen(hex); y++) {
			tmp[i] = '0';
			i++;
		}
		tmp = mx_strcat(tmp, hex);
	}
	minor_major = mx_strcat(minor_major, tmp);
	return minor_major;
}

static int chislo(int c) {
	int i = 0;

	if (c == 0)
		i = 1;
	for (; c > 0; i++)
		c = c / 10;
	return i;
}
