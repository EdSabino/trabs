#include <stdio.h>
#include <stdlib.h>
#include "account.h"

void print_options() {
    printf("Digite 1 para inserir nova conta\n");
    printf("Digite 2 para pesquisar uma conta pelo nome\n");
    printf("Digite 3 para pesquisar uma conta pelo numero da conta\n");
    printf("Digite 4 para atualizar o saldo de uma conta\n");
    printf("Digite 5 para atualizar o numero da conta\n");
    printf("Digite 6 para listar todas as contas\n");
    printf("Digite 7 para exibir a soma de todos os saldos\n");
    printf("Digite 8 para excluir uma conta\n");
    printf("Digite 9 para reorganizar o arquivo\n");
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