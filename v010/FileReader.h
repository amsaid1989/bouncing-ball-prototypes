#ifndef CONFIG_LOADER_H
#define CONFIG_LOADER_H

#include "string_utils.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

typedef struct {
  FILE *file;
  size_t size;
  size_t line_count;
  char *contents;
  char **lines;
} FileReader;

bool init_config_loader(FileReader *reader, const char *filename);
void destroy_config_loader(FileReader *reader);

#endif // !CONFIG_LOADER_H
