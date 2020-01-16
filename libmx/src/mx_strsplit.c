#include "libmx.h"

static char **check(int size_arr, const char *s, char **result);

char **mx_strsplit(const char *s, char c) {
    int size_arr = mx_count_words(s, c);
    int counter = 0;
    char **result = malloc(sizeof(char *) * (size_arr + 1));
    int index = 0;

    result = check(size_arr, s, result);
    for (int i = 0; i < mx_strlen(s); i++) {
        index = mx_get_char_index(s, c);
        index = index == -1 ? mx_strlen(s) : index;
        if (index) {
            result[counter] = mx_strndup(s, index);
            s += mx_strlen(result[counter]) - 1;
            i += mx_strlen(result[counter]) - 1;
            counter++;
        }
        s++;
    } 
    result[size_arr] = NULL;
    return result;
}

static char **check(int size_arr, const char *s, char **result) {
    if (!s)
        return NULL;
    if (size_arr == 1) {
        result[0] = mx_strdup(s);
        result[1] = NULL;
        return result;
    }
    return result;
}
