#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "account.h"

static char *index = "bank/";

void insert_account() {
    FILE *pfile;
    char name[1000];
    int account;
    double value;
    printf("Escreva o numero da conta\n");
    scanf("%i", &account);
    printf("Escreva o nome do usuário\n");
    getchar();
    fgets(name, 1000, stdin);
    printf("Escreva o saldo inicial da conta\n");
    scanf("%le", &value);
    strip_string(name);

    int position = find_right_file(account);
    char *str = (char*)malloc(30 * sizeof(char));
    sprintf(str, "banks/index/index%i.ss", position);
    pfile = fopen(str, "at+");
    fprintf(pfile, "%i;", account);
    fprintf(pfile, "%s;", name);
    fprintf(pfile, "%f/", value);
    fclose(pfile);
}

void free_account(Account *account) {
    free(account);
}

int find_right_file(int account) {
    int i = 1;
    FILE *pfile;
    while (1 == 1) {
        char *str = (char*)malloc(30 * sizeof(char));
        sprintf(str, "banks/index/index%i.ss", i);
        int quantity = -1;
        double first, last;
        pfile = fopen(str, "at+");
        fscanf(pfile, "%i;%f;%f", &quantity, &first, &last);
        if (quantity == -1) {
            fprintf(pfile, "%i;", quantity);
            fprintf(pfile, "%f;", account);
            fprintf(pfile, "%f;", account);
            fprintf(pfile, "\n");
            fprintf(pfile, "%f->%i", account, i);
        } else {
            if (account > first && account < last) {
                break;
            } else {
                i++;
            }
        }
    }
    fclose(pfile);
}

void strip_string(char *value) {
    char *pos;
    if ((pos=strchr(value, '\n')) != NULL)
        *pos = '\0';
}

