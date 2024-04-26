// Author: Tomáš Lajda <xlajdat00>
// Date: 2024-04-25
// Description: Reads word from file

#include "io.h"

int read_word(char *s, int max, FILE *f) {
    if(f == NULL) {
        fprintf(stderr, "Error: couldn't open the file.\n");
        return EOF;
    }

    int i = 0;
    int c;
    for(i = 0; i < max; i++) {
        c = fgetc(f);

        if(c == EOF) {
            return EOF;
        }

        if(isspace(c)) {
            s[i] = '\0';
            break;
        }

        s[i] = c;

        if(i == max - 1) {
            s[i] = '\0';
            // Skip the rest of the word
            while ((c = fgetc(f)) != EOF && !isspace(c)){
                i++;
            }
        }
    }

    return i;
}