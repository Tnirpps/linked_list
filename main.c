#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <error.h>
#include <stdbool.h>
#include "list.h"


void usage() {
    printf("1) push back\t 2) erase\t 3) count\t 0) exit\n");
}

#define INTEGER 1
#define DOUBLE  2
#define STRING  3

/* define type of data in List*/
#ifndef TYPEOFLIST
 #define TYPEOFLIST  (DOUBLE)
#endif

#if TYPEOFLIST == INTEGER

void loop() {
    list* l = ListCreate(Int);
    int q;
    int x;
    usage();
    while (1) {
        printf("enter query number: ");
        if (scanf("%d", &q) != 1) {
            printf("Cannot read query\n");
            return;
        }
        if (q == 0) break;
        if (q == 1) {
            printf("enter value: ");
            if (scanf("%d", &x) != 1) {
                printf("Cannot read value\n");
                return;
            }
            ListPushBack(&x, l);
        } else if (q == 2) {
            printf("enter value: ");
            if (scanf("%d", &x) != 1) {
                printf("Cannot read value\n");
                return;
            }
            ListErase(&x, l);
        } else if (q == 3) {
            printf("enter value: ");
            if (scanf("%d", &x) != 1) {
                printf("Cannot read value\n");
                return;
            }
            printf("Count of '%d': %u\n", x, ListCount(&x, l));
        } else {
            printf("bad query numder\n");
            usage();
            continue;
        }

        ListPrint(l);
    }

    ListDestroy(l);
}

#elif TYPEOFLIST == DOUBLE

void loop() {
    list* l = ListCreate(Double);
    int q;
    double x;
    usage();
    while (1) {
        printf("enter query number: ");
        if (scanf("%d", &q) != 1) {
            printf("Cannot read query\n");
            return;
        }
        if (q == 0) break;
        if (q == 1) {
            printf("enter value: ");
            if (scanf("%lf", &x) != 1) {
                printf("Cannot read value\n");
                return;
            }
            ListPushBack(&x, l);
        } else if (q == 2) {
            printf("enter value: ");
            if (scanf("%lf", &x) != 1) {
                printf("Cannot read value\n");
                return;
            }
            ListErase(&x, l);
        } else if (q == 3) {
            printf("enter value: ");
            if (scanf("%lf", &x) != 1) {
                printf("Cannot read value\n");
                return;
            }
            printf("Count of '%lf': %u\n", x, ListCount(&x, l));
        } else {
            printf("bad query numder\n");
            usage();
            continue;
        }

        ListPrint(l);
    }

    ListDestroy(l);
}

#elif TYPEOFLIST == STRING

char* readString(FILE* fp){
    char* str;
    int ch;
    size_t len = 0;
    size_t size = 10; //size is start size
    str = malloc(sizeof(char)*size);
    if (str == NULL) return NULL;

    while ((ch = fgetc(fp)) != EOF && ch != '\n') {
        str[len++] = ch;
        if (len + 1 == size - 1) {
            size *= 2;
            char* tmp = realloc(str, sizeof(char)*size);
            if (tmp == NULL) {
                free(str);
                printf("Cannot read string\n");
                exit(1);
            }
            str = tmp;
        }
    }
    str[len++]='\0';

    return str;
}

void loop() {
    list* l = ListCreate(String);
    int q;
    char* x;
    usage();
    while (1) {
        printf("enter query number: ");
        if (scanf("%d", &q) != 1) {
            printf("Cannot read query\n");
            return;
        }
        // remove \n from stdin after scanf
        fgetc(stdin);

        if (q == 0) break;
        if (q == 1) {
            printf("enter value: ");
            x = readString(stdin);
            ListPushBack(x, l);
            free(x);
            x = NULL;
        } else if (q == 2) {
            printf("enter value: ");
            x = readString(stdin);
            ListErase(x, l);
            free(x);
            x = NULL;
        } else if (q == 3) {
            printf("enter value: ");
            x = readString(stdin);
            printf("Count of '%s': %u\n", x, ListCount(x, l));
            free(x);
            x = NULL;
        } else {
            printf("bad query numder\n");
            usage();
            continue;
        }

        ListPrint(l);
    }

    ListDestroy(l);
}

#else
 #error "Unexpected value of TYPEOFLIST."
#endif


int main() {
    loop();
    return 0;
}

