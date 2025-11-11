#include "../header/utility.h"

#include <errno.h>
#include <stdio.h>
#include <string.h>

int close_file(FILE* file) {

    if (!fclose(file)) {
        return 0;
    }
    fprintf(stderr,"Doslo k chybe pri zavirani souburu: %s\n", strerror(errno));
    return 1;

}

FILE* read_file(const char* file_path) {

    FILE* file = fopen(file_path, "r");
    if (file == NULL) {
        fprintf(stderr,"Doslo k chybe pri otevirani souboru: %s\n", strerror(errno));
        return NULL;
    }

    return file;
}

int clear_file(const char* file_path) {

    FILE* file = fopen(file_path, "w");
    if (file == NULL) {
        fprintf(stderr,"Doslo k chybe pri vytvareni souboru: %s\n", strerror(errno));
        return 1;
    }

    close_file(file);
    return 0;
}

int write_file(const char* file_path, char* content) {
    FILE* file = fopen(file_path, "a");
    if (file == NULL) {
        fprintf(stderr,"Doslo k chybe pri otevirani souboru: %s\n", strerror(errno));
        return 1;
    }
    if (fputs(content, file) == EOF) {
        fprintf(stderr,"Doslo k chybe pri zapisu do souboru: %s\n", strerror(errno));
        close_file(file);
        return 1;
    }

    close_file(file);
    return 0;
}

int validate_argument(char* argument) {

    FILE *file = read_file(argument);

    if (!file) {
        fprintf(stderr,"Spatny argument\n");
        return 1;
    }
    close_file(file);
    return 0;
}

