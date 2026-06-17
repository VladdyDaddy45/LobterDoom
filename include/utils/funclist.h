#pragma once

#ifndef FUNCLIST_H
#define FUNCLIST_H

typedef void (*AnyFunc)(void);

typedef struct {
    void** arr;
    int size;
} FuncList;

/* i'll let you have a guess what this returns */
FuncList FuncList_new();
/* returns true if successfully added the element */
int FuncList_add(FuncList* list, void* element);
void* FuncList_get(FuncList* list, int index);
void FuncList_free(FuncList* list);

#endif