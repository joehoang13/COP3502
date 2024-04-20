#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Trie structure
struct Trie
{
    struct Trie* children[26];
    int count;
};

struct Trie *createTrie();

// Inserts the word to the trie structure
void insert(struct Trie *pTrie, char *word)
{
    struct Trie* currentNode = createTrie();
    currentNode = pTrie;
    for (int i = 0; i < strlen(word); i++) {
        char character = word[i];
        if (currentNode->children[character - 'a'] == NULL) {
            currentNode->children[character - 'a'] = createTrie();
        }
        currentNode->children[character - 'a']->count++;
        currentNode = currentNode->children[character - 'a'];
    }
}

// computes the number of occurances of the word
int numberOfOccurances(struct Trie *pTrie, char *word)
{
    struct Trie* currentNode = createTrie();
    currentNode = pTrie;
    for (int i = 0; i < strlen(word); i++) {
        char character = word[i];
        if (currentNode->children[character - 'a'] == NULL) {
            return 0;
        }
        currentNode = currentNode->children[character - 'a'];
    }
    return currentNode->count;
}

// deallocate the trie structure
struct Trie *deallocateTrie(struct Trie *pTrie)
{
    free(pTrie);
    pTrie = NULL;
    return pTrie;
}

// Initializes a trie structure
struct Trie *createTrie()
{
    struct Trie* node = (struct Trie*)malloc(sizeof(struct Trie));
    node->count = 0;
    for(int i = 0; i < 26; i++) {
        node->children[i] = NULL;
    }
    return node;
}

// this function will return number of words in the dictionary,
// and read all the words in the dictionary to the structure words
int readDictionary(char *filename, char **pInWords)
{
    char buffer[256];

    FILE* file = fopen(filename, "r");
    fgets(buffer, 256, file);
    int numWords = atoi(buffer); 
    for(int i = 0; i < numWords; i++) {
        fgets(buffer, 256, file);
        pInWords[i] = strdup(buffer);
    }
    return numWords;
}

int main(void)
{
	char *inWords[256];
	
	//read the number of the words in the dictionary
	int numWords = readDictionary("dictionary-1.txt", inWords);
	for (int i=0;i<numWords;++i)
	{
		printf("%s\n",inWords[i]);
	}
	
	struct Trie *pTrie = createTrie();
	for (int i=0;i<numWords;i++)
	{
		insert(pTrie, inWords[i]);
	}
	// parse lineby line, and insert each word to the trie data structure
	char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
	for (int i=0;i<5;i++)
	{
		printf("\t%s : %d\n", pWords[i], numberOfOccurances(pTrie, pWords[i]));
	}
	pTrie = deallocateTrie(pTrie);
	if (pTrie != NULL)
		printf("There is an error in this program\n");
    
	return 0;
}