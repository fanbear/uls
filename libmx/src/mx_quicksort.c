#include "libmx.h"

static void quick_while(char **arr, int i, int j, char *middle);
static void con(char **arr, int i, int j, int count);

int mx_quicksort(char **arr, int left, int right) {	
	int count = 0;
	int i = left;
	int j = right;
	char *middle = arr[(i + j) / 2];

	if (!arr) 
		return -1;
	while (i <= j) {
	 	quick_while(arr, i, j, middle);
	 	con(arr, i, j, count);
	 }
	 if (left < j)
	 	count += mx_quicksort(arr, left, j);
	 if (i < right)
	 	count += mx_quicksort(arr, i, right);
	 return count;
}

static void quick_while(char **arr, int i, int j, char *middle) {
	while (mx_strlen(arr[i]) < mx_strlen(middle))
	 	i++;
	while (mx_strlen(arr[j]) > mx_strlen(middle))
	 	j--;
}

static void con(char **arr, int i, int j, int count) {
	if (i <= j) {
	 	if (i <= j && (mx_strlen(arr[i]) != mx_strlen(arr[j]))) {
	   		mx_swap_char(arr[i], arr[j]);
	   		count++;
	   	}
	   	i++;
	   	j--;
	}
}
