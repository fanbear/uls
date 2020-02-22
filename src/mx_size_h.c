#include "uls.h"

static int ostatok(char *kb);
static void print_mb(int summ);
static void print_kb(int summ, int ost, char *str);

void mx_size_h(char *file_size) {
	float summ = atoi(file_size) / 1024;
	int ost = atoi(file_size) % 1024;
	char *str;

	mx_printchar(' ');
	if (atoi(file_size) > 1048576)
		print_mb(summ);
	else if (atoi(file_size) >= 1024){
		str = mx_itoa(summ);
		print_kb(summ, ost, str);
	}
	else
		mx_pb_flag_h(ost);
}

static void print_kb(int summ, int ost, char *str) {
	if (summ < 10) {
		mx_printstr(str);
		mx_printchar('.');
		mx_printint(ostatok(mx_itoa(ost)));
		mx_printchar('K');
	}
	else {
		if (summ < 10) {
			mx_printstr(str);
			mx_printchar('.');
			mx_printchar('0');
			mx_printchar('K');
		}
		else {
			for (int i = mx_strlen(str) + 1; i < 4; i++)
			mx_printchar(' ');
			mx_printstr(str);
			mx_printchar('K');
		}
	}
}

static void print_mb(int summ) {
	int delim = summ / 1024;
	int kb = summ - (delim * 1024);

	mx_printint(delim);
	mx_printchar('.');
	if (delim > 10)
		mx_printint(0);
	else {
		kb = 1024 / kb;
		mx_printint(kb);
	}
	mx_printchar('M');
}

static int ostatok(char *kb) {
	int tr = 0;
	for (int i = 0; i < mx_strlen(kb); i--) {
		if (mx_strcmp(&kb[i], "5") > 0){
			tr = 1;
			if (kb[i - 1] && kb[i - 1] != '9')
				kb[i - 1] = ((kb[i - 1] - '0') + tr) + '0';
			else
				return (kb[0] - '0');
		}
		else
			return (kb[0] - '0') + 1;
	}
	return kb[0] - '0';
}
