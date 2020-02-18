#include "uls.h"

static t_dirs *parse(t_args *args, t_dirs *dirs, char *dir_name);
static t_dirs *data_to_dirs_struct(t_args *args, char *dir_name);
static char **data_to_arr(t_args *args, DIR *dir);

t_dirs *mx_get_dir_entry(t_args *args) {
	t_dirs *dirs = NULL;
	int size = mx_arr_size(args->dirs);

	for (int i = 0; i < size; i++)
		dirs = parse(args, dirs, args->dirs[i]);
	return dirs;
}

static t_dirs *parse(t_args *args, t_dirs *dirs, char *dir_name) {
	t_dirs *temp = dirs;

	if (!dirs)
		return data_to_dirs_struct(args, dir_name);
	while (temp->next != NULL) {
		temp = temp->next;
	}
	temp->next = data_to_dirs_struct(args, dir_name);
	return dirs;
}

static t_dirs *data_to_dirs_struct(t_args *args, char *dir_name) {
	t_dirs *temp = malloc(sizeof(t_dirs));
	DIR *dir = opendir(dir_name);
	char **data = data_to_arr(args, dir);
	int i = 0;

	temp->entry_dir = NULL;
	for (; data[i]; i++)
		temp->entry_dir = mx_add_dirs_entry(args, temp->entry_dir, data[i], dir_name);
	if (dir)
		closedir(dir);
	if (args->fl[4] || args->fl[5] || args->fl[11])
		mx_get_max_value_in_dirs(temp);
	temp->dir = mx_strdup(dir_name);
	temp->next = NULL;
	mx_del_str_arr(data);
	errno = 0;
	return temp;
}

static char **data_to_arr(t_args *args, DIR *dir) {
	struct dirent *entry = NULL;
	char **data = (char **)malloc(sizeof (char *) * 300000);
	int i = 0;

	while (dir && ((entry = readdir(dir)) != NULL)) {
		if (!args->fl[3] && entry->d_name[0] == '.')
			continue;
		data[i++] = mx_strdup(entry->d_name);
	}
	data[i] = NULL;
	mx_sort_data(args, data);
	return data;
}
