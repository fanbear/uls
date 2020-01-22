#include "uls.h"

static int dell_point(char **src, st_general *gnr);
static void sort_print(int size, char **dst, st_general *gnr);
static void sort_folder(char **src, st_general *gnr);
static void print_one_folder(char **dst, st_general *gnr);

void mx_print_directory(st_general *gnr, int argc, char **argv) {
	if (argc == 2) {
		print_one_folder(argv, gnr);
	}
	if (argc > 2) {
		sort_folder(argv, gnr); // отсортированый масив папок
		sort_print(argc, gnr->sort_f, gnr);
	}
}

static int dell_point(char **src, st_general *gnr) {
	int cn = 0;
	int n = 0;
	int size = 0;

	for (int i = 0; src[i] != NULL; i++ )
		cn++;
	gnr->no_point = (char**)malloc(sizeof(char**) * (cn + 2));
	for (int i = 0; i < cn; i++) {
		if (src[i][0] == '.')
			i++;
		if (src[i][0] != '.') {
			gnr->no_point[n] = mx_strdup(src[i]);
			gnr->no_point[n + 1] = NULL;
			n++;
			size++;
		}
	}
	return size;
}

static void sort_print(int size, char **dst, st_general *gnr) {

	for (int i = 0, cn = 0; i < size - 1; i++) {

		gnr->d_str = mx_open_folder(dst[i]);
		for (int i = 0; gnr->d_str[i] != NULL; i++)
			cn++;
		cn = dell_point(gnr->d_str, gnr);
		mx_b_sort(gnr->no_point, cn);
		mx_printstr(dst[i]);
		mx_printstr(":\n");
		mx_output(gnr->no_point, cn);
		if (dst[i + 1]) {
			mx_printstr("\n");
		}
	}
}

static void print_one_folder(char **dst, st_general *gnr) {
		int cn = 0;

		gnr->d_str = mx_open_folder(dst[1]);
		for (int i = 0; gnr->d_str[i] != NULL; i++)
			cn++;
		cn = dell_point(gnr->d_str, gnr);
		mx_b_sort(gnr->no_point, cn);
		mx_output(gnr->no_point, cn);
}

static void sort_folder(char **src, st_general *gnr) {
	int cn = 0;

	for (int i = 1; src[i] != NULL; i++)
		cn++;
	gnr->sort_f = (char**)malloc(sizeof(char*) * (cn + 1));
	for (int i = 1, n = 0; src[i] != NULL; i++) {
		gnr->sort_f[n] = mx_strdup(src[i]);
		gnr->sort_f[n + 1] = NULL;
		n++;
	}
	mx_b_sort(gnr->sort_f, cn);

}
