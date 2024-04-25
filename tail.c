#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_LINE_LENGTH 2048
#define DEFAULT_SIZE_BUFFER 10

typedef struct cb
{
  size_t start;
  size_t end;
  size_t size;
  char** lines;
} cb;

cb* cbuf_create(size_t n) {
  cb* buffer = malloc(sizeof(cb));

  if(buffer == NULL) {
    fprintf(stderr, "Error: Memory allocation failed\n");
    exit(EXIT_FAILURE);
  }

  buffer->start = 0;
  buffer->end = 0;
  buffer->size = n;

  buffer->lines = malloc(buffer->size * sizeof(char*));

  if(buffer->lines == NULL) {
    fprintf(stderr, "Error: Memory allocation failed\n");
    free(buffer);
    exit(EXIT_FAILURE);
  }

  for (size_t i = 0; i < buffer->size; i++) {
    buffer->lines[i] = NULL;
  }

  return buffer;
} 

void line_free(char* line) {
  if(line != NULL) {
    free(line);
    line = NULL;
  }
}

void cbuf_free(cb* buffer) {
  for (size_t i = 0; i < buffer->size; i++) {
    if(buffer->lines[i] != NULL) {
      line_free(buffer->lines[i]);
    }
  }

  free(buffer->lines);
  buffer->lines = NULL;
  free(buffer);
  buffer = NULL;
}

void cbuf_put(cb* buffer, char* line) {
  if(buffer->lines[buffer->end] != NULL) {
    line_free(buffer->lines[buffer->end]);
  }

  buffer->lines[buffer->end] = malloc(strlen(line) + 1);
  if(buffer->lines[buffer->end] == NULL) {
    cbuf_free(buffer);
    fprintf(stderr, "Error: Memory allocation failed\n");
    exit(EXIT_FAILURE);
  }

  strcpy(buffer->lines[buffer->end], line);

  if(buffer->end + 1 == buffer->size) {
    buffer->end = 0;
    buffer->start = 0;
  } else {
    if(buffer->end == buffer->start && buffer->lines[buffer->size - 1] != NULL) {
      buffer->start++;
    }

    buffer->end++;
  }
}

char* cbuf_get(cb* buffer) {
  if(buffer->lines[buffer->start] == NULL) {
    return NULL;
  }

  if(buffer->start + 1 == buffer->size) {
    buffer->start = 0;
    return buffer->lines[buffer->size - 1];
  } else {
    buffer->start++;
    return buffer->lines[buffer->start - 1];
  }
}

int main(int argc, char* argv[]) {
  FILE *file;
  int bufferSize = DEFAULT_SIZE_BUFFER;

  if (argc > 2 && strcmp(argv[1], "-n") == 0) {
    char *endptr;
    bufferSize = strtol(argv[2], &endptr, 10);

    if (*endptr != '\0' || bufferSize < 0) {
      fprintf(stderr, "Error: Invalid buffer size\n");
      exit(EXIT_FAILURE);
    }

    if(argc == 4) {
      file = fopen(argv[3], "r");

      if (file == NULL) {
        fprintf(stderr, "Error: Could not open file %s\n", argv[3]);
        exit(EXIT_FAILURE);
      }
    } else if (argc == 3) {
      file = stdin;
    } else {
      fprintf(stderr, "Usage: %s [-n number] [file]\n", argv[0]);
      exit(EXIT_FAILURE);
    }
  } else if (argc == 2) {
    file = fopen(argv[1], "r");
    if (file == NULL) {
      fprintf(stderr, "Error: Could not open file %s\n", argv[1]);
      exit(EXIT_FAILURE);
    }
  } else if (argc == 1) {
    file = stdin;
  }
  else {
    fprintf(stderr, "Usage: %s [-n number] [file]\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  if(bufferSize == 0) {
    fclose(file);
    exit(EXIT_SUCCESS);
  }

  cb* buffer = cbuf_create(bufferSize);

  char line[MAX_LINE_LENGTH];
  bool warningPrinted = false;

  while(fgets(line, sizeof(line), file) != NULL) {
    cbuf_put(buffer, line);

    size_t len = strlen(line);

    if(line[len - 1] != '\n') {
      if(!feof(file)) {
        if(!warningPrinted) {
          fprintf(stderr, "Warning: line is too long, only the first %d characters were saved.\n", MAX_LINE_LENGTH - 1);
          warningPrinted = true;
        }
        
        int ch;
        while((ch = getc(file)) != '\n' && ch != EOF);
      }
    }
  }

  fclose(file);

  do {
    char* line = cbuf_get(buffer);
    if(line == NULL) {
      break;
    }

    printf("%s", line);
  } while (buffer->start != buffer->end && line != NULL);

  cbuf_free(buffer);
  exit(EXIT_SUCCESS);
}