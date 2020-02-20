#include "uls.h"

void mx_karetka_files(char* str) {
	for (int i = 0; i < mx_strlen(str); i++) {
		//printf("%d\n", str[i]);
		if (str[i] == '\b' 
			|| str[i] == '\r' 
			|| str[i] == '\t' 
			|| str[i] == '\v') {
			str[i] = '?';
			//printf("NASHOL\n");
	}
	}
}
