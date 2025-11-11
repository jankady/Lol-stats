#pragma once
#include <stdio.h>

int close_file(FILE*);

FILE* read_file(const char* file_path);

int clear_file(const char* file_path);

int write_file(const char* file_path, char* content);

int validate_argument(char* argument);

void remove_tailing(char* line);

void print_error(int error_code, const char* message, int number_as_message);
