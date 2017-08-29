/**
 * Implements a dictionary's functionality.
 */

#include <stdbool.h>
#include <stdio.h>
#include "dictionary.h"

// functions
void initnode(node *node);
void triedic(node *parent, FILE *dic);
bool checkword(node *parent, const char *word);
void convertnode(int *c);
bool unloaddic(node *parent);

// global variables
int wordcount = 0;
FILE *dic;

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char *word)
{
    bool checks = checkword(root, word);
    if (checks)
    {
        return true;
    }
    return false;
}

/**
 * Loads dictionary into memory. Returns true if successful else false.
 */
bool load(const char *dictionary)
{
    // load root node pointer
    root = malloc(sizeof(node));
    initnode(root);
    if (root == NULL)
    {
        return false;
    }

    // open dictionnary for reading
    dic = fopen(dictionary, "r");
    if (dic == NULL)
    {
        return false;
    }

    // create dictionary (trie data structure)
    triedic(root, dic);

    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    return wordcount;
}

/**
 * Unloads dictionary from memory. Returns true if successful else false.
 */
bool unload(void)
{
    bool unloadcheck = unloaddic(root);
    fclose(dic);
    if (unloadcheck)
    {
        return true;
    }
    return false;
}

void triedic(node *parent, FILE *dic)
// Makes a dictionnary with the trie data structure
{
    int c;
    // for each letter
    for (c = fgetc(dic); c != EOF; c = fgetc(dic))
    {
        if (c == 10)
        {
            parent->is_word = true; // new word
            parent = root; // go back to root
            wordcount++;
        }

        // create nodes
        else if (isalpha(c) || c == 39)
        {
            // alphabetic conversion for the node pointers
            convertnode(&c);

            // if children is NULL, malloc a new node
            if (parent->children[c] == NULL)
            {
                parent->children[c] = malloc(sizeof(node));
                initnode(parent->children[c]);
            }
            parent = parent->children[c];
        }
    }
}

bool checkword(node *parent, const char *word)
// Checks if a given word is in the dictionary
{
    // size of word
    int wordsize = strlen(word);

    // check each letter
    int c;
    for (int i = 0; i < wordsize; i++)
    {
        c = word[i];
        convertnode(&c);
        if (parent->children[c] == NULL)
        {
            return false;
        }
        else
        {
            parent = parent->children[c];
        }
    }

    // check word
    if (parent->is_word == true)
    {
        return true;
    }
    return false;
}

void convertnode(int *c)
// alphabetic conversion for the node pointers
{
    // a-z or A-Z = 0-25
    if (isalpha(*c))
    {
        *c = toupper(*c) - 65;
    }

    // apostrophe = 26
    else if (*c == 39)
    {
        *c = 26;
    }
}

bool unloaddic(node *parent)
// Unloads the dictionary, freeing up the memory.
{
    if (parent == NULL)
    {
        return false;
    }

    for (int i = 0; i < 27; i++)
    {
        if (parent->children[i] != NULL)
        {
            unloaddic(parent->children[i]);
        }
    }

    // memset(parent, 0, sizeof(node));
    free(parent);
    // parent = NULL;
    return true;
}

void initnode(node *parent)
// Initialise a node, setting all the pointers to NULL.
{
    parent->is_word = false;
    for (int i = 0; i < 27; i++)
    {
        parent->children[i] = NULL;
    }
}
