#ifndef LIST_H
#define LIST_H

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
void         ListPushBack (const void* elem, list* lst);
unsigned int ListCount    (const void* elem, const list* lst);
void         ListErase    (const void* elem, list* lst);
void         ListPrint    (const list* lst);
void         ListDestroy  (list* lst);

#endif // LIST_H

