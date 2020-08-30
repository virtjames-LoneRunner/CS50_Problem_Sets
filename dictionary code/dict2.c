// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
// Math using all the letters so it requires a lot of buckets
const unsigned int N = (LENGTH + 1) * 'z';

// Hash table
node *table[N];

// Keep track of the number of words
int number_of_words = 0;

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    int input_index = hash(word);
    node *cursor = NULL;
    cursor = table[input_index];

    while (cursor != NULL)
    {
        if (strcasecmp(cursor->word, word) == 0)
        {
            return true;
        } 
        cursor = cursor->next;
        
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // Hash
    unsigned int hash_index = 0;
    int length_of_word = strlen(word);

    for (int i = 0; i < length_of_word; i++)
    {
        hash_index += tolower(word[i]);
    }
    return (hash_index % N);
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Variables
    int index;
    char word[LENGTH];

    // Load dictionary
    FILE *file = fopen(dictionary, "r"); 

    // Check if successful or not
    if (file == NULL)
    {
        return false;
    }
    
    while (fscanf(file, "%s", word) != EOF)
    {
        node *n = malloc(sizeof(node));

        // Check if malloc returned a value
        if (n == NULL)
        {
            return false;
        }

        // Copy string from dictionary to table
        strcpy(n->word, word);
        //n->next = NULL;
        
        // Use hash function to return hash
        index = hash(word);

        // Insert node to hash table
        // If first index is empty, overwrite it
        if (table[index] == NULL)
        {
            table[index] = n;
        }
        // Else insert new node to beginning of linked list
        else
        {
            n->next = table[index];
            table[index] = n;
        }
        // Keep track of the number of loaded words
        number_of_words++;
        
    }
    fclose(file);
    
    
    // Return true to signify that dictionary properly loaded
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // Simple return the number_of_words variable as it was counting each loaded word
    return number_of_words;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    node *head = NULL;
    node *cursor = NULL;
    node *tmp = NULL;
    // Unload
    for (int i = 0; i < N; i++)
    {
        head = table[i];
        cursor = head;
        tmp = cursor;

        while (cursor != NULL)
        {
            cursor = cursor->next;
            free(tmp);
            tmp = cursor;
        }
    }
    return true;
}
