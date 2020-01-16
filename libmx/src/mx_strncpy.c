#include "libmx.h"

char *mx_strncpy(char *dst, const char *src, int len) {
	int i = 0;

	for (; i < len; i++) {
		if (src[i] != '\0') {
			dst[i] = src[i];
		}
		else {
			dst[i] = '\0';
		}
	}
	dst[i] = '\0';
	return dst;
}
