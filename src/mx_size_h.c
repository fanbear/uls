#include "uls.h"

static int ostatok(int kb, int summ);
static void print_mb(int summ);
static void print_kb(int summ, int ost, char *str);
static void print_byte(int ost);
static int ostatok_mb(int kb);
 // убрать  atoi

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
		print_byte(ost);
}

static void print_kb(int summ, int ost, char *str) {
	if (summ < 10) {
		if (ostatok(ost, summ) == 1000)
			mx_printint(summ + 1);
		else
			mx_printstr(str);
		mx_printchar('.');
		mx_printint(ostatok(ost, summ));
		mx_printchar('K');
	}
	else {
		for (int i = mx_strlen(str) + 1; i < 4; i++)
			mx_printchar(' ');
		if (ostatok(ost, summ) == 1000) {
			mx_printint(summ + 1);
			mx_printchar('K');
		}
		else {
			mx_printstr(str);
			mx_printchar('K');
		}
	}
}

static void print_mb(int summ) {
	int delim = summ / 1024;
	int kb = summ - (delim * 1024);

	if (delim > 10) {
		mx_printstr(" ");
		mx_printint(delim);
		mx_printchar('M');
	}
	else {
		mx_printint(delim);
		mx_printchar('.');
		mx_printint(ostatok_mb(kb));
		mx_printchar('M');
	}
	
}

static int ostatok_mb(int kb) {
	if (kb < 50)
		return 0;
	if (kb >= 500) {
		if (kb % 10 > 5 && kb % 100 > 45 && kb / 100 != 9)
			return kb / 100 + 1;
		else
			return kb / 100;
	}
	else {
		if (kb % 100 > 55 && kb / 100 != 9)
			return kb / 100 + 1;
		else
			return kb / 100;
	}
	return kb / 100;
}

static int ostatok(int kb, int summ) {
	if (kb < 50)
		return 0;
	if (kb > 500 && summ > 10) {
		return 1000;
	}
	kb = (kb * 1000) / 1024;
	if (kb % 100 >= 50)
		return kb / 100 + 1;
	return kb / 100;
}

static void print_byte(int ost) {
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

