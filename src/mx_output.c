#include "uls.h"

static int max_symbol(char **src);
// static int max_corect(int max);

void mx_output(char **src, int size) {
	int max = max_symbol(src);
	int cirlce = 0;
	int wsz = window_size();
	int col = size * max;

	printf("max = %d\n", (max + 8) * size);
	printf("wsz = %d\n", wsz);
	printf("col = %d\n", col);
	printf("max = %d\n", max);
	if ((max + 8) * size < wsz) {
		for (int i = 0; i < size; ++i) {
			cirlce = (max - mx_strlen(src[i])) / 8;
			if ((max - mx_strlen(src[i])) % 8 > 0)
				cirlce++;
	    	mx_printstr(src[i]);
	    	for (int j = 0; j < cirlce; j++)
	    		mx_printstr("\t");
	    	if (mx_strlen(src[i]) % 8 == 0)
	    		mx_printstr("\t");
	    }
	    mx_printstr("\n");
	} 
	// else {
	// 	for (int i = 0; i < size; i++) {
	// 		cirlce = (max - mx_strlen(src[i])) / 8;
	// 		if ((max - mx_strlen(src[i])) % 8 > 0)
	// 			cirlce++;
	//     	mx_printstr(src[i]);
	//     	for (int j = 0; j < cirlce; j++)
	//     		mx_printstr("\t");
	//     	if (src[i + 1])
	// 			mx_printstr("\t");
	// 	}
	// 	mx_printstr("\n");
	// }
	
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
	for (int i = 0; max_s % 8 != 0; i++) {
		max_s++;
	}
	return max_s;
}

// static int max_corect(int max) {
// 	for (int i = 0; max % 8 != 0; i++)
// 		max++;
// 	return max;
// }
