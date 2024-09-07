#include <stdio.h>
#include <stdlib.h>

// Inclusão dos cabeçalhos de cada entidade
#include "../lib/cliente.h"                 // Inclusão do cabeçalho da entidade Cliente
#include "../lib/pedido.h"                  // Inclusão do cabeçalho da entidade Pedido
#include "../lib/itens.h"                   // Inclusão do cabeçalho da entidade Itens
#include "../lib/atendente.h"               // Inclusão do cabeçalho da entidade Atendente
#include "../lib/fornecedor.h"              // Inclusão do cabeçalho da entidade Fornecedor
#include "../lib/produto.h"                 // Inclusão do cabeçalho da entidade Produto
#include "../lib/produto_fornecedor.h"      // Inclusão do cabeçalho da entidade Produto_Fornecedor
#include "../lib/pedido_atendente.h"        // Inclusão do cabeçalho da entidade Pedido_Atendente

void painelCliente();
void painelPedido();
void painelItens();
void painelAtendente();
void painelFornecedor();
void painelProduto();
void painelProdutoFornecedor();
void painelPedidoAtendente();

void menuPrincipal() {
    int opcao;

    while (1) {
        printf("\n\n========== Menu Principal ==========\n");
        printf("1. Painel Cliente\n");
        printf("2. Painel Pedido\n");
        printf("3. Painel Itens\n");
        printf("4. Painel Atendente\n");
        printf("5. Painel Fornecedor\n");
        printf("6. Painel Produto\n");
        printf("7. Painel Produto_Fornecedor\n");
        printf("8. Painel Pedido_Atendente\n");
        printf("9. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                painelCliente();
                break;
            case 2:
                painelPedido();
                break;
            case 3:
                painelItens();
                break;
            case 4:
                painelAtendente();
                break;
            case 5:
                painelFornecedor();
                break;
            case 6:
                painelProduto();
                break;
            case 7:
                painelProdutoFornecedor();
                break;
            case 8:
                painelPedidoAtendente();
                break;
            case 9:
                printf("Saindo...\n");
                exit(0);
            default:
                printf("Opção inválida! Tente novamente.\n");
        }
    }
}

int main() {
    menuPrincipal();
    return 0;
}
