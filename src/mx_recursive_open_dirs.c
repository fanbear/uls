#include "uls.h"

static void get_entry_dirs(t_args *args, char *dir_n);
static t_dirs *data_to_dirs_struct(t_args *args, char *dir_name);
static char **data_to_arr(t_args *args, DIR *dir);
static void uls_print(t_args *args, t_dirs *dirs);

void mx_recursive_open_dirs(t_args *args) {
    for (int i = 0; args->dirs[i]; i++) {
        t_dirs *dirs = data_to_dirs_struct(args, args->dirs[i]);

        if (mx_arr_size(args->dirs) > 1) {
            mx_printstr(args->dirs[i]);
            mx_printstr(":\n");
        }
        if (args->fl[4] || args->fl[5] || args->fl[11]) // печать одного флага
            mx_print_ls_l(args, dirs);
        else if (args->fl[6]) // печать одного флага
            mx_print_flag_mp(args, dirs, ", ");
        else {
            uls_print(args, dirs);
        }

        if (args->fl[2]) {
            // if (mx_arr_size(args->dirs) == 1)
            //     mx_printstr("\n");
            get_entry_dirs(args, args->dirs[i]);

        }
        if (args->dirs[i + 1])
        mx_printstr("\n");
    }
}

static void get_entry_dirs(t_args *args, char *dir_n) {
    DIR *dir;
    struct dirent *entry;
    int i = 0;
    char **res_data = (char **)malloc(sizeof(char *) * 30000000);

    if (!(dir = opendir(dir_n)))
        return;
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_DIR) {
            if ((!args->fl[3] && entry->d_name[0] == '.')
                || !mx_strcmp(entry->d_name, ".")
                || !mx_strcmp(entry->d_name, ".."))
                continue;
            char *d_name = mx_strjoin(dir_n, "/");

            d_name = mx_strjoin(d_name, entry->d_name);
            res_data[i++] = mx_strdup(d_name);
            mx_strdel(&d_name);
        }
    }
    mx_sort_data(args, res_data);

    // if (mx_arr_size(res_data) > 1)
        // mx_printstr("2\n");
    for (int j = 0; res_data[j]; j++) {
        t_dirs *dirs = data_to_dirs_struct(args, res_data[j]);

        mx_printstr("\n");
        mx_printstr(dirs->dir);
        mx_printstr(":\n");
        if (args->fl[4] || args->fl[5] || args->fl[11]) { // печать одного флага
    		mx_print_ls_l(args, dirs);
            // mx_printstr("3\n");
        }
    	else if (args->fl[6]) { // печать одного флага
    		mx_print_flag_mp(args, dirs, ", ");
            // mx_printstr("4\n");
        }
    	else {
    		uls_print(args, dirs);
        }
        mx_del_dirs_struct(dirs);
        get_entry_dirs(args, res_data[j]);
        // if (res_data[j+1])
    }

    mx_del_str_arr(res_data);
    closedir(dir);
}

static t_dirs *data_to_dirs_struct(t_args *args, char *dir_name) {
	t_dirs *temp = malloc(sizeof (t_dirs));
	DIR *dir = opendir(dir_name);
	char **data = data_to_arr(args, dir);
	int i = 0;

	temp->entry_dir = NULL;
	for (; data[i]; i++)
		temp->entry_dir = mx_add_dirs_entry(args, temp->entry_dir,
											data[i], dir_name);
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
	char **data = (char **)malloc(sizeof (char *) * 3000000);
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

static void uls_print(t_args *args, t_dirs *dirs) {
	if ((isatty(1) || args->fl[0]) && !args->fl[8]) {
		if (isatty(1) && args->fl[1])
			mx_print(args, dirs, mx_print_multy_colomn_g);
		else
			mx_print(args, dirs, mx_print_ls_multy_colomn); // обычный принт
	}
	else
		mx_print(args, dirs, mx_print_ls_monocolomn); // обычный принт | cat -e
}
