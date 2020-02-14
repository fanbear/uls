#include "uls.h"

static void stat_checking(int mult, char *data, struct stat *buf);
static char *r_find(char *data);

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
		stat_checking(mult, data, buf);
		return -1;
	}
	free(buf);
	buf = NULL;
	if (dir)
		closedir(dir);
	return 0;
}

static void stat_checking(int mult, char *data, struct stat *buf) {
	int lstat_h = lstat(data, buf);
	char *parse = r_find(data);

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
		perror(parse);
		errno = 0;
	}
}

static char *r_find(char *data) {
	int lenth = mx_strlen(data);

	while (data[lenth - 1] != '/')
		lenth--;
	return &data[lenth];
}
