/**
 * Tests.c
 *
 * Susan Xu
 *
 * Implements and tests a hashmap
 */

#include <ctype.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "dictionary.h"
// int to string function, credits to Robert Jan Schaper:
char* itoa(int val, int base){
    static char buf[32] = {0};
    int i = 30;
    for(; val && i ; --i, val /= base)
        buf[i] = "0123456789abcdef"[val % base];
    return &buf[i+1];
    }


int main(int argc, char* argv[])
{
    // creating an empty hashmap
    hashmap* map1 = constructor(10);

    // creating some random data
    int* int_ptr = malloc(sizeof(int));
    *int_ptr = 1;
    int* int_ptr2 = malloc(sizeof(int));
    *int_ptr2 = 2;
    char* char_ptr = malloc(sizeof(char));
    *char_ptr = 'a';

    // testing for an empty value
    assert(get("test", map1) == NULL);

    // inserting some stuff
    assert(set("test", (void*) int_ptr, map1));
    assert(get("test", map1) == (void*)int_ptr);

    // check that load is .1 
    assert(fabs(load(map1) - .1) < 0.0001);

    // try deleting at head of list
    assert(delete("test", map1) == (void*)int_ptr);

    // check load is 0
    assert(fabs(load(map1)) < 0.0001);

    // add the pointer back in
    assert(set("test", (void*) int_ptr, map1));

    // testing for linked list behavior at collision
    assert(set("test2", (void*) int_ptr2, map1));

    // check gets for multiple in a list
    assert(get("test", map1) == (void*)int_ptr);
    assert(get("test2", map1) == (void*)int_ptr2);

    // check load is .2
    assert(fabs(load(map1) - .2) < 0.00001);

    // delete 
    assert(delete("test", map1) == (void*)int_ptr);
    // check that load is .1 
    assert(fabs(load(map1) - .1) < 0.0001);
        // delete 
    assert(delete("test2", map1) == (void*)int_ptr2);
    // check that load is 0
    assert(fabs(load(map1)) < 0.0001);

    free(map1);

    // let's try a bigger example
    hashmap* map2 = constructor(1000);

    for (int i = 0; i < 1000; i++) {
        set(itoa(i, 8), (void*) int_ptr, map2);
    }
    // check load is 1
    assert(fabs(load(map1) - 1.0) < 0.00001);

    // delete 
    for (int i = 0; i < 1000; i++) {
        delete(itoa(i,8), map2);
    }

    // check load is 0
    assert(fabs(load(map1)) < 0.00001);




}

