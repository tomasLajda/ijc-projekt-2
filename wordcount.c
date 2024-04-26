// Author: Tomáš Lajda <xlajdat00>
// Date: 2024-04-25
// Description: Wordcount program

#include <stdio.h>
#include <stdlib.h>

// custom header files
#include "io.h"
#include "htab.h"

// I used this formula to determine the size of hash table
// Expected number of elements = 100,000
// Load factor = 0.7
// Initial hash table size = Expected number of elements / Load factor
// Initial hash table size = 100,000 / 0.7
// Initial hash table size ≈ 142,857
#define HTAB_SIZE 143000
#define MAX_WORD_LEN 255

void print_htab_pair(htab_pair_t *pair) {
    printf("%s\t%d\n", pair->key, pair->value);
}

int main() {
    htab_t *t = htab_init(HTAB_SIZE);
    if(t == NULL) {
        fprintf(stderr, "Error: Couldn't allocate memory for hash table.\n");
        return 1;
    }

    int charCount = 0;
    char word[MAX_WORD_LEN];
    bool overflow = false;
    while ((charCount = read_word(word, MAX_WORD_LEN, stdin)) != EOF) {
        if(charCount >= MAX_WORD_LEN) {
            overflow = true;
            fprintf(stderr, "Warning: Word is too long. Max length supported is: %d.\n", MAX_WORD_LEN);
        }

        if(word[0] != '\0') {
            htab_pair_t *pair = htab_lookup_add(t, word);
            if(pair == NULL) {
                fprintf(stderr, "Error: Couldn't allocate memory for new item.\n");
                htab_free(t);
                return 1;
            }

            (pair->value)++;
        }
    }
    
    htab_for_each(t, print_htab_pair);

    #ifdef STATISTICS 
    htab_statistics(t);
    #endif

    htab_free(t);
    return 0;
}
