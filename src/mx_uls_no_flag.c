#include "uls.h"

char **mx_uls_no_flag(int argc, char *argv[]) {
	DIR *dptr;
    struct dirent *ds;
    char **temp = (char**)malloc(sizeof(char) * 100000);
    int n = 0;
    
    for (int i = 1; i < argc; i++) {
    	dptr = opendir(argv[i]);
    	while ((ds = readdir(dptr)) != 0) {
            temp[n] = malloc(sizeof(char*) * mx_strlen(ds->d_name));
            temp[n] = ds->d_name;
            n++;
        }
    }
    closedir(dptr);
    return temp;
}
