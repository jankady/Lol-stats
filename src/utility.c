#pragma once

#include "../header/utility.h"

#include <errno.h>
#include <stdio.h>
#include <string.h>

FILE* read_file(const char* file_path) {

    FILE* file = fopen(file_path, "r");
    if (file == NULL) {
        printf("Doslo k chybe pri otevirani souboru: %s\n", strerror(errno));
        return NULL;
    }

    return file;
}

int close_file(FILE* file) {

    if (!fclose(file)) {
        return 0;
    }
    printf("Doslo k chybe pri zavirani souburu: %s\n", strerror(errno));
    return 1;

}

int validate_argument(char* argument) {

    FILE *file = read_file(argument);

    if (!file) {
        printf("Spatny argument\n");
        return 1;
    }
    close_file(file);
    return 0;
}