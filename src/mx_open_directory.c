#include "uls.h"

char **mx_open_directory(int argc, char *argv[]) {
    int count = 0;
	DIR *dptr;
    struct dirent *ds;
    char **temp = NULL;;
    
    for (int i = 1; i < argc; i++) {
        dptr = opendir(argv[i]);
        while ((ds = readdir(dptr)))
            count++;
        closedir(dptr);
    	dptr = opendir(argv[i]);
        temp = (char**)malloc(sizeof(char*) * (count + 10));
    	for (int g = 0; ((ds = readdir(dptr)) != NULL); g++){
            temp[g] = mx_strdup(ds->d_name);
            temp[g + 1] = NULL;
        }
    }
    closedir(dptr);
    return temp;
    
}
