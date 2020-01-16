#include "libmx.h"

int mx_get_substr_index(const char *str, const char *sub) {
	char *temp = NULL;
	int index = 0;
	
    if (str == NULL || sub == NULL)
    	return -2;
    temp = mx_strstr(str,sub);
    if (temp == NULL)
    	return -1;
    index = mx_strlen(str) - mx_strlen(temp);
    return index;
}
