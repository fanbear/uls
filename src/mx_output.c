#include "uls.h"

static int max_symbol(char **src);

void mx_output(char **src, int size) {
	for (int i = 0; i < size; ++i) {
    	mx_printstr(src[i]);
    	for (int j = 0; j < (max_symbol(src) - mx_strlen(src[i])); j++)
    		mx_printstr(" ");
    	if (src[i + 1]) {
			mx_printstr("\t");
		}
    }
    mx_printstr("\n");
}

static int max_symbol(char **src) {
	int max_s = 0;
	int count = 0;
	for (int i = 0; src[i] != NULL; ++i) {
		count = 0;
		for (int j = 0; src[i][j] != '\0'; ++j) {
			count++;
		}
		if (max_s <= count) {
			max_s = count;	
		}
	}
	return max_s;
}
