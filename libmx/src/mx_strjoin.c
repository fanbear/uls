#include "libmx.h"

static void condition(const char *s1, const char *s2, int i, int j, char *temp);

char *mx_strjoin(const char *s1, const char *s2) {
	int i = 0;
	int j = 0;
	char *temp = NULL;
	char *buf = NULL;

	if (s1 == NULL && s2 == NULL)
		return NULL;
	if (s1 == NULL) {
		buf = mx_strnew(mx_strlen(s2));
		return mx_strcpy(buf, s2);
	}
	if (s2 == NULL) {
		buf = mx_strnew(mx_strlen(s1));
		return mx_strcpy(buf, s1);
	}
	temp = mx_strnew(mx_strlen(s1) + mx_strlen(s2) + 1);
	condition(s1, s2, i, j, temp);
	return temp;
}

static void condition(const char *s1, const char *s2, int i, int j, char *temp) {
	while (s1[i] != '\0') {
		temp[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0') {
		temp[i] = s2[j];
		i++;
		j++;
	}
}
