#include "list.h"
#include <stdio.h>
#include <string.h>

void* CreateValue(const void* value, types t) {
    void* ptr = NULL;
    size_t size;

    switch (t) {
        case String:
            /* +1 for '\0' */
            size = (strlen((char*)value) + 1) * sizeof(char);
            break;
        case Int:
            size = sizeof(int);
            break;
        case Double:
            size = sizeof(double);
            break;
        default:
            fprintf(stderr, "ERROR: invalid Node type\n");
            exit(1);
    }

    ptr = malloc(size);
    if (ptr == NULL) {
        fprintf(stderr, "ERROR: could not allocate memory for the Node value\n");
        exit(1);
    }

    memcpy(ptr, value, size);
    return (void*) ptr;
}

Node* NodeCreate(const void* value, types type) {
    Node* n = malloc(sizeof(Node));
    if (n == NULL) {
        fprintf(stderr, "ERROR: could not allocate memory for the Node\n");
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

list ListCreate(types type) {
    list l = {
        .head = NULL,
        .type = type,
    };
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
            printf("◊");
            fprintf(stderr, "ERROR: invalid Node type\n");
    }
}

void ListPrint(const list* l) {
    if (l == NULL) {
        return;
    }

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

size_t ListSize(const list* l) {
    if (l == NULL) {
        fprintf(stderr, "ERROR: could not get size of NULL-list\n");
        exit(1);
    }
    
    size_t size = 0;
    Node* ptr = l->head;
    while (ptr != NULL) {
        ++size;
        ptr = ptr->next;
    }
    return size;
    
}

void ListPushBack(list* l, const void* elem) {
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
        fprintf(stderr, "ERROR: invalid Node type in comparing\n");
        exit(1);
    } 
}

bool ListContains(const list* l, const void* elem) {
    if (l == NULL || elem == NULL) return false;

    Node* ptr = l->head;
    while (ptr != NULL) {
        if (isEqual(ptr->value, elem, l->type)) {
            return true;
        }
        ptr = ptr->next;
    }

    return false;
}

size_t ListCount(const list* l, const void* elem) {
    if (l == NULL || elem == NULL || l->head == NULL) return 0;
    unsigned int res = 0;
    
    Node* ptr = l->head;
    while (ptr != NULL) {
        res += isEqual(ptr->value, elem, l->type);
        ptr = ptr->next;
    }

    return res;
}

void ListErase(list* l, const void* elem) {
    if (l == NULL || l->head == NULL || elem == NULL) return;

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
}

