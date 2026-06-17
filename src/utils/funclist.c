//This entire file is just for dynamic void pointer lists.

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

#include "utils/funclist.h"

extern double PI;

FuncList FuncList_new() {
    FuncList list = {
        NULL,
        0,
    };

    return list;
}

/* returns -1 if failed to add the element */
int FuncList_add(FuncList* list, void* element)
{ 
    //element = (void (*)(void))element;

    void** buffer = malloc((list->size+1) * sizeof(void*));
    if (buffer == NULL) {
        return -1;
    }

    if (list->arr == NULL) { // checking if the list is new
        buffer[0] = element;
    } else {
        for (int i = 0; i < list->size; i++) {
            buffer[i] = list->arr[i];
        }
        free(list->arr);
        buffer[list->size] = element;
    }
    
    list->arr = buffer;
    list->size++;
    return 0;
}

void* FuncList_get(FuncList* list, int index) {
    return list->arr[index];
}

void FuncList_free(FuncList* list) 
{
    for (int i = 0; i < list->size; i++) 
    {
        list->arr[i] = NULL;
    }
    free(list->arr);
    list->size = 0;
}