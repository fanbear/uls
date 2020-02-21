#include "uls.h"

static int ostatok(int kb);
static void print_mb(int summ);
static void print_kb(int summ, int ost, char *str);

void mx_size_h(char *file_size) {
	float summ = atoi(file_size) / 1024;
	int ost = atoi(file_size) % 1024;
	char *str;

	mx_printchar(' ');
	if (atoi(file_size) > 100240)
		print_mb(summ);
	else if (atoi(file_size) >= 1024){
		str = mx_itoa(summ);
		print_kb(summ, ost, str);
	}
	else
		mx_pb_flag_h(ost);
}

static void print_kb(int summ, int ost, char *str) {
	if (ostatok(ost) < 9 && summ < 10) {
		mx_printstr(str);
		mx_printchar('.');
		mx_printint(ostatok(ost));
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
	if (delim < 10)
		mx_printint(0);
	else {
		kb = 1024 / kb;
		mx_printint(kb);
	}
	mx_printchar('M');
}

static int ostatok(int kb) {
	int r = 0;
	if (kb < 100){
		return 0;
	}
	while (kb > 9) {
		if ((kb % 10) > 5)
			r = 1;
		else
			r = 0;
		kb /= 10;
		kb += r;
	}

	return kb;
}
