#include "libmx.h"

bool is_space(char c);
static void ret(char *temp, char *string, int i, int j);

char *mx_del_extra_spaces(const char *str) {
	char *temp = NULL;
	char *string = NULL;
	int j = 0;

	if (str == NULL)
		return NULL;
	temp = mx_strtrim(str);
	string = (char *) malloc(sizeof(char) * mx_strlen(temp));
	if (string == NULL) {
		free(string);
		return NULL;
	}
	for (int i = 0 ; temp[i]; i++)
		ret(temp, string, i, j);
	free(temp);
	string[j + 1] = '\0';
	return string;
}

static void ret(char *temp, char *string, int i, int j) {
	if (temp[i] == ' ') {
		if (!is_space(temp[i + 1])) {
			string[j] = ' ';
			j++;
		}
		else (is_space(temp[i + 1])) ;
	}
	else {
		string[j] = temp[i];
		j++;
	}
}
