#ifndef STRING_UTILS_H
#define STRING_UTILS_H

#include <stdbool.h>
#include <stdio.h>

bool starts_with(const char *str, const char *search);
bool ends_with(const char *str, const char *search);
size_t get_file_length(FILE *file);
void clear_string(char *str);
void extract_option(char *dest, const char *str, size_t start);
size_t count_lines(const char *str);
char **split_lines(const char *str, size_t line_count);

#endif // !STRING_UTILS_H
