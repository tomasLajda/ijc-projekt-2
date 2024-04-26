// Author: Tomáš Lajda <xlajdat00>
// Date: 2024-04-12
// Description: Tail program

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_LINE_LENGTH 2048
#define DEFAULT_SIZE_BUFFER 10

typedef struct cycle_buffer {
  size_t start;
  size_t end;
  size_t size;
  char** lines;
} cycle_buffer_t;

// Cycle buffer initialization
cycle_buffer_t* cbuf_create(size_t n) {
  cycle_buffer_t* cb = malloc(sizeof(cycle_buffer_t));

  if(cb == NULL) {
    fprintf(stderr, "Error: Memory allocation failed\n");
    exit(EXIT_FAILURE);
  }

  cb->start = 0;
  cb->end = 0;
  cb->size = n;

  cb->lines = malloc(cb->size * sizeof(char*));

  if(cb->lines == NULL) {
    fprintf(stderr, "Error: Memory allocation failed\n");
    free(cb);
    exit(EXIT_FAILURE);
  }

  for (size_t i = 0; i < cb->size; i++) {
    cb->lines[i] = NULL;
  }

  return cb;
} 

// Free string line
void line_free(char* line) {
  if(line != NULL) {
    free(line);
    line = NULL;
  }
}

// Free cycle buffer
void cbuf_free(cycle_buffer_t* cb) {
  for (size_t i = 0; i < cb->size; i++) {
    if(cb->lines[i] != NULL) {
      line_free(cb->lines[i]);
    }
  }

  free(cb->lines);
  cb->lines = NULL;
  free(cb);
  cb = NULL;
}

// Put line into cycle buffer
void cbuf_put(cycle_buffer_t* cb, char* line) {
  if(cb->lines[cb->end] != NULL) {
    line_free(cb->lines[cb->end]);
  }

  cb->lines[cb->end] = malloc(strlen(line) + 1);
  if(cb->lines[cb->end] == NULL) {
    cbuf_free(cb);
    fprintf(stderr, "Error: Memory allocation failed\n");
    exit(EXIT_FAILURE);
  }

  strcpy(cb->lines[cb->end], line);

  if(cb->end + 1 == cb->size) {
    cb->end = 0;
    cb->start = 0;
  } else {
    if(cb->end == cb->start && cb->lines[cb->size - 1] != NULL) {
      cb->start++;
    }

    cb->end++;
  }
}

// Get line from cycle buffer
char* cbuf_get(cycle_buffer_t* cb) {
  if(cb->lines[cb->start] == NULL) {
    return NULL;
  }

  if(cb->start + 1 == cb->size) {
    cb->start = 0;
    return cb->lines[cb->size - 1];
  } else {
    cb->start++;
    return cb->lines[cb->start - 1];
  }
}

int main(int argc, char* argv[]) {
  FILE *file;
  int bufferSize = DEFAULT_SIZE_BUFFER;

  // Parse arguments
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

  cycle_buffer_t* cb = cbuf_create(bufferSize);

  char line[MAX_LINE_LENGTH];
  bool warningPrinted = false;

  // Read lines from file
  while(fgets(line, sizeof(line), file) != NULL) {
    cbuf_put(cb, line);

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

  // Print lines from cycle buffer
  do {
    char* line = cbuf_get(cb);
    if(line == NULL) {
      break;
    }

    printf("%s", line);
  } while (cb->start != cb->end && line != NULL);

  cbuf_free(cb);
  return 0;
}