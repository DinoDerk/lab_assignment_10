#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPHABET_SIZE 26

struct Trie {
    int count;
    struct Trie *children[ALPHABET_SIZE];
};

// Initialize a new Trie node
struct Trie *newTrieNode() {
    struct Trie *node = (struct Trie *)malloc(sizeof(struct Trie));
    node->count = 0;
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        node->children[i] = NULL;
    }
    return node;
}

// Insert a word into the Trie
void insert(struct Trie **ppTrie, char *word) {
    struct Trie *pTrie = *ppTrie;
    if (pTrie == NULL) {
        pTrie = newTrieNode();
        *ppTrie = pTrie;
    }
    int len = strlen(word);
    for (int i = 0; i < len; i++) {
        int index = word[i] - 'a';
        if (pTrie->children[index] == NULL) {
            pTrie->children[index] = newTrieNode();
        }
        pTrie = pTrie->children[index];
    }
    pTrie->count++;
}

// Search for the number of occurrences of a word in the Trie
int numberOfOccurrences(struct Trie *pTrie, char *word) {
    struct Trie *temp = pTrie;
    int len = strlen(word);
    for (int i = 0; i < len; i++) {
        int index = word[i] - 'a';
        if (temp->children[index] == NULL) {
            return 0;
        }
        temp = temp->children[index];
    }
    return temp->count;
}

// Deallocate the memory allocated for the Trie
struct Trie *deallocateTrie(struct Trie *pTrie) {
    if (pTrie == NULL) {
        return NULL;
    }
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        pTrie->children[i] = deallocateTrie(pTrie->children[i]);
    }
    free(pTrie);
    return NULL;
}

int main(void) {
    struct Trie *trie = NULL;

    // read the number of the words in the dictionary
    // parse line by line, and insert each word to the trie data structure
    char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
    for (int i = 0; i < 5; i++) {
        insert(&trie, pWords[i]);
    }

    // search for the number of occurrences of each word in the Trie
    for (int i = 0; i < 5; i++) {
        printf("\t%s : %d\n", pWords[i], numberOfOccurrences(trie, pWords[i]));
    }

    trie = deallocateTrie(trie);
    if (trie != NULL) {
        printf("There is an error in this program\n");
    }

    return 0;
}