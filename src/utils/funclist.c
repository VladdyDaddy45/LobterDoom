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
    bool successfulMalloc = false;
    bool newList = false;

    // swap out for list->arr == NULL when finished
    if (list->arr == NULL) {
        newList = true;
    }

    void** buffer = malloc((list->size+1) * sizeof(void*));
    if (buffer == NULL) {
        printf("List memory allocation failed\n");
        return -1;
    }

    if (newList) {
        buffer[0] = element;
    } else {
        for (int i = 0; i < list->size; i++) {
            buffer[i] = list->arr[i];
        }
        buffer[list->size+1] = element;
    }
    
    list->size++;
    return 0;

    /*
    int max = list->size;
    void** buffer = malloc(list->size * sizeof(void*));
    if (buffer == NULL) {
        printf("List memory allocation failed");
        list->size--;
        return (void)NULL;
    }

    for (int i = 0; i < list->size; i++)
    {
        if (i == sizeof(list->arr)-1) {
            buffer[max] = element;
            break;
        }
        buffer[i] = list->arr[i];
    }

    List_free(list);
    list->arr = buffer;
    */
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