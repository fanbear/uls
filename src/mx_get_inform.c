// для заполнение информации о файле
// буду использовать после парсинга для сбора атрибутов файла ( заполнение структуры t_file)

//передаю основную структуру, i-й элемент и файл из консоли
#include "uls.h"

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

// static void free_lol(t_file *file_st) {
// 	free(file_st->file_name);
// 	free(file_st->permiss);
// 	free(file_st->user_name);
// 	free(file_st->group_name);
// 	free(file_st);
// }
void mx_get_inform(st_general *gnr, char* file, int i) {
	// printf("\t\tfile = \"%s\"\n", file);
	// printf("lstat = %d\n", lstat(file, &gnr->array_p[i].buf));
	lstat(file, &gnr->array_p[i].buf);
	gnr->array_p[i].blocks = gnr->array_p[i].buf.st_blocks;
	// printf("\t\t\tfile_blocks = \"%lld\"\n", gnr->array_p[i].buf.st_blocks);
	gnr->array_p[i].permiss = mx_permission(file, &gnr->array_p[i]);
	// printf("\t\t\tfile_permiss = \"%hu\"\n", gnr->array_p[i].buf.st_mode);
	gnr->array_p[i].nlink = mx_itoa(gnr->array_p[i].buf.st_nlink);
	gnr->array_p[i].pw = getpwuid(gnr->array_p[i].buf.st_uid);
	gnr->array_p[i].user_name = mx_strdup(gnr->array_p[i].pw->pw_name);
	gnr->array_p[i].group_name = mx_itoa(gnr->array_p[i].pw->pw_gid);
	gnr->array_p[i].file_size = mx_itoa(gnr->array_p[i].buf.st_size);
	gnr->array_p[i].time1 = get_time(&gnr->array_p[i]);
	gnr->array_p[i].file_name = mx_strdup(file);
}
