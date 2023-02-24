#ifndef LIST_H
#define LIST_H

#include <stdbool.h>
#include <stdlib.h>

typedef enum {
    String,
    Int,
    Double,
} types;

typedef struct Node {
    void*         value;
    struct Node*  next;
} Node;

typedef struct {
    Node* head;
    types type;
} list;
             
list         ListCreate   (types type);
size_t       ListSize     (const list* lst);
size_t       ListCount    (const list* lst, const void* elem);
bool         ListContains (const list* lst, const void* elem);
void         ListPushBack (list* lst, const void* elem);
void         ListErase    (list* lst, const void* elem);
void         ListPrint    (const list* lst);
void         ListDestroy  (list* lst);

#endif // LIST_H

