#ifndef _ISDEF
#define _ISDEF
#include <stdio.h>
#include <stdlib.h>

struct account {
    int number;
    char *name;
    double value;
};

typedef struct account Account;

void insert_account();

void free_account();

#endif