#include "uls.h"

void mx_print(t_args *args, t_dirs *dirs, void (*print_ls)(char **, t_args *, char *dir)) {
    if (args->files[0]) {
        (*print_ls)(args->files, args, NULL);
        if (dirs)
            mx_printchar('\n');
    }
    if (dirs) {
        char **data = NULL;

        if (dirs->next || args->not_valid[0] || args->files[0]) {
            while (dirs) {
                if (!mx_check_on_access(1, dirs->dir)) {
                    data = mx_get_data_from_struct(dirs);
                    if (args->fl[2] && args->dirs_num == 1)
                        args->dirs_num = 0;
                    else {
                        mx_printstr(dirs->dir);
                        mx_printstr(":\n");
                    }
                    if (data) {
                        (*print_ls)(data, args, dirs->dir);
                        mx_del_str_arr(data);
                    }
                }
                dirs = dirs->next;
                if (dirs)
                    mx_printchar('\n');
            }
        }
        else
            if (!mx_check_on_access(0, dirs->dir)) {
                data = mx_get_data_from_struct(dirs);
                if (data) {
                    (*print_ls)(data, args, dirs->dir);
                    mx_del_str_arr(data);
                }
            }
        }
}

// #include "uls.h"
// ​
// static void file_and_dir(char **data, t_args *args, t_dirs *dirs,
//     void (*print)(char **, t_args *));
// static void many_dirs(char **data, t_args *args, t_dirs *dirs,
//     void (*print)(char **, t_args *));
// ​
// void mx_print(t_args *args, t_dirs *dirs, void (*print_ls)(char **, t_args *)) {
//     if (args->files[0]) {
//         (*print_ls)(args->files, args);
//         if (dirs)
//             mx_printchar('\n');
//     }
//     if (dirs) {
//         char **data = NULL;
// ​
//         if (dirs->next || args->not_valid[0] || args->files[0]) {
//             while (dirs) {
//                 if (!mx_check_on_access(1, dirs->dir))
//                     many_dirs(data, args, dirs, print_ls);
//                 dirs = dirs->next;
//                 if (dirs)
//                     mx_printchar('\n');
//             }
//         }
//         else
//             file_and_dir(data, args, dirs, print_ls);
//     }
// ​
// }
// ​
// static void file_and_dir(char **data, t_args *args, t_dirs *dirs,
//     void (*print)(char **, t_args *)) {
//     if (!mx_check_on_access(0, dirs->dir)) {
//         data = mx_get_data_from_struct(dirs);
//         print(data, args);
//         mx_del_str_arr(data);
//     }
// }
// ​
// static void many_dirs(char **data, t_args *args, t_dirs *dirs,
    // void (*print)(char **, t_args*)) {
//     data = mx_get_data_from_struct(dirs);
//
//     if (args->fl[2] && args->dirs_num == 1) {
//         args->dirs_num = 0;
//     } else {
//         mx_printstr(dirs->dir);
//         mx_printstr(":\n");
//     }
//     if (data) {
//         print(data, args);
//         mx_del_str_arr(data);
//     }
//
// }
