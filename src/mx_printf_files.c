#include "uls.h"

void mx_print_files(int size, char **files) {
    while (size--) {
        printf("%s ", *files);
    }
}
