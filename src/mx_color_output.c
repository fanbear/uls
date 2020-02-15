#include "uls.h"

void mx_color_output(t_file *file_st) {
    if (file_st->permiss[0] == 'b')
        file_st->color = mx_strdup("\033[34;46m");
    else if (file_st->permiss[0] == 'c')
        file_st->color = mx_strdup("\033[34;43m");
    else if (file_st->permiss[0] == 'd') {
        if (file_st->permiss[8] == 'w' && file_st->permiss[9] == 't')
       		file_st->color = mx_strdup("\033[30;42m");
    	else if (permiss[8] == 'w' && permiss[9] == 'x')
        	file_st->color = mx_strdup("\033[30;43m");
    	else
        	file_st->color = mx_strdup("\033[34m");
    }
    else if (file_st->permiss[0] == 'l')
        file_st->color = mx_strdup("\033[35m");
    else if (file_st->permiss[0] == 's')
        file_st->color = mx_strdup("\033[32m");
    else if (file_st->permiss[0] == 'p')
        file_st->color = mx_strdup("\033[33m");	
	}
