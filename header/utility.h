#pragma once
#include <stdio.h>

FILE* read_file(const char* file_path);

FILE* write_file(const char* file_path);

int close_file(FILE*);

int validate_argument(char* argument);