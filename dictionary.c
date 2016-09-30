/**
 * hashmap.c
 *
 * Implements a dictionary's functionality.
 */

#include <stdbool.h>
#include "dictionary.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <limits.h>


// length of hashtable 
//define HASHLENGTH 80000
// node* hashtable[HASHLENGTH] = {NULL};


// initialize hashmap of fixed length HASHLENGTH
hashmap* constructor(int length)
{
    hashmap* hashmap_instance = malloc(sizeof(hashmap));
    hashmap_instance->table_size = length;
    hashmap_instance->size = 0;
    hashmap_instance->table = malloc(sizeof(node)*length);
    // node* hashtable[length];
    for (int i = 0; i< length; i++)
        hashmap_instance->table[i] = NULL;
    return hashmap_instance;

}

// using djb2 hash function; returns an int based on the string
int hash(const char* str, int HASHLENGTH)
{
    unsigned long hash = 5381;
    int c;

    while ((c = *str++))
        hash = ((hash << 5) + hash) + c;    
    
    return (hash % HASHLENGTH);
}

// very simple hash using first letter of string. Used for testing purposes
// to test linked list in the case of a collision
int hash_1(const char* str, int HASHLENGTH)
{
    return ((int)(str) %HASHLENGTH);
}

/**
 * Returns a pointer to entire node if key is in hashmap else NULL.
 */
void* get_node(const char* key, hashmap* map)
{
    
    /* declare a node pointer and set point it to the correct index of the 
    hash table, as determined by the hash function */
    node* currentNode;
    currentNode = *((map->table)+hash(key, map->table_size));
    
    // check if value at hashtable is NULL, meaning the key is not in the dictionary
    //  if so, return false
    if (currentNode == NULL)
        return NULL;
    
    /* if there is only one node at this spot in the hash table, check the key
    at this node */
    else if (currentNode->next == NULL && (strcmp(currentNode->key,key)== 0))
        return currentNode;
    
    // iterate through linked list 
    else {
        while(currentNode != NULL)
        {
            // check if the key matches what we want
            if (strcmp(currentNode->key,key)== 0)
            {
                return currentNode;
            }
            // otherwise go to the next node
            currentNode = currentNode->next;
        }
        return NULL;
    }
}
/**
 * Returns a pointer to data if key is in hashmap else NULL.
 */
 void* get(const char* key, hashmap* map)
{
    node* ptr= get_node(key, map);
    if (ptr)
        return ptr->data;
    return NULL;
}
/*
 * Stores a key-value pair in the hashmap. Returns true if successful, else false
 */ 

bool set(char* key, void* value, hashmap* map) 
{
    // if the key is already in the hashmap, return false
    if (get_node(key, map) != NULL)
        return false;

    node* newNode = malloc(sizeof(node));

    // if malloc failed for some reason, return false
    if (newNode == NULL)
        return false;

    else 
    {
        // put the key-value pair in a new node 
        newNode->key = key;
        newNode->data = value;
        newNode->prev = NULL;
    
        // index from hash function
        int index = hash(key, map->table_size);
        
        // if the index is empty, put newnode at the first position
        if (*((map->table) + index) == NULL)
        {
            newNode->next = NULL;

        }
        
        // otherwise insert it at the beginning, move the key-value pair that 
        // was originally there down one in the linked list
        else 
        {
            newNode->next = (map->table)[index];
            newNode->next->prev = newNode;
        }
        (map->table)[index] = newNode;

        // increase currently utilized size by one
        map->size ++;
        return true;
    }
}


/**
 * Deletes the value associated with this key, returning value on success 
 * or null if key has no value.
 */
void* delete(char* key, hashmap* map)
{
    // set a cursor equal to the value of get(key)
    node* cursor = get_node(key, map);

    // if key wasn't found, just return null
    if (cursor == NULL)
        return NULL;

    // otherwise we need to delete the value and return it
    else 
    {
        // let's save the value we need 
        void* val = cursor->data;

        // removing the cursor
        if ((cursor->next) != NULL)
            cursor->next->prev = cursor->prev;
        if ((cursor->prev) != NULL)
            cursor->prev->next = cursor->next;
        else
            *((map->table) +hash(key, map->table_size)) = cursor->next;

        // free the node 
        free(cursor);

        // subtract one from currently used size
        map->size--;

        // return the value
        return val;
    }

}

/**
 * Returns the ratio of usage of the hashmap, as a float.
 */
float load(hashmap* map)
{
    return ((float)map->size) / map->table_size;
}

/**
 * Frees the hashmap from memory.
 */
bool free_hashmap(hashmap* map)
{
    free(map->table);
    free(map);
    return 0;
}
