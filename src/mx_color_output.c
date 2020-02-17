#include "uls.h"

void mx_color_output(t_file *file_st) {
    if (file_st->permiss[3] == 's' || file_st->permiss[3] == 'S')
        file_st->color = mx_strdup("\033[30;41m");
    else if (file_st->permiss[6] == 's' || file_st->permiss[6] == 'S')
        file_st->color = mx_strdup("\033[30;46m");
    else if (file_st->permiss[0] == 'b')
        file_st->color = mx_strdup("\033[34;46m");
    else if (file_st->permiss[0] == 'c')
        file_st->color = mx_strdup("\033[34;43m");
    else if (file_st->permiss[0] == 'd') {
        if (file_st->permiss[8] == 'w' && (file_st->permiss[9] == 't' || file_st->permiss[9] == 'T'))
            file_st->color = mx_strdup("\x1B[0;30;42m");
        else if (file_st->permiss[8] == 'w' && file_st->permiss[9] == 'x')
            file_st->color = mx_strdup("\033[30;43m");
        else
            file_st->color = mx_strdup("\x1B[34m");
    }
    else if (file_st->permiss[0] == 'l')
        file_st->color = mx_strdup("\033[35m");
    else if (file_st->permiss[0] == 's')
        file_st->color = mx_strdup("\033[32m");
    else if (file_st->permiss[0] == 'p')
        file_st->color = mx_strdup("\033[33m");
    else if (file_st->permiss[0] == 'w')
        file_st->color = mx_strdup("\033[36m");
    else if (file_st->permiss[3] == 'x')
        file_st->color = mx_strdup("\033[31m");
}
