#include "uls.h"

static t_dirs *parse(t_args *args, t_dirs *dirs, char *dir_name);
static t_dirs *data_to_dirs_struct(t_args *args, char *dir_name);
static t_dirs_entry *add_dirs_entry(t_dirs_entry *dirs_entry,
	struct dirent *entry, int *count, char *dir);
static t_dirs_entry *mx_pushing_data(struct dirent *entry, int *count, char *dir);

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
	struct dirent *entry = NULL;
	int count = 0;

	errno = 0;
	temp->total = 0;
	temp->entry_dir = NULL;
	while (dir && ((entry = readdir(dir)) != NULL)) {
		if (!args->fl[3] && entry->d_name[0] == '.')
			continue;
		temp->entry_dir = add_dirs_entry(temp->entry_dir, entry, &count, dir_name);
	}
	if (dir)
		closedir(dir);
	temp->dir = mx_strdup(dir_name);
	mx_get_max_value_in_dirs(temp);
	temp->amount_d_data = count;
	temp->next = NULL;
	return temp;
}

static t_dirs_entry *add_dirs_entry(t_dirs_entry *dirs_entry,
	struct dirent *entry, int *count, char *dir) {
	t_dirs_entry *current = dirs_entry;

	if (!dirs_entry)
		return mx_pushing_data(entry, count, dir);
	while (current->next != NULL)
		current = current->next;
	current->next = mx_pushing_data(entry, count, dir);
	return dirs_entry;
}

static t_dirs_entry *mx_pushing_data(struct dirent *entry, int *count, char *dir) {
	t_dirs_entry *temp = malloc(sizeof(t_dirs_entry));
	char *res = (mx_strcmp(dir, "/")) ? mx_strjoin(dir, "/") : mx_strdup(dir);

	*count = *count + 1;
	temp->d_name = mx_strdup(entry->d_name);
	temp->d_namlen = (int)entry->d_namlen;
	dir = mx_strjoin(res, temp->d_name);
	temp->stat = mx_get_stat(dir);
	mx_strdel(&dir);
	mx_strdel(&res);
	temp->next = NULL;

	return temp;
}
