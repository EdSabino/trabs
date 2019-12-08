#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "account.h"

void insert_account() {
    _insert_account();
}

void find_account_by_name() {
    _find_account_by_name();
}

void find_account_by_number() {
    char name_partial[1000];
    int account_partial;
    double value_partial;
    _find_account_by_number(name_partial, &account_partial, &value_partial);
    printf("Conta: %i\n Nome: %s\n Saldo: %f\n", account_partial, name_partial, value_partial);
}

void update_value() {
    _update_value();
}

void update_account() {
    _update_account();
}

void list_all() {
    _list_all();
}

void sum_all() {
    _sum_all();
}

void delete_account() {
    int account;
    printf("Escreva o numero da conta\n");
    scanf("%i", account);
    _delete_account(account);
}

void _insert_account() {
    FILE *pfile;
    char name[1000];
    int account;
    double value;
    char name_partial[1000];
    int account_partial_last;
    int account_partial;
    double value_partial;
    get_values(name, &account, &value);

    int i = 0;
    char[10000] final;
    char[10000] partial;
    strcpy(final, "");
    pfile = _find_right_file(account);
    while (fscanf(pfile,"%i;%s;%f/", &account_partial, name_partial, &value_partial)==1) {
        if (account_partial_last < account && account_partial > account) {
            sprintf(partial, "%i;%s;%f/", account_partial, name_partial, value_partial);
            strcat(final, partial);    
        }
        sprintf(partial, "%i;%s;%f/", account_partial, name_partial, value_partial);
        strcat(final, partial);
        account_partial_last = account_partial;
    }
    fprintf(pfile, "%s", final);
    fclose(pfile);
}

FILE *_find_right_file(int account) {
    int file;
    if (account % 500 == 0) {
        file = account / 500;
    } else {
        file = (account / 500) + 1;
    }
    char *str = (char*)malloc(30 * sizeof(char));
    sprintf(str, "banks/files/%i.ss", file);
    return fopen(str, "at+");
}

void _strip_string(char *value) {
    char *pos;
    if ((pos=strchr(value, '\n')) != NULL)
        *pos = '\0';
}

void get_values(char *name, int *account, double *value) {
    printf("Escreva o numero da conta\n");
    scanf("%i", account);
    printf("Escreva o nome do usuário\n");
    getchar();
    fgets(name, 1000, stdin);
    printf("Escreva o saldo inicial da conta\n");
    scanf("%le", value);
    _strip_string(name);
}

void _find_account_by_name() {
    FILE *pfile;
    char name[1000];
    char name_partial[1000];
    int account_partial;
    double value_partial;
    printf("Escreva o nome do usuário\n");
    getchar();
    fgets(name, 1000, stdin);
    _strip_string(name);
    int i = 0;
    int must_break == 0;
        while (must_break == 0) {
            sprintf(str, "banks/files/%i.ss", file);
            pfile = fopen(str, "at+");
            while (fscanf(pfile,"%i;%s;%f/", &account_partial, name_partial, &value_partial)==1) {
                if (name_partial == name) {
                    must_break = 1;
                    break;
                }
            }
            i++;
        }
        printf("Conta: %i\n Nome: %s\n Saldo: %f\n", account_partial, name_partial, value_partial);
}

void _find_account_by_number(char *name_partial, int *account_partial, double *value_partial) {
    FILE *pfile;
    int account;
    printf("Escreva o numero da conta\n");
    scanf("%i", account);
    int i = 0;
    pfile = _find_right_file(account);
    while (fscanf(pfile,"%i;%s;%f/", &account_partial, name_partial, &value_partial)==1) {
        if (account_partial == account) {
           break;
        }
    }
    
}

void _update_value() {
    FILE *pfile;
    int account;
    int value;
    char name_partial[1000];
    int account_partial;
    double value_partial;
    _find_account_by_number(name_partial, &account_partial, &value_partial);
    printf("Escreva o novo valor\n");
    scanf("%i", value);
    fseek(pfile, -8, SEEK_CUR);
    fputc(value, pfile);
}

void _delete_account(int account) {
    FILE *pfile;
    char name_partial[1000];
    int account_partial;
    double value_partial;
    char[10000] partial;
    char[10000] final;
    strcpy(final, "");
    pfile = _find_right_file(account);
    while (fscanf(pfile,"%i;%s;%f/", &account_partial, name_partial, &value_partial)==1) {
        if (account_partial != account) {
            sprintf(partial, "%i;%s;%f/", account_partial, name_partial, value_partial);
            strcat(final, partial);
        }
    }
    fprintf(pfile, "%s", final);
    fclose(pfile);
}

void _update_account() {
    FILE *pfile;
    int account;
    int new_account;
    char name_partial[1000];
    int account_partial;
    double value_partial;
    char[10000] partial;
    char[10000] final;
    strcpy(final, "");
    printf("Escreva o numero atual da conta\n");
    scanf("%i", account);
    printf("Escreva o novo numero da conta\n");
    scanf("%i", new_account);
    pfile = _find_right_file(account);
    while (fscanf(pfile,"%i;%s;%f/", &account_partial, name_partial, &value_partial)==1) {
        if (account_partial != account) {
            sprintf(partial, "%i;%s;%f/", account_partial, name_partial, value_partial);
            strcat(final, partial);
        } else {
            sprintf(partial, "%i;%s;%f/", new_account, name_partial, value_partial);
            strcat(final, partial);
        }
    }
    fprintf(pfile, "%s", final);
    fclose(pfile);
}

void _list_all() {
    char name_partial[1000];
    int account_partial;
    double value_partial;
    int i = 0;
    int must_break == 0;
    while (must_break == 0) {
        sprintf(str, "banks/files/%i.ss", file);
        pfile = fopen(str, "at+");
        if (pfile == NULL) {
            must_break = 1;
        } else {
            while (fscanf(pfile,"%i;%s;%f/", &account_partial, name_partial, &value_partial)==1) {
                printf("Conta: %i\n Nome: %s\n Saldo: %f\n", account_partial, name_partial, value_partial);
            }
        }
        i++;
    }
}

void _sum_all() {
    char name_partial[1000];
    int account_partial;
    double value_partial;
    int i = 0;
    int must_break == 0;
    double sum = 0;
    while (must_break == 0) {
        sprintf(str, "banks/files/%i.ss", file);
        pfile = fopen(str, "at+");
        if (pfile == NULL) {
            must_break = 1;
        } else {
            while (fscanf(pfile,"%i;%s;%f/", &account_partial, name_partial, &value_partial)==1) {
                sum += value_partial;
            }
        }
        i++;
    }
    printf("Total: %f\n", sum);
}