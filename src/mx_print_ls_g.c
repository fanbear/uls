#include "uls.h"

static void print_files(t_args *args);
static void print_dirs(t_dirs *dirs);

static void print_space(int max_elem, char* str) {
	for(int j = 0; j < max_elem - mx_strlen(str); j++) {
		mx_printchar(' ');
	}
}

static void print_total(int sum_total) {
	mx_printstr("total ");
	mx_printint(sum_total);
	mx_printchar('\n');
}

static t_files *mx_get_files(char **files);
static t_file_entry *get_files_entry(t_file_entry *entry_file, char *file);
static t_file_entry *pushing_data(char *file);

void mx_print_ls_g(t_args *args, t_dirs *dirs) {
	if (args->files[0]) {
		print_files(args);
		if (dirs)
			mx_printchar('\n');
	}

    if (dirs) {
        if (dirs->next || args->not_valid[0] || args->files[0])
            while (dirs) {
				if (mx_check_on_access(1, dirs->dir)) {
					dirs = dirs->next;
				}
				else {
					mx_printstr(dirs->dir);
					mx_printstr(":\n");
					// mx_sort_content(dirs->entry_dir);
		            print_dirs(dirs);
					dirs = dirs->next;
				}
				if (dirs)
					mx_printchar('\n');
            }
        else {
			if (!mx_check_on_access(0, dirs->dir)) {
				// mx_sort_content(dirs->entry_dir);
				print_dirs(dirs);
			}
		}
    }
}

static void print_dirs(t_dirs *dirs) {
    t_dirs_entry *temp = dirs->entry_dir;

	print_total(dirs->total);
    while (temp) {
        mx_printstr(temp->stat->permiss);
        mx_printchar(' ');
        print_space(dirs->max_link, temp->stat->nlink);
        mx_printstr(temp->stat->nlink);
        mx_printchar(' ');
        // mx_printstr(temp->stat->user_name);
        // print_space(dirs->max_user, temp->stat->user_name);
        // mx_printchar(' ');
        // mx_printchar(' ');
        mx_printstr(temp->stat->group_name);
        print_space(dirs->max_group, temp->stat->group_name);
        mx_printchar(' ');
        mx_printchar(' ');
         if (temp->stat->permiss[0] == 'b' || temp->stat->permiss[0] == 'c') {
        	mx_printstr(temp->stat->rdev);
        }
        else {
			print_space(dirs->max_size, temp->stat->file_size);
			mx_printstr(temp->stat->file_size);
        }
        mx_printchar(' ');
        mx_printstr(temp->stat->time1);
		print_space(dirs->max_time, temp->stat->time2);
		mx_printstr(temp->stat->time2);
        mx_printchar(' ');
        mx_printstr(temp->d_name);
		if (temp->stat->name_link[0]) {
			mx_printstr(" -> ");
			mx_printstr(temp->stat->name_link);
		}
		mx_printchar('\n');
        temp = temp->next;
    }
}

static void print_files(t_args *args) {
	t_files *files = mx_get_files(args->files);

	mx_get_max_value_in_files(files);
	while (files->entry_file) {
		mx_printstr(files->entry_file->stat->permiss);
        mx_printchar(' ');
        print_space(files->max_link, files->entry_file->stat->nlink);
        mx_printstr(files->entry_file->stat->nlink);
        mx_printchar(' ');
        mx_printstr(files->entry_file->stat->group_name);
        print_space(files->max_group, files->entry_file->stat->group_name);
        mx_printchar(' ');
        mx_printchar(' ');
        if (files->entry_file->stat->permiss[0] == 'b' || files->entry_file->stat->permiss[0] == 'c') {
        	mx_printstr(files->entry_file->stat->rdev);
        }
        else {
			print_space(files->max_size, files->entry_file->stat->file_size);
        	mx_printstr(files->entry_file->stat->file_size);
        }
        mx_printchar(' ');
        mx_printstr(files->entry_file->stat->time1);
		print_space(files->max_time, files->entry_file->stat->time2);
		mx_printstr(files->entry_file->stat->time2);
        mx_printchar(' ');
        mx_printstr(files->entry_file->files);
		if (files->entry_file->stat->name_link[0]) {
			mx_printstr(" -> ");
			mx_printstr(files->entry_file->stat->name_link);
		}
		mx_printchar('\n');
		files->entry_file = files->entry_file->next;
	}
}

static t_files *mx_get_files(char **files) {
	int i = 0;
	t_files *files_st = malloc(sizeof (t_files));

	files_st->entry_file = NULL;
	while (files[i]) {
		files_st->entry_file = get_files_entry(files_st->entry_file, files[i]);
		i++;
	}
	return files_st;
}

static t_file_entry *get_files_entry(t_file_entry *entry_file, char *file) {
	t_file_entry *current  = entry_file;

	if (!entry_file)
		return pushing_data(file);
	while (current->next != NULL)
		current = current->next;
	current->next = pushing_data(file);
	return entry_file;
}

static t_file_entry *pushing_data(char *file) {
	t_file_entry *entry_file = malloc(sizeof (t_file_entry));

	entry_file->stat = mx_get_stat(file);
	entry_file->files = mx_strdup(file);
	entry_file->next = NULL;
	return entry_file;
}
