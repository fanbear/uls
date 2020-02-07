#include "uls.h"

char **mx_get_data_from_struct(t_dirs *dirs) {
    t_dirs_entry *temp = dirs->entry_dir;
    char *data = NULL;
    char **res = NULL;

    while (temp) {
        char *space = mx_strdup(" ");
        char *d_name = mx_strdup(temp->d_name);

        data = mx_strjoin_no_leaks(data, space);
        data = mx_strjoin_no_leaks(data, d_name);
        temp = temp->next;
    }

    res = mx_strsplit(data, ' ');
    mx_strdel(&data);

    // printf("data = %s\n", data);
    // for (int i = 0; res[i]; i++) {
    //     printf("res[%d] = %s\n", i, res[i]);
	// 	mx_strdel(&res[i]);
    //     printf("res[%d] = %s\n", i, res[i]);
	// }
    // mx_del_str_arr(res);

    // system("leaks -q uls");
    // exit(1);
    return res;
}
