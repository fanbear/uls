#include "uls.h"

void mx_color_output(t_file *file_st) {
    if (file_st->permiss[0] == 'b')
        mx_printstr("\033[34;46m");
    else if (file_st->permiss[0] == 'c')
        mx_printstr("\033[34;43m");
    else if (file_st->permiss[0] == 'd') {
        if (file_st->permiss[8] == 'w' && file_st->permiss[9] == 't')
       		mx_printstr("\033[30;42m");
    	else if (permiss[8] == 'w' && permiss[9] == 'x')
        	mx_printstr("\033[30;43m");
    	else
        	mx_printstr("\033[34m");
    }
    else if (file_st->permiss[0] == 'l')
        mx_printstr("\033[35m");
    else if (file_st->permiss[0] == 's')
        mx_printstr("\033[32m");
    else if (file_st->permiss[0] == 'p')
        mx_printstr("\033[33m");	
	}
