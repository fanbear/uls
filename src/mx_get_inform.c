// для заполнение информации о файле 
// буду использовать после парсинга для сбора атрибутов файла ( заполнение структуры t_file) 

//передаю основную структуру, i-й элемент и файл из консоли
void mx_get_inform(st_general *gnr, int i, char* file) {
	gnr->struct_p[i].file = mx_strdup(file_name);
	lstat(m_s->struct_p[i].stat);
	mx_permissoin(file);
	gnr->struct_p[i].uid_name = mx_strdup(user_uid(m_s->struct_p[i].stat.st_uid));
	gnr->struct_p[i].gid_name = mx_strdup(user_gid(m_s->struct_p[i].stat.st_gid));
	gnr->struct_p[i].file_size = m_s->struct_p[i].stat.st_size;
	gnr->struct_p[i].nlink = m_s->struct_p[i].stat.st_nlink;
}