#include "uls.h"

int mx_get_window_size() {
    struct winsize w;

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	return w.ws_col;
}
