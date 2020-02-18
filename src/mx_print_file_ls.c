#include "uls.h"

static void print_space(int max_elem, char* str) {
    for(int j = 0; j < max_elem - mx_strlen(str); j++) {
        mx_printchar(' ');
    }
}

static void g_or_l(t_files *files, t_args *args) {
    if (args->fl[4] != 1) {
        mx_printstr(files->entry_file->stat->user_name);
        print_space(files->max_user, files->entry_file->stat->user_name);
        mx_printchar(' ');
        mx_printchar(' ');
    }
    if (args->fl[11] != 1) {
        mx_printstr(files->entry_file->stat->group_name);
        print_space(files->max_group, files->entry_file->stat->group_name);
        mx_printchar(' ');
        mx_printchar(' ');
    }
    if (args->fl[4] && args->fl[11]) {
        mx_printchar(' ');
        mx_printchar(' ');
    }
}


static t_file_entry *pushing_data(t_args *args, char *file) {
    t_file_entry *entry_file = malloc(sizeof (t_file_entry));

    entry_file->files = mx_strdup(file);
    entry_file->stat = mx_get_stat(args, file);
    entry_file->next = NULL;
    return entry_file;
}

static t_file_entry *get_files_entry(t_args *args, t_file_entry *entry_file, char *file) {
    t_file_entry *current  = entry_file;

    if (!entry_file)
        return pushing_data(args, file);
    while (current->next != NULL)
        current = current->next;
    current->next = pushing_data(args, file);
    return entry_file;
}

static t_files *mx_get_files(t_args *args, char **files) {
 int i = 0;
 t_files *files_st = malloc(sizeof (t_files));

 files_st->entry_file = NULL;
 while (files[i]) {
     files_st->entry_file = get_files_entry(args, files_st->entry_file, files[i]);
     i++;
 }
 return files_st;
}


static void print_info(t_args *args, t_files *files) {
    mx_printstr(files->entry_file->stat->permiss);
    mx_printchar(' ');
    print_space(files->max_link, files->entry_file->stat->nlink);
    mx_printstr(files->entry_file->stat->nlink);
    mx_printchar(' ');
    g_or_l(files, args);
    if (files->entry_file->stat->permiss[0] == 'b' || files->entry_file->stat->permiss[0] == 'c')
        mx_printstr(files->entry_file->stat->rdev);
    else {
        print_space(files->max_size, files->entry_file->stat->file_size);
        mx_printstr(files->entry_file->stat->file_size);
    }
}

void mx_print_file_ls(t_args *args) {
    t_files *files = mx_get_files(args, args->files);

    mx_get_max_value_in_files(files);
    while (files->entry_file) {
        print_info(args, files);
        mx_printchar(' ');
        if (args->fl[10] == 1)
            mx_printstr(files->entry_file->stat->time1);
        else {
            mx_printstr(files->entry_file->stat->time1);
            print_space(files->max_time, files->entry_file->stat->time2);
            mx_printstr(files->entry_file->stat->time2);
        }
        mx_printchar(' ');
        mx_colored_name(args, files->entry_file->files, NULL);
    	if (files->entry_file->stat->name_link[0]) {
    		mx_printstr(" -> ");
    		mx_printstr(files->entry_file->stat->name_link);
    	}
    	mx_printchar('\n');
    	files->entry_file = files->entry_file->next;
	}
}
