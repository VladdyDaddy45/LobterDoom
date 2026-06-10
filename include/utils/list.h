#pragma once

#ifndef LIST_H
#define LIST_H


typedef struct {
    void** arr;
    int size;
} List;

List List_new();
void List_add(List* list, void* element);
void List_free(List* list);

#endif