// для заполнение информации о файле 
// буду использовать после парсинга для сбора атрибутов файла ( заполнение структуры t_file) 

//передаю основную структуру, i-й элемент и файл из консоли
#include "uls.h"

static char* get_time(t_file *file_st) {
	char* str = ctime(&file_st->buf.st_atime);
	char* tmp_str= NULL;
     char *time1 = NULL;
     char* res = NULL;
     time_t current = time(0);

     if (current - file_st->buf.st_atime >= 31536000 / 2) {
            str += 4;
            time1 = mx_strndup(str, 6);
            str += 15;
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

static void free_lol(t_file *file_st) {
	free(file_st->file_name);
	free(file_st->permiss);
	free(file_st->user_name);
	free(file_st->group_name);
	free(file_st);
}
void mx_get_inform(char* file) {
	t_file *file_st = (t_file*)malloc(sizeof(t_file));
	char* time1 = get_time(file_st);

	file_st->file_name = mx_strdup(file);
	lstat(file, &file_st->buf);
	file_st->pw = getpwuid(file_st->buf.st_uid);
	file_st->permiss = mx_permission(file, file_st);
	mx_printstr(file_st->permiss);
	file_st->user_name = mx_strdup(file_st->pw->pw_name);
	mx_printstr(file_st->user_name);
	file_st->group_name = mx_itoa(file_st->pw->pw_gid);
	mx_printstr(file_st->group_name);
	file_st->file_size = file_st->buf.st_size;
	mx_printint(file_st->file_size);
	file_st->nlink = file_st->buf.st_nlink;
	mx_printint(file_st->buf.st_nlink);
	mx_printstr(time1);
	free(time1);
	printf("\n");
	free_lol(file_st);
}
