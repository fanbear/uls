#include "uls.h"

static void stat_checking(char *data, struct stat *buf);

DIR *mx_check_on_access(char *data) {
	DIR *dir = opendir(data);
	struct stat *buf = NULL;

	if (errno == 13) {
		stat_checking(data, buf);
		if (dir)
			closedir(dir);
		return NULL;
	}
	else if (errno == 20) {
		int file = open(data, O_RDONLY);

		if (errno == 13) 
			stat_checking(data, buf);
		close(file);
		return NULL;
	}
	return dir;
}

static void stat_checking(char *data, struct stat *buf) {
	int lstat_h = lstat(data, buf);
	char **parse = mx_strsplit(data, '/');

	free(buf);
	buf = NULL;
	if (lstat_h)
		mx_print_not_valid(data);
	else 
		mx_print_not_valid(parse[mx_arr_size(parse) - 1]);
}
