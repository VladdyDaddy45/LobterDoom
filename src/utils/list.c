//This entire file is just for dynamic void pointer lists.

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "utils/list.h"

List List_new() {
    List list = {
        malloc(1),
        0,
    };

    return list;
}

void List_add(List* list, void* element)
{
    list->size++;

    int max = list->size;
    void** buffer = malloc(list->size * sizeof(void*));
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
}

void List_free(List* list) 
{
    for (int i = 0; i < list->size; i++) 
    {
        list->arr[i] = NULL;
    }
    free(list->arr);
    list->size = 0;
}