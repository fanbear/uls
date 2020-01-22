#include "uls.h"

char **mx_open_folder(char *str) {
    int count = 0;
	DIR *dptr;
    struct dirent *ds;
    char **temp = NULL;;
    
        dptr = opendir(str);
        while ((ds = readdir(dptr)))
            count++;
        closedir(dptr);
    	dptr = opendir(str);
        temp = (char**)malloc(sizeof(char*) * (count + 10));
    	for (int g = 0; ((ds = readdir(dptr)) != NULL); g++){
            temp[g] = mx_strdup(ds->d_name);
            temp[g + 1] = NULL;
        }
    closedir(dptr);
    return temp;
    
}
