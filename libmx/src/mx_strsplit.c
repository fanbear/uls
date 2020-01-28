#include "libmx.h"

static char** split_word(const char *s, char c, char ** arr);

char **mx_strsplit(const char *s, char c) {
    int count = mx_count_words(s, c);
    char** arr = (char**)malloc(sizeof(char*) * count + 1);

    result = check(size_arr, s, result);
    for (int i = 0; i < mx_strlen(s); i++) {
        index = mx_get_char_index(s + i, c);
        index = index == -1 ? mx_strlen(s) : index;
        if (index) {
            result[counter] = mx_strndup(s+i, index);
            i += mx_strlen(result[counter]) - 1;
            counter++;
        }
    } 
    result[size_arr] = NULL;
    return result;
}

static char** split_word(const char *s, char c, char **arr) {
    int j = 0;
    int letters = 0;
    int word = 0;

    for (int i = 0; s[i] != '\0'; i++) {
        while (s[i] != c && s[i] != '\0') {
             word = 1;
             letters++;
             i++;
        }
        if (word) {
            arr[j] = mx_strnew(letters);
            arr[j] = mx_strncpy(arr[j], s + i - letters, letters);
            word = 0;
            letters = 0;
            j++;
        }
    }
    arr[j] = NULL;
    return arr;
}
