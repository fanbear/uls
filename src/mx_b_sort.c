#include "uls.h"

void mx_b_sort(char **arr, int size) { 
    char *buf = (char*)malloc(sizeof(char) * 200);

    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (mx_strcmp(arr[j], arr[j + 1]) > 0) {
                buf = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = buf;
             }
         }
     }
}
