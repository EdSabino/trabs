#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

FILE* _find_right_file(int account) {
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

FILE* _find_right_index(int account) {
    int file;
    if (account % 500 == 0) {
        file = account / 500;
    } else {
        file = (account / 500) + 1;
    }
    char *str = (char*)malloc(30 * sizeof(char));
    sprintf(str, "banks/index/%i.ss", file);
    return fopen(str, "at+");
}

FILE *_find_on_index(char *name) {
    FILE *pfile;
    char *str = (char*)malloc(30 * sizeof(char));
    char name_partial[1000];
    int file;
    int i = 1;
    int must_break = 0;
    while (must_break == 0) {
        sprintf(str, "banks/index/%i.ss", i);
        pfile = fopen(str, "at+");
        while (fscanf(pfile,"%s ->%i/", name_partial, &file) != EOF) {
            if (strcmp(name_partial, name) == 0) {
                must_break = 1;
                break;
            }
        }
        i++;
    }
    sprintf(str, "banks/files/%i.ss", i - 1);
    return fopen(str, "at+");
}

void _find_account_by_number(char *name_partial, int *account_partial, double *value_partial) {
    FILE *pfile;
    int account;
    printf("Escreva o numero da conta\n");
    scanf("%i", &account);
    int i = 0;
    pfile = _find_right_file(account);
    while (fscanf(pfile,"%i;%s ;%f/", account_partial, name_partial, value_partial) != EOF) {
        if (*account_partial == account) {
           break;
        }
    }
    
}

void delete_account() {
    int account;
    printf("Escreva o numero da conta\n");
    scanf("%i", &account);
    _delete_account(account);
}

void _add_to_index(int account, char *name) {
    FILE *pfile_index;
    pfile_index = _find_right_index(account);
    int file;
    if (account % 500 == 0) {
        file = account / 500;
    } else {
        file = (account / 500) + 1;
    }
    char *str = (char*)malloc(30 * sizeof(char));
    char name_partial[1000];
    char name_partial_last[1000];
    char final[1000];
    char partial[1000];
    int file_partial;
    strcpy(final, "");
    strcpy(partial, "");
    while (fscanf(pfile_index,"%s ->%i/", name_partial, &file_partial) != EOF) {
        if (strcmp(name_partial_last, name) < 0 && strcmp(name_partial, name) > 0) {
            sprintf(partial, "%s ->%i/", name, file);
            strcat(final, partial);
        }
        sprintf(partial, "%s ->%i/", name_partial, file_partial);
        strcat(final, partial);    
        strcpy(name_partial_last, name_partial);
    }
    if (strcmp(partial, "") == 0 || strcmp(final, partial) == 0) {
        sprintf(partial, "%s ->%i/", name, file);
        strcat(final, partial);
    }
    freopen(NULL,"w+",pfile_index);
    fprintf(pfile_index, "%s", final);
    fclose(pfile_index);
}

void _insert_account() {
    FILE *pfile;
    char name[1000];
    int account;
    double value;
    char name_partial[1000];
    int account_partial_last = 0;
    int account_partial;
    double value_partial;
    get_values(name, &account, &value);

    int i = 0;
    char final[10000];
    char partial[10000];
    strcpy(final, "");
    strcpy(partial, "");
    pfile = _find_right_file(account);
    while (fscanf(pfile,"%i;%s ;%f/", &account_partial, name_partial, &value_partial) != EOF) {
        if (account_partial_last < account && account_partial > account) {
            sprintf(partial, "%i;%s ;%f/", account, name, value);
            strcat(final, partial);
        }
        sprintf(partial, "%i;%s ;%f/", account_partial, name_partial, value_partial);
        strcat(final, partial);
        account_partial_last = account_partial;
    }
    if (strcmp(partial, "") == 0 || strcmp(final, partial) == 0) {
        sprintf(partial, "%i;%s ;%f/", account, name, value);
        strcat(final, partial);
    }
    _add_to_index(account, name);
    freopen(NULL, "wt+", pfile);
    fprintf(pfile, "%s", final);
    fclose(pfile);
    return ;
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
    scanf("%s", name);
    printf("Escreva o saldo inicial da conta\n");
    scanf("%le", value);
}

void _find_account_by_name() {
    FILE *pfile;
    char name[1000];
    char name_partial[1000];
    int account_partial;
    double value_partial;
    printf("Escreva o nome do usuário\n");
    scanf("%s", name);
    pfile = _find_on_index(name);
    while (fscanf(pfile,"%i;%s ;%f/", &account_partial, name_partial, &value_partial) != EOF) {
        if (strcmp(name_partial, name) == 0) {
            break;
        }
    }
    printf("Conta: %i\n Nome: %s\n Saldo: %f\n", account_partial, name_partial, value_partial);
}

void _update_value() {
    int account;
    double value;
    char name_partial[1000];
    int account_partial;
    int account_partial_last;
    double value_partial;
    char partial[10000];
    char final[10000];
    printf("Escreva o numero da conta\n");
    scanf("%i", &account);
    printf("Escreva o novo valor\n");
    scanf("%lf", &value);
    FILE *pfile = _find_right_file(account);
    fseek(pfile, 0, SEEK_SET);
    strcpy(final, "");
    strcpy(partial, "");
    while (fscanf(pfile,"%i;%s ;%f/", &account_partial, name_partial, &value_partial) != EOF) {
        if (account == account_partial) {
            sprintf(partial, "%i;%s ;%f/", account_partial, name_partial, value);
            strcat(final, partial);
        } else {
            sprintf(partial, "%i;%s ;%f/", account_partial, name_partial, value_partial);
            strcat(final, partial);
        }
        account_partial_last = account_partial;
    }
    freopen(NULL, "wt+", pfile);
    fprintf(pfile, "%s", final);
    fclose(pfile);
    return ;
}

void _delete_account(int account) {
    FILE *pfile;
    char name_partial[1000];
    int account_partial;
    double value_partial;
    char partial[10000];
    char final[10000];
    strcpy(final, "");
    strcpy(partial, "");
    pfile = _find_right_file(account);
    fseek(pfile, 0, SEEK_SET);
    while (fscanf(pfile,"%i;%s ;%f/", &account_partial, name_partial, &value_partial) != EOF) {
        if (account_partial != account) {
            sprintf(partial, "%i;%s ;%f/", account_partial, name_partial, value_partial);
            strcat(final, partial);
        }
    }
    freopen(NULL, "wt+", pfile);
    fprintf(pfile, "%s", final);
    fclose(pfile);
}

void _update_account() {
    FILE *pfile;
    int account;
    int new_account;
    char name[10000];
    double value[1000];
    char name_partial[1000];
    int account_partial;
    int account_partial_last = 0;
    double value_partial;
    char partial[10000];
    char final[10000];
    strcpy(final, "");
    strcpy(partial, "");
    _find_account_by_number(&name, &account, &value);
    _delete_account(account);
    printf("Escreva o novo numero da conta\n");
    scanf("%i", &new_account);
    pfile = _find_right_file(account);
    while (fscanf(pfile,"%i;%s ;%f/", &account_partial, name_partial, &value_partial) != EOF) {
        if (account_partial_last < new_account && account_partial > new_account) {
            sprintf(partial, "%i;%s ;%f/", new_account, name, value);
            strcat(final, partial);
        }
        sprintf(partial, "%i;%s ;%f/", account_partial, name_partial, value_partial);
        strcat(final, partial);
        account_partial_last = account_partial;
    }
    if (strcmp(partial, "") == 0 || strcmp(final, partial) == 0) {
        sprintf(partial, "%i;%s ;%f/", new_account, name, value);
        strcat(final, partial);
    }
    _add_to_index(new_account, name);
    freopen(NULL, "wt+", pfile);
    fprintf(pfile, "%s", final);
    fclose(pfile);
    return ;
}

void _list_all() {
    char *str = (char*)malloc(30 * sizeof(char));
    FILE *pfile;
    char name_partial[1000];
    int account_partial;
    double value_partial;
    int i = 0;
    int must_break = 0;
    while (must_break == 0) {
        sprintf(str, "banks/files/%i.ss", i);
        if (access(str, F_OK)) {
            pfile = fopen(str, "rt+");
            while (fscanf(pfile,"%i;%s ;%f/", &account_partial, name_partial, &value_partial) != EOF) {
                printf("Conta: %i\n Nome: %s\n Saldo: %f\n", account_partial, name_partial, value_partial);
            }
            i++;
        } else {
            must_break = 1;
        }
    }
}

void _sum_all() {
    char *str = (char*)malloc(30 * sizeof(char));
    FILE *pfile;
    char name_partial[1000];
    int account_partial;
    double value_partial;
    int i = 1;
    int must_break = 0;
    double sum = 0;
    while (must_break == 0) {
        sprintf(str, "banks/files/%i.ss", i);
        if (access(str, F_OK)) {
            pfile = fopen(str, "rt+");
            while (fscanf(pfile,"%i;%s ;%f/", &account_partial, name_partial, &value_partial) != EOF) {
                sum += value_partial;
            }
            i++;
        } else {
            must_break = 1;
        }
    }
    printf("Total: %f\n", sum);
}

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

void print_options() {
    printf("Digite 1 para inserir nova conta\n");
    printf("Digite 2 para pesquisar uma conta pelo nome\n");
    printf("Digite 3 para pesquisar uma conta pelo numero da conta\n");
    printf("Digite 4 para atualizar o saldo de uma conta\n");
    printf("Digite 5 para atualizar o numero da conta\n");
    printf("Digite 6 para listar todas as contas\n");
    printf("Digite 7 para exibir a soma de todos os saldos\n");
    printf("Digite 8 para excluir uma conta\n");
    printf("Digite 0 para sair\n");
}

void create_menu(int value) {
    switch (value) {
        case 1:
            insert_account();
            break;
        case 2:
            find_account_by_name();
            break;
        case 3:
            find_account_by_number();
            break;
        case 4:
            update_value();
            break;
        case 5:
            update_account();
            break;
        case 6:
            list_all();
            break;
        case 7:
            sum_all();
            break;
        case 8:
            delete_account();
            break;
        case 9:
            break;
        default:
            break;
    }
}

void main() {
    while (1 == 1) {
        int response;
        print_options();
        scanf("%i", &response);
        create_menu(response);
        if (response == 0) {
            break;
        }
    }
}