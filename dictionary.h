/**
 * dictionary.h
 *
 * Susan Xu
 *
 * Declares a hashmap's functionality. Because I chose to implement this in C, 
 * each function after constructor will have to take as an additioanl argument 
 * the pointer to the hashmap being acted upon. 
 */

#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <stdbool.h>


// defines a node for each element of our hashmap
typedef struct node
{
    // for now, we use a void pointer to our data because we don't know 
    // what type the data is
    char* key;
	void* data;

    // in the case of collisions, we will chain on the next node as part of a 
    // doubly linked list
	struct node* next;
    struct node* prev;
} node;

// defines a hashmap: total size, current size, and the actual table 
typedef struct hashmap{
    int table_size;
    int size;

    // the actual hash part will be an array of nodes
    node** table;
} hashmap;


/**
 * Constructs a hashmap into memory.  Returns true if successful else false.
 */
hashmap* constructor(int length);

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
bool set(char* key, void* value, hashmap* map);

/**
 * Returns a pointer to the value if key is in hashmap else returns NULL.
 */
void* get(const char* key, hashmap* map);

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
void* delete(char* key, hashmap* map);

/**
 * Returns the ratio of usage of the hasmap.
 */
float load(hashmap* map);

#endif // DICTIONARY_H
