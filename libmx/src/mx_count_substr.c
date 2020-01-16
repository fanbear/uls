#include "libmx.h"

int mx_count_substr(const char *str, const char *sub) {
	int len = 0;
	int count = 0;

	if (!str || !sub)
		return -1;
	len = mx_strlen(sub);
	if (!len) return 0;
	while (mx_strstr(str,sub) != NULL) {
		if (mx_strncmp(str, sub, len) == 0)
			count++;
		str += len;
	}
	return count;
}
