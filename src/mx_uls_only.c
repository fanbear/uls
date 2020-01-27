#include "uls.h"
// Найти и зафришить память
static int dell_point(char **src, st_general *gnr);

void mx_uls_only(st_general *gnr) {
    int count = 0;
	DIR *dptr;
    struct dirent *ds;
    char **temp;

    dptr = opendir(".");
    while ((ds = readdir(dptr)) != NULL)
    	count++;
    closedir(dptr);
    dptr = opendir(".");
    temp = (char**)malloc(sizeof(char*) * count + 1);
    for (int i = 0; (ds = readdir(dptr)) != NULL; i++){
    	temp[i] = (char*)malloc(sizeof(char) * mx_strlen(ds->d_name) + 1);
        temp[i] = ds->d_name;
        temp[i + 1] = NULL;
    }
    closedir(dptr);
    count = dell_point(temp, gnr);
    mx_b_sort(gnr->no_point, count);
    mx_output(gnr->no_point, count);
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
			gnr->no_point[n] = (char*)malloc(sizeof(char) * mx_strlen(src[i]) + 1);
			gnr->no_point[n] = src[i];
			n++;
			size++;
		}
	}
	return size;
}
