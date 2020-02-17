#include "uls.h"

void mx_colored_name(int toggle_g, char *color, char *name) {
    if (toggle_g) {
        mx_printstr(color);
        mx_printstr(name);
        mx_printstr(COLOR_RESET);
    }
    else
        mx_printstr(name);
}
