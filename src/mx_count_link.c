#include "uls.h"

int mx_count_link(const char* file) {
	struct stat buf;
	int link = 0;

	lstat(file, &buf);
	link = buf.st_nlink;
	return link;
}
