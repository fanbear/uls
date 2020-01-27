#include "uls.h"


 static void type(char* str, t_file *file_st) {
 	if ((file_st->buf.st_mode & S_IFMT) == S_IFREG)
		str[0] = '-';
	else if ((file_st->buf.st_mode & S_IFMT) == S_IFLNK)
		str[0] = 'l';
	else if ((file_st->buf.st_mode & S_IFMT) == S_IFIFO)
		str[0] = 'p';
	else if ((file_st->buf.st_mode & S_IFMT) == S_IFCHR)
		str[0] = 'c';
	else if ((file_st->buf.st_mode & S_IFMT) == S_IFDIR)
		str[0] = 'd';
	else if ((file_st->buf.st_mode & S_IFMT) == S_IFSOCK)
		str[0] = 's';
	else if ((file_st->buf.st_mode & S_IFMT) == S_IFBLK)
		str[0] = 'b';
 }

 static void perm_for_user(t_file *file_st, char* str) {
 	if (file_st->buf.st_mode & S_IRUSR)
		str[1] = 'r';
	else
		str[1] = '-';
	if (file_st->buf.st_mode & S_IWUSR)
		str[2] = 'w';
	else
		str[2] = '-';
	if (file_st->buf.st_mode & S_IXUSR)
		str[3] = 'x';
	else
		str[3] = '-';
 }

 static void perm_for_group(t_file *file_st, char* str) {
 	if (file_st->buf.st_mode & S_IRGRP)
		str[4] = 'r';
	else
		str[4] = '-';
	if (file_st->buf.st_mode & S_IWGRP)
		str[5] = 'w';
	else
		str[5] = '-';
	if (file_st->buf.st_mode & S_IXGRP)
		str[6] = 'x';
	else
		str[6] = '-';
 }

 static void perm_for_other(t_file *file_st, char* str) {
 	if (file_st->buf.st_mode & S_IROTH)
		str[7] = 'r';
	else
		str[7] = '-';
	if (file_st->buf.st_mode & S_IWOTH)
		str[8] = 'w';
	else
		str[8] = '-';
	if (file_st->buf.st_mode & S_IXOTH)
		str[9] = 'x';
	else
		str[9] = '-';
 }
char* mx_permission(char* file, t_file *file_st) {
	char* str = mx_strnew(11);
	size_t value = 0;
	value = listxattr(file, NULL, 0, XATTR_NOFOLLOW);
	printf("%lu\n",value );
	printf("%s\n",file);
	acl_t acl = NULL;

	type(str, file_st);
	perm_for_user(file_st, str);
	perm_for_group(file_st, str);
	perm_for_other(file_st, str);
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
		str[10] = '\0';
	return str;
}
