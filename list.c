#include "list.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void* CreateValue(const void* value, types t) {
    void* ptr = NULL;
    size_t len;

    switch (t) {
        case String:
            /* +1 for '\0' */
            len = strlen((char*)value) + 1;
            ptr = malloc(len * sizeof(char));
            if (ptr == NULL) {
                printf("Cannot allocate memory\n");
                exit(1);
            }
            memcpy(ptr, value, len);
            return ptr;
        case Int:
            ptr = malloc(sizeof(int));
            if (ptr == NULL) {
                printf("Cannot allocate memory\n");
                exit(1);
            }
            *(int*)ptr = *(int*)value;
            return (void*) ptr;
        case Double:
            ptr = malloc(sizeof(double));
            if (ptr == NULL) {
                printf("Cannot allocate memory\n");
                exit(1);
            }
            *(double*)ptr = *(double*)value;
            return (void*) ptr;
        default:
            printf("Bad type for allocate memmory\n");
            exit(1);
    }
}

Node* NodeCreate(const void* value, types type) {
    Node* n = malloc(sizeof(Node));
    if (n == NULL) {
        printf("Cannot allocate memory\n");
        exit(1);
    }
    
    n->value = CreateValue(value, type); 
    n->next  = NULL;
    return n;
}

void NodeDestroy(Node* n) {
    if (n == NULL) return;
    free(n->value);
    free(n);
}

list*  ListCreate(types type) {
    list* l = malloc(sizeof(list));
    if (l == NULL) {
        printf("Cannot allocate memory\n");
        exit(1);
    }
    l->head = NULL;
    l->type = type;
    return l;
}

void PrintType(void* value, types type) {
    switch (type) {
        case String:
            printf("%s", (char*)value);
            return;
        case Int:
            printf("%d", *(int*)value);
            return;
        case Double:
            printf("%lf", *(double*)value);
            return;
        default:
            printf("Bad type List\n");
    }
}

void ListPrint(const list* l) {
    Node* ptr = l->head;
    if (ptr != NULL) {
        printf("[ ");
    }

    while (ptr != NULL) {
        PrintType(ptr->value, l->type);
        ptr = ptr->next;
        if (ptr != NULL) {
            printf(" -> ");
        } else {
            printf(" ]\n");
        }
    }
}

void ListPushBack(const void* elem, list* l) {
   if (l == NULL || elem == NULL) return;
   Node* ptr = l->head;
   if (ptr == NULL) {
        l->head = NodeCreate(elem, l->type);
        return;
   }
   while (ptr->next != NULL) {
       ptr = ptr->next;
   }
   ptr->next = NodeCreate(elem, l->type);
}

/* return 1 when (a == b) */
int isEqual(const void* a, const void* b, types type) {
    switch (type) {
    case String:
        return (0 == strcmp((char*)a, (char*)b));
    case Int:
        return ((*(int*)a) == (*(int*)b));
    case Double:
        return ((*(double*)a) == (*(double*)b));
    default:
        printf("Bad Type of List\n");
        exit(1);
    } 
}

unsigned int ListCount(const void* elem, const list* l) {
    if (l == NULL || elem == NULL) return 0;
    if (l->head == NULL) return 0;
    unsigned int res = 0;
    Node* ptr = l->head;
    while (ptr != NULL) {
        res += isEqual(ptr->value, elem, l->type);
        ptr = ptr->next;
    }
    return res;
}

void ListErase(const void* elem, list* l) {
    if (l == NULL || elem == NULL) return;
    if (l->head == NULL) return;

    Node* ptr = l->head;
    if (isEqual(ptr->value, elem, l->type)) {
        l->head = ptr->next;
        NodeDestroy(ptr);
        return;
    }

    while (ptr->next != NULL) {
        if (isEqual(ptr->next->value, elem, l->type)) {
            Node* OldNext = ptr->next->next;
            NodeDestroy(ptr->next);
            ptr->next = OldNext;
            return;
        }
        ptr = ptr->next;
    }

}

void ListDestroy(list* l) {
    if (l == NULL) return;
    Node* ptr = l->head;
    Node* tmp;
    while (ptr != NULL) {
        tmp = ptr;
        ptr = ptr->next;
        NodeDestroy(tmp);
    }
    free(l);
}

