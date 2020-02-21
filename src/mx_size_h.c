#include "uls.h"

static int ostatok(int n);
static void print_byte(int ost);
static void print_mb(int summ);
static int kb_o(int kb);

void mx_size_h(char *file_size) {
	float summ = atoi(file_size) / 1024;
	int ost = atoi(file_size) % 1024;

	if (atoi(file_size) > 100240)
		print_mb(summ);
	else if (atoi(file_size) > 1024){
		mx_printint(summ);
		if (ostatok(ost) < 600 && ostatok(ost) != 0 && summ < 10) {
			mx_printchar('.');
			mx_printint(ostatok(summ));
		}
		mx_printchar('K');
	}
	else
		print_byte(ost);
}

static void print_byte(int ost) {
	mx_printint(ost);
	mx_printchar('B');
}

static void print_mb(int summ) {
	int delim = summ / 1024;
	int kb = summ - (delim * 1024);

	mx_printint(delim);
	mx_printchar('.');
	if (kb < 100)
		mx_printint(0);
	else {
		kb = 1024 / kb;
		mx_printint(kb);
	}
	mx_printchar('M');
}


static int ostatok(int n) {
	int delim = n / 1024;
	int kb = n - (delim * 1024);
	
	return kb_o(kb);
}

static int kb_o(int kb) {
	int r = 0;
	// printf("%i\n", kb);
	if (kb > 9) {
		if ((kb % 10) > 5 && kb > 10)
			r = 1;
		kb /= 10;
		kb += r;
		kb_o(kb);
	}
	else
		return kb;
	return kb;
}
