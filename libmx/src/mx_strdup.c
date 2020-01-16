#include "libmx.h"

char *mx_strdup(const char *str) {
    char *buf = NULL;

    if (str == NULL)
    	return NULL;
    buf =  mx_strnew(mx_strlen(str));
    mx_strcpy(buf,str);
    return buf;
}
