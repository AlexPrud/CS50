/*------------------------------

PROGRAM

------------------------------*/

// includes
#include <stdio.h> // Standard library
#include <cs50.h> // get_string(), etc.
#include <ctype.h> // toupper(), etc.
#include <string.h> // strlen(), etc.
#include <math.h> // roundf(), etc.
#include <stdint.h> // uint8_t, etc.

// defines


// declare functions


// global variables

typedef struct node
{
    bool is_word;
    struct node *children[27];
}
node;

node *root;

void triedic(node *parent, FILE *dic);
bool checkword(node *parent, const char *word);
int convertnode(int *c);

int main(void)
{
    // load root node pointer
    root = malloc(sizeof(node));
    if (root == NULL)
    {
        printf("root pointer is NULL\n");
        return false;
    }

    // open dictionnary for reading
    FILE *dic;
    dic = fopen("dictionaries/small", "r");
    if (dic == NULL)
    {
        printf("Failed to load dictionary\n");
        return false;
    }

    // create dictionary (trie data structure)
    triedic(root, dic);

    // check word
    char *word;
    printf("string: ");
    word = get_string();
    bool checks = checkword(root, word);
    if (checks)
    {
        printf("%s is in the dic!\n", word);
    }
    else
    {
        printf("%s is in NOT the dic!\n", word);
    }

    return true;
}



void triedic(node *parent, FILE *dic)
// makes a dictionnary with the trie data structure [ici]
{
    int c;
    // for each letter
    for (c = fgetc(dic); c != EOF; c = fgetc(dic))
    {
        if (c == 10)
        {
            parent->is_word = true; // new word
            parent = root; // go back to root
        }

        // create nodes
        else if (isalpha(c) || c == 39)
        {
            // alphabetic conversion for the node pointers
            c = convertnode(&c);

            // if children is NULL, malloc a new node
            if (parent->children[c] == NULL)
            {
                parent->children[c] = malloc(sizeof(node));
            }
            parent = parent->children[c];
        }
    }
}

bool checkword(node *parent, const char *word)
{
    // size of word
    int wordsize = strlen(word);
    printf("wordsize is: %i\n", wordsize);

    // check each letter
    int c;
    for (int i = 0; i < wordsize; i++)
    {
        c = word[i];
        c = convertnode(&c);
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

int convertnode(int *c)
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
    return *c;
}