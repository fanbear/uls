#include "uls.h"

static void b_sort(char **arr, int size);
static int dell_point(char **src, st_general *gnr);

void mx_print_directory(st_general *gnr) {
	int count = 0;

	for (int i = 0; gnr->d_str[i] != NULL; i++)
		count++;
	count = dell_point(gnr->d_str, gnr);
	b_sort(gnr->no_point, count);
	mx_output(gnr->no_point, count);
}


static void b_sort(char **arr, int size) { 
    char *buf = (char*)malloc(sizeof(char) * 200);

    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (mx_strcmp(arr[j], arr[j + 1]) > 0) {
                buf = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = buf;
             }
         }
     }
}

static int dell_point(char **src, st_general *gnr) {
	int cn = 0;
	int n = 0;
	int size = 0;

	for (int i = 0; src[i] != NULL; i++ )
		cn++;
	gnr->no_point = (char**)malloc(sizeof(char) * (cn + 1));
	for (int i = 0; i < cn; i++) {
		if (src[i][0] == '.')
			i++;
		if (src[i][0] != '.') {
			gnr->no_point[n] = (char*)malloc(sizeof(char) * mx_strlen(src[i]));
			gnr->no_point[n] = src[i];
			n++;
			size++;
		}
	}
	return size;
}

