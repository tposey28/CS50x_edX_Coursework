/**
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 */
#include "dictionary.h"

// front of dictionary
dict_trie* dict_front;
// size of dictionary
unsigned int word_count;

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    // make sure load has been called
    if (dict_front == NULL) return false;
    dict_trie* curr = dict_front;
    // grab the first char
    int index = 0;
    int c = word[index];
    // iterate until terminating char
    while (c != '\0')
    {
        // reduce case (dictionary is lower case), or if an apostrophe reassign for mapping
        c = (c != '\'') ? tolower(c) : 123;
        // if not a leaf node and if the next letter exists, traverse
        if (curr->children != NULL && curr->children[c - 97] != NULL) 
        {
            curr = curr->children[c - 97];
        } else { // otherwise return, since the word is not present
            return false;
        }
        index++;
        c = word[index];
    }
    // return if the current node is truly the end of a word
    return curr->end;
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    // open dictionary file and verify
    FILE* dict = fopen(dictionary, "r");
    if (dict == NULL) return false;
    // allocate the root of our dictionary and verify
    dict_front = (dict_trie*) calloc(1, sizeof(dict_trie));
    if (dict_front == NULL) return false;
    // read char by char through the whole dictionary file, ending at EOF
    dict_trie* curr = dict_front;
    for (int c = fgetc(dict); c != EOF; c = fgetc(dict))
    {
        // if the letter is alphabetical or an apostrophe, add
        if (isalpha(c) || c == '\'')
        {
            // reduce to lower, or if an apostrophe reassign for mapping
            c = (c == '\'') ? 123 : tolower(c);
            // if current is a leaf node, allocate the children array and verify
            if (curr->children == NULL) 
            {
                curr->children = (dict_trie**) calloc(1, 27*sizeof(dict_trie*));
                if (curr->children == NULL) return false;
            }
            // if the letter hasn't been encountered yet, allocate a new node and verify
            if (curr->children[c - 97] == NULL) 
            {
                curr->children[c - 97] = (dict_trie*) calloc(1, sizeof(dict_trie));
                if (curr->children[c - 97] == NULL) return false;
            }
            // traverse down the trie
            curr = curr->children[c - 97];
        } else // otherwise it must have been another symbol and thus the word has ended
        {
            // make sure we actually started a word
            if (curr != dict_front)
            {
                word_count++;
                curr->end = true;
                curr = dict_front;
            }
        }
    }
    fclose(dict);
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    return word_count;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    // make sure load has been called
    if (dict_front == NULL)
    {
        return false;
    }
    // free the trie and set count to 0
    word_count = 0;
    free_all(dict_front);
    dict_front = NULL;
    return true;
}

/**
 * Given a node, it will free it and all of its children.
 */
void free_all(dict_trie* curr)
{
    // if node is not a leaf node, free all children that exist and the array
    if (curr->children != NULL)
    {
        for (int i = 0; i < 27; i++)
        {
            if (curr->children[i] != NULL)
            free_all(curr->children[i]);
        }
        free(curr->children);
    }
    // free given node
    free(curr);
}
