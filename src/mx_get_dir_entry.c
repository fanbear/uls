#include "uls.h"

static t_dirs *parse(t_args *args, t_dirs *dirs, char *dir_name);
static t_dirs *data_to_dirs_struct(t_args *args, char *dir_name);
static char **data_to_arr(t_args *args, DIR *dir);

t_dirs *mx_get_dir_entry(t_args *args) {
	t_dirs *dirs = NULL;

	for (int i = 0; args->dirs[i]; i++)
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
	DIR *dir = opendir(dir_name);
	t_dirs *temp = malloc(sizeof(t_dirs));
	char **data = data_to_arr(args, dir);

	temp->entry_dir = NULL;
	if (data) {
		for (int i = 0; data[i]; i++)
			temp->entry_dir = mx_add_dirs_entry(args, temp->entry_dir, data[i], dir_name);
		mx_get_max_value_in_dirs(temp);
		mx_del_str_arr(data);
	}
	if (dir)
		closedir(dir);
	errno = 0;
	temp->dir = mx_strdup(dir_name);
	temp->next = NULL;
	return temp;
}

static char **data_to_arr(t_args *args, DIR *dir) {
	struct dirent *entry = NULL;
	char *data = NULL;
	char **res = NULL;

	while (dir && ((entry = readdir(dir)) != NULL)) {
		if (!args->fl[3] && entry->d_name[0] == '.')
			continue;
		char *space = mx_strdup("~");
        char *d_name = mx_strdup(entry->d_name);

        data = mx_strjoin_no_leaks(data, space);
        data = mx_strjoin_no_leaks(data, d_name);
	}
	if (data) {
		res = mx_strsplit(data, '~');
		mx_strdel(&data);
		mx_sort_data(args, res);
	}
	return res;
}
