#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../lib/itens.h"
#include "../lib/cliente.c"
#include "../lib/atendente.c"

// #include "../lib/pedido.h"
// #include "../lib/fornecedor.h"
// #include "../lib/produto.h"
// #include "../lib/produto_fornecedor.h"
// #include "../lib/pedido_atendente.h"

void cliente_painel() {
    printf("Painel do Cliente.\n");
}

void pedido_painel() {
    printf("Painel do Pedido.\n");
}

void atendente_painel() {
    printf("Painel do Atendente.\n");
}

void fornecedor_painel() {
    printf("Painel do Fornecedor.\n");
}

void produto_painel() {
    printf("Painel do Produto.\n");
}

void produto_fornecedor_painel() {
    printf("Painel do Produto_Fornecedor.\n");
}

void pedido_atendente_painel() {
    printf("Painel do Pedido_Atendente.\n");
}

int main() {
    int escolha;
    char terminal[50] = "psql";

    size_t length = strlen(terminal);
    if (terminal[length - 1] == '\n') {
        terminal[length - 1] = '\0';
    }

    printf("Você escolheu acessar o banco de dados usando: %s\n", terminal);

    conectarBanco();

    // Loop para manter o menu principal ativo até o usuário sair
    while (1) {

        printf(" ___  ___                 \n");
        printf("|  \\/  |                 \n");
        printf("| .  . | ___ _ __  _   _  \n");
        printf("| |\\/| |/ _ \\ '_ \\| | | | \n");
        printf("| |  | |  __/ | | | |_| | \n");
        printf("\\_|  |_/\\___|_| |_|\\__,_| \n");
        printf("                          \n");
        printf("                          \n");

        printf("\nEscolha o painel que você deseja acessar:\n");
        printf("1. Painel de Itens\n");
        printf("2. Painel de Cliente\n");
        printf("3. Painel de Pedido\n");
        printf("4. Painel de Atendente\n");
        printf("5. Painel de Fornecedor\n");
        printf("6. Painel de Produto\n");
        printf("7. Painel de Produto_Fornecedor\n");
        printf("8. Painel de Pedido_Atendente\n");
        printf("9. Sair\n");  // Opção para sair do programa
        printf("Opção: ");
        scanf("%d", &escolha);

        switch (escolha) {
            case 1:
                itens_painel();  // Chama o painel de Itens
                break;
            case 2:
                cliente_painel();
                conectarBanco();
                exibirMenu();
                desconectarBanco();  // Painel de Cliente
                break;
            case 3:
                pedido_painel();  // Painel de Pedido
                break;
            case 4:
                menuAtendente();
                break;
            case 5:
                fornecedor_painel();  // Painel de Fornecedor
                break;
            case 6:
                produto_painel();  // Painel de Produto
                break;
            case 7:
                produto_fornecedor_painel();  // Painel de Produto_Fornecedor
                break;
            case 8:
                pedido_atendente_painel();  // Painel de Pedido_Atendente
                break;
            case 9:
                printf("Saindo do programa...\n");
                return 0;  // Sai do programa
            default:
                printf("Opção inválida!\n");
        }
    }

    return 0;
}
