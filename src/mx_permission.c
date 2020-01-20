#include <stdio.h>
#include <time.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/xattr.h>
#include <sys/types.h>
#include <sys/acl.h>

// переделать под статики, весь функционал вывода прав доступа работает
char* mx_permission(const char* file) {
	char* str = malloc(sizeof(char)* 11);
	struct stat buf;
	lstat(file, &buf);
	size_t value = 0;
	char* key = NULL;
	acl_t acl = NULL;

	if ((buf.st_mode & S_IFMT) == S_IFREG)
		str[0] = '-';
	else if ((buf.st_mode & S_IFMT) == S_IFLNK)
		str[0] = 'l';
	else if ((buf.st_mode & S_IFMT) == S_IFIFO)
		str[0] = 'p';
	else if ((buf.st_mode & S_IFMT) == S_IFCHR)
		str[0] = 'c';
	else if ((buf.st_mode & S_IFMT) == S_IFDIR)
		str[0] = 'd';
	else if ((buf.st_mode & S_IFMT) == S_IFSOCK)
		str[0] = 's';
	else if ((buf.st_mode & S_IFMT) == S_IFBLK)
		str[0] = 'b';

	if (buf.st_mode & S_IRUSR)
		str[1] = 'r';
	else
		str[1] = '-';
	if (buf.st_mode & S_IWUSR)
		str[2] = 'w';
	else
		str[2] = '-';
	if (buf.st_mode & S_IXUSR)
		str[3] = 'x';
	else
		str[3] = '-';
	if (buf.st_mode & S_IRGRP)
		str[4] = 'r';
	else
		str[4] = '-';
	if (buf.st_mode & S_IWGRP)
		str[5] = 'w';
	else
		str[5] = '-';
	if (buf.st_mode & S_IXGRP)
		str[6] = 'x';
	else
		str[6] = '-';
	if (buf.st_mode & S_IROTH)
		str[7] = 'r';
	else
		str[7] = '-';
	if (buf.st_mode & S_IWOTH)
		str[8] = 'w';
	else
		str[8] = '-';
	if (buf.st_mode & S_IXOTH)
		str[9] = 'x';
	else
		str[9] = '-';
	value = listxattr(file, NULL, 0, XATTR_NOFOLLOW);
	if (value > 0) {
		str[10] = '@';
		return str;
	}
	acl = acl_get_file(file, ACL_TYPE_EXTENDED);
	if ( acl != NULL) {
		str[10] = '+';
		acl_free(acl);
	}
	else 
		str[10] = ' ';
	return str;
}
