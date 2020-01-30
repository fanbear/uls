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

void mx_get_data_info(t_file *stat, char* file, int *total) {
	lstat(file, &stat->buf);
	*total += stat->buf.st_blocks;
	stat->permiss = mx_permission(file, stat);
	stat->nlink = mx_itoa(stat->buf.st_nlink);
	stat->pw = getpwuid(stat->buf.st_uid);
	stat->user_name = mx_strdup(stat->pw->pw_name);
	stat->group_name = mx_itoa(stat->pw->pw_gid);
	stat->file_size = mx_itoa(stat->buf.st_size);
	stat->time1 = get_time(stat);
	stat->file_name = mx_strdup(file);
}
