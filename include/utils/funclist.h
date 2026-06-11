#pragma once

#ifndef FUNCLIST_H
#define FUNCLIST_H

typedef void (*function)(void);

typedef struct {
    void** arr;
    int size;
} FuncList;

/* i'll let you have a guess what this returns */
FuncList FuncList_new();
/* returns true if successfully added the element */
int FuncList_add(FuncList* list, void* function);
void FuncList_free(FuncList* list);

#endif