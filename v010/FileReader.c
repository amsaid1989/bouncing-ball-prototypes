#include "FileReader.h"
#include "string_utils.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool init_config_loader(FileReader *loader, const char *filename) {
  *loader = (FileReader){NULL, 0, 0, NULL, NULL};

  loader->file = fopen(filename, "r");
  if (!loader->file) {
    printf("Failed to open file %s\n", filename);
    return false;
  }

  loader->size = get_file_length(loader->file);
  if (loader->size == 0) {
    printf("Empty configuration file\n");

    fclose(loader->file);

    return false;
  }

  loader->contents = (char *)malloc(loader->size);
  size_t count =
      fread(loader->contents, sizeof(char), loader->size, loader->file);
  if (count < loader->size) {
    printf("Failed to read the file contents\n");

    if (ferror(loader->file)) {
      perror("Error");
    }

    free(loader->contents);
    loader->contents = NULL;

    fclose(loader->file);

    return false;
  }

  loader->line_count = count_lines(loader->contents);
  loader->lines = split_lines(loader->contents, loader->line_count);

  fclose(loader->file);

  return true;
}

void destroy_config_loader(FileReader *loader) {
  if (loader->contents) {
    free(loader->contents);
    loader->contents = NULL;
  }

  if (loader->lines) {
    for (size_t i = 0; i < loader->line_count; ++i) {
      if (loader->lines[i]) {
        free(loader->lines[i]);
        loader->lines[i] = NULL;
      }
    }

    free(loader->lines);
    loader->lines = NULL;
  }
}
