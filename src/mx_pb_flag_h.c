#include "uls.h"

void mx_pb_flag_h(int ost) {
	if (ost > 999 && ost < 1023) {
		mx_printstr("1.0K");
	}
	else {
		if (mx_strlen(mx_itoa(ost)) + 1 < 4)
		for (int i = mx_strlen(mx_itoa(ost)) + 1; i < 4; i++)
			mx_printchar(' ');
		mx_printint(ost);
		mx_printchar('B');
	}
}
