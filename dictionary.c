// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dictionary.h"

// Represents number of children for each node in a trie
#define N 27

// Hash function
unsigned int hash(char c)
{
    if (c == '\'')
    {
        return 26;
    }
    else
    {
        return (tolower(c) - 'a');
    }
}

// Represents a node in a trie
typedef struct node
{
    char word[LENGTH + 1];
    struct node *children[N];
}
node;

// Declares the "create_node()" function
node *create_node(void);


// Declares the clean function used in the 'unload' function
bool clean(node *cursor);

// Represents a trie
node *root;

// Keeps track of the number of words uploaded
unsigned int words = 0;

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Initialize trie
    root = malloc(sizeof(node));
    if (root == NULL)
    {
        return false;
    }
    root->word[0] = '\0';
    for (int i = 0; i < N; i++)
    {
        root->children[i] = NULL;
    }

    // Open dictionary
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        unload();
        return false;
    }

    // Buffer for a word
    char word[LENGTH + 1];

    // Insert words into trie
    while (fscanf(file, "%s", word) != EOF)
    {
        node *cursor = root;
        for (int j = 0, length = strlen(word); j < length; j++)
        {
            int h = hash(word[j]);
            // Checks if the children is NULL
            if (cursor->children[h] == NULL)
            {
                // creates a new node
                node *new_node = create_node();
                if (new_node == NULL)
                {
                    unload();
                    return false;
                }

                // Links the children[h] to point to the newly created node
                cursor->children[h] = new_node;

                // Set the cursor to point to its correspondant node
                cursor = cursor->children[h];
            }
            // The children is not NULL, thus the cursor is moved to the pointed adress
            else
            {
            cursor = cursor->children[h];
            }
        }

        // Writes the word in the dictionary in its correspondant node
        strcpy(cursor->word, word);
        words++;
    }

    // Close dictionary
    fclose(file);

    // Indicate success
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return words;
}

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    int length = strlen(word);

    // Turns the word obtained from the text into an all-lowercase word
    char lowercase_word[length + 1];
    strcpy(lowercase_word, word);
    for (int j = 0; j < length; j++)
    {
        lowercase_word[j] = tolower(lowercase_word[j]);
    }

    // Navigates through the trie searching for the word in the dictionary
    node *cursor = root;
    for (int i = 0; i < length; i++)
    {
        int h = hash(word[i]);
        if (cursor->children[h] != NULL)
        {
            cursor = cursor->children[h];
        }
        else
        {
            return false;
        }
    }

    // Compares the string storaged in the 'word' section of the struct at the final node
    if ((strcmp(cursor->word, lowercase_word) == 0))
    {
        return true;
    }
    else
    {
        return false;
    }
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    node *cursor = root;

    if(clean(cursor))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool clean(node *cursor)
{
    for (int i = 0; i < N; i++)
    {
        if (cursor->children[i] != NULL)
        {
            clean(cursor->children[i]);
        }
    }
    free(cursor);
    return true;
}

node *create_node(void)
{
    node *new_node = malloc(sizeof(node));
    if (new_node == NULL)
    {
        return NULL;
    }
    // Empties the newly created node
    new_node->word[0] = '\0';
    for (int i = 0; i < N; i++)
    {
        new_node->children[i] = NULL;
    }

        // Success
    return new_node;
}

