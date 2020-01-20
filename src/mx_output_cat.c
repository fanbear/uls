#include "uls.h"

static void print_cat(char **src, int size);
static void open_dot(st_general *gnr);
static int dell_point(char **src, st_general *gnr);
static void print_directory(st_general *gnr);

void mx_output_cat(st_general *gnr, int argc, char **argv) {
	if (argc == 1) {
		open_dot(gnr);
	}
	if (argc > 1) {
		gnr->d_str = mx_uls_no_flag(argc, argv);
		print_directory(gnr);
	}
}

static void open_dot(st_general *gnr) {
    int count = 0;
	DIR *dptr;
    struct dirent *ds;
    char **temp;

    dptr = opendir(".");
    while ((ds = readdir(dptr)) != NULL)
    	count++;
    closedir(dptr);
    dptr = opendir(".");
    temp = (char**)malloc(sizeof(char) * count);
    for (int i = 0; (ds = readdir(dptr)) != NULL; i++){
    	temp[i] = malloc(sizeof(char*) * mx_strlen(ds->d_name));
        temp[i] = ds->d_name;
        temp[i + 1] = NULL;
    }
    closedir(dptr);
    count = dell_point(temp, gnr);
    mx_b_sort(gnr->no_point, count);
    print_cat(gnr->no_point, count); //  принт через /n
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

static void print_cat(char **src, int size) {

	for (int i = 0; i < size; ++i) {
		mx_printstr(src[i]);
		mx_printstr("\n");
	}
}

static void print_directory(st_general *gnr) {
	int count = 0;

	for (int i = 0; gnr->d_str[i] != NULL; i++)
		count++;
	count = dell_point(gnr->d_str, gnr);
	mx_b_sort(gnr->no_point, count);
	mx_output(gnr->no_point, count);
}
