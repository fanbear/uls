#include "uls.h"

static char* minor_lol(t_file *file_st);
static char* major_lol(t_file *file_st);

char* mx_major_minor_size(t_file *file_st) {
	char* minor_major = NULL;
    char* minor = minor_lol(file_st);
    char* major = major_lol(file_st);

    minor_major = mx_strjoin_no_leaks(major, minor);
	return minor_major;
}

static char* major_lol(t_file *file_st) {
	char* itoa = mx_itoa(MAJOR(file_st->buf.st_rdev));
	char* lol = mx_strdup(", ");
	char* major = mx_strdup("   ");
	mx_str_reverse(itoa);

	for (int i = 0; itoa[i]; i++) {
		major[i] = itoa[i];
	}
	mx_str_reverse(major);
	major = mx_strjoin_no_leaks(major, lol);
	mx_strdel(&itoa);
	return major;
}

static char* minor_lol(t_file *file_st) {
	char* itoa = mx_itoa(MINOR(file_st->buf.st_rdev));
	char* minor = NULL;
	char* hex = NULL;

	if (MINOR(file_st->buf.st_rdev) < 255) {
		minor =  mx_strdup("   ");
		for (int i = 0; itoa[i]; i++)
			minor[i] = itoa[i];
		mx_str_reverse(minor);
	}
	else {
		minor = mx_strnew(8);
		int i = 2;
		minor[0] = '0';
		minor[1] = 'x';
		hex = mx_nbr_to_hex(MINOR(file_st->buf.st_rdev));
		for (int y = 0; y < 8 - mx_strlen(hex); y++) {
			minor[i] = '0';
			i++;
		}
		minor = mx_strcat(minor, hex);
		mx_strdel(&hex);
	}
	mx_strdel(&itoa);
	return minor;
}
