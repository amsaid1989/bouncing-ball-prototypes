#include "string_utils.h"
#include <ctype.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool starts_with(const char *str, const char *search) {
  size_t length = strlen(search);

  for (size_t i = 0; i < length; ++i) {
    if (str[i] != search[i]) {
      return false;
    }
  }

  return true;
}

bool ends_with(const char *str, const char *search) {
  size_t str_length = strlen(str);
  size_t search_length = strlen(search);

  for (size_t i = 0; i < search_length; ++i) {
    if (search[i] != str[str_length - search_length + i]) {
      return false;
    }
  }

  return true;
}

size_t get_file_length(FILE *file) {
  fseek(file, 0, SEEK_END);
  size_t size = ftell(file);
  rewind(file);

  return size;
}

void clear_string(char *str) {
  size_t size = strlen(str);
  if (size > 0) {
    memset(str, '\0', size);
  }
}

void extract_option(char *dest, const char *str, size_t start) {
  clear_string(dest);

  size_t index = start;
  while (isalnum(str[index])) {
    ++index;
  }

  strncpy(dest, &str[start], index - start);
}

size_t count_lines(const char *str) {
  if (strlen(str) == 0) {
    return 0;
  }

  size_t line_count = 0;

  const char *index = str;
  while ((index = strchr(index, '\n'))) {
    ++line_count;
    ++index;
  }

  return line_count;
}

char **split_lines(const char *str, size_t line_count) {
  char **lines = (char **)malloc(sizeof(char *) * line_count);

  const char *prev = str;
  const char *current = str;

  size_t line = 0;
  size_t char_count;

  while ((current = strchr(current, '\n'))) {
    char_count = current - prev;

    lines[line] = (char *)malloc(sizeof(char) * char_count);

    strncpy(lines[line], prev, current - prev);

    ++current;
    ++line;
    prev = current;
  }

  return lines;
}
