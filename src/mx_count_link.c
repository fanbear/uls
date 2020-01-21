#include <stdio.h>
#include <time.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/xattr.h>
#include <sys/types.h>
#include <sys/acl.h>

int mx_count_link(const char* file) {
	struct stat buf;
	int link = 0;

	lstat(file, &buf);
	link = buf.st_nlink;
	return link;
}