#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../lib/itens.h"                   

// #include "../lib/cliente.h"              
// #include "../lib/pedido.h"              
// #include "../lib/atendente.h"            
// #include "../lib/fornecedor.h"          
// #include "../lib/produto.h"              
// #include "../lib/produto_fornecedor.h"   
// #include "../lib/pedido_atendente.h"     

int main() {
    int escolha;
    char terminal[50];

    printf("Digite o terminal que você deseja acessar para o banco de dados (por exemplo: psql): ");
    fgets(terminal, sizeof(terminal), stdin);
    
    size_t length = strlen(terminal);
    if (terminal[length - 1] == '\n') {
        terminal[length - 1] = '\0';
    }

    printf("Você escolheu acessar o banco de dados usando: %s\n", terminal);

    printf("\nEscolha o painel que você deseja acessar:\n");
    printf("1. Painel de Itens\n");
    printf("2. Painel de Cliente\n");
    printf("3. Painel de Pedido\n");
    printf("4. Painel de Atendente\n");
    printf("5. Painel de Fornecedor\n");
    printf("6. Painel de Produto\n");
    printf("7. Painel de Produto_Fornecedor\n");
    printf("8. Painel de Pedido_Atendente\n");
    printf("Opção: ");
    scanf("%d", &escolha);

    switch (escolha) {
        case 1:
            itens_painel();  
            break;
        case 2:
            cliente_painel();  
            break;
        case 3:
            pedido_painel();  
            break;
        case 4:
            atendente_painel();  
            break;
        case 5:
            fornecedor_painel();  
            break;
        case 6:
            produto_painel();  
            break;
        case 7:
            produto_fornecedor_painel();  
            break;
        case 8:
            pedido_atendente_painel();  
            break;
        default:
            printf("Opção inválida!\n");
            break;
    }

    return 0;
}
