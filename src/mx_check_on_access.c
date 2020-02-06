#include "uls.h"

static void stat_checking(int mult, char *data, struct stat *buf);

int mx_check_on_access(int mult, char *data) {
	DIR *dir = opendir(data);
	struct stat *buf = malloc(sizeof(struct stat));

	if (errno == 13) {
		stat_checking(mult, data, buf);
		if (dir)
			closedir(dir);
		return -1;
	}
	else if (errno == 20) {
		int file = open(data, O_RDONLY);

		if (errno == 13)
			stat_checking(mult, data, buf);
		close(file);
		return -1;
	}
	free(buf);
	buf = NULL;
	closedir(dir);
	return 0;
}

static void stat_checking(int mult, char *data, struct stat *buf) {
	int lstat_h = lstat(data, buf);
	char **parse = mx_strsplit(data, '/');

	free(buf);
	buf = NULL;
	if (lstat_h) {
		write(2, "uls: ", 5);
		perror(data);
		errno = 0;
	}
	else {
		if (mult) {
			mx_printstr(data);
			mx_printstr(":\n");
		}
		write(2, "uls: ", 5);
		perror(parse[mx_arr_size(parse) - 1]);
		errno = 0;
	}
}
