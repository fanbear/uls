#include "uls.h"

static int max_symbol(char **src);
// static int max_corect(int max);

void mx_output(char **src, int size) {
	int max = max_symbol(src);
	int cirlce = 0;
	int wsz = window_size();
	int col = (max * size) / wsz;

	if ((max * size) % wsz > 60)
		col++;
	if (wsz - (max * size % wsz) < max)
		col++;

	if ((max) * size < wsz) {
		for (int i = 0; i < size; ++i) {
			cirlce = (max - mx_strlen(src[i])) / 8;
			if ((max - mx_strlen(src[i])) % 8 != 0)
				cirlce++;
	    	mx_printstr(src[i]);
	    	if (src[i + 1]){
		    	for (int j = 0; j < cirlce; j++)
		    		mx_printstr("\t");
	    	}
	    }
	    mx_printstr("\n");
	} 
	else {
		for (int i = 0; i < col; i++) {
			for (int j = i; j < size; j = j + col) {
				cirlce = (max - mx_strlen(src[j])) / 8;
				if ((max - mx_strlen(src[j])) % 8 != 0)
					cirlce++;
		    	mx_printstr(src[j]);
		    	for (int s = 0; s < cirlce; s++)
		    		mx_printstr("\t");
			}
			mx_printstr("\n");
		}
		// mx_printstr("\n");
	}
	
}

static int max_symbol(char **src) {
	int max_s = 0;
	int count = 0;
	for (int i = 0; src[i] != NULL; ++i) {
		count = 0;
		for (int j = 0; src[i][j] != '\0'; ++j)
			count++;
		if (max_s <= count)
			max_s = count;	
	}
	if (max_s % 8 == 0) 
		max_s = max_s + 8;
	else
		for (int i = 0; max_s % 8 != 0; i++)
			max_s++;
	return max_s;
}
