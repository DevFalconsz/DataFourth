// Uso para a parte de itens

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libpq-fe.h>

// Definição da estrutura para armazenar um item
typedef struct {
    int num_item;
    int id_pedido;
    int id_produto;
    int quantidade;
    float valor_unitario;
    float valor_total_item;
} Item;

PGconn *connectDB() {
    const char *conninfo = "dbname=datafourth user=itens_user password=ueg2024 hostaddr=10.150.1.220 port=5432";
    PGconn *conn = PQconnectdb(conninfo);

    if (PQstatus(conn) != CONNECTION_OK) {
        fprintf(stderr, "Falha na conexão: %s", PQerrorMessage(conn));
        PQfinish(conn);
        exit(1);
    }

    return conn;
}

void createItem(PGconn *conn, Item item) {
    char query[512];
    snprintf(query, sizeof(query), 
             "INSERT INTO itens (num_item, id_pedido, id_produto, quantidade, valor_unitario, valor_total_item) "
             "VALUES (%d, %d, %d, %d, %.2f, %.2f);",
             item.num_item, item.id_pedido, item.id_produto, item.quantidade, item.valor_unitario, item.valor_total_item);

    PGresult *res = PQexec(conn, query);

    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        fprintf(stderr, "Erro ao inserir item: %s", PQerrorMessage(conn));
    } else {
        printf("Item inserido com sucesso!\n");
    }

    PQclear(res);
}

void readItems(PGconn *conn) {
    PGresult *res = PQexec(conn, "SELECT * FROM itens");

    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        fprintf(stderr, "Erro ao consultar itens: %s", PQerrorMessage(conn));
        PQclear(res);
        return;
    }

    int rows = PQntuples(res);
    for (int i = 0; i < rows; i++) {
        printf("Num Item: %s, ID Pedido: %s, ID Produto: %s, Quantidade: %s, Valor Unitário: %s, Valor Total Item: %s\n",
               PQgetvalue(res, i, 0), PQgetvalue(res, i, 1), PQgetvalue(res, i, 2), PQgetvalue(res, i, 3), PQgetvalue(res, i, 4), PQgetvalue(res, i, 5));
    }

    PQclear(res);
}

void updateItem(PGconn *conn, int num_item, Item item) {
    char query[512];
    snprintf(query, sizeof(query), 
             "UPDATE itens SET id_pedido=%d, id_produto=%d, quantidade=%d, valor_unitario=%.2f, valor_total_item=%.2f "
             "WHERE num_item=%d;",
             item.id_pedido, item.id_produto, item.quantidade, item.valor_unitario, item.valor_total_item, num_item);

    PGresult *res = PQexec(conn, query);

    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        fprintf(stderr, "Erro ao atualizar item: %s", PQerrorMessage(conn));
    } else {
        printf("Item atualizado com sucesso!\n");
    }

    PQclear(res);
}

void deleteItem(PGconn *conn, int num_item) {
    char query[256];
    snprintf(query, sizeof(query), "DELETE FROM itens WHERE num_item=%d;", num_item);

    PGresult *res = PQexec(conn, query);

    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        fprintf(stderr, "Erro ao deletar item: %s", PQerrorMessage(conn));
    } else {
        printf("Item deletado com sucesso!\n");
    }

    PQclear(res);
}

void painel() {
    printf("  _____   _                        \n");
    printf(" |_   _| | |                       \n");
    printf("   | |   | |_    ___   _ __    ___ \n");
    printf("   | |   | __|  / _ \\ | '_ \\  / __|\n");
    printf("  _| |_  | |_  |  __/ | | | | \\__ \\\n");
    printf(" |_____|  \\__|  \\___| |_| |_| |___/\n");
    printf("                                   \n");
    printf("                                   \n");
    
    PGconn *conn = connectDB();
    
    int escolha;
    Item item;
    int num_item;

    while (1) {
        printf("\nEscolha uma operação:\n");
        printf("1. Inserir Item\n");
        printf("2. Listar Itens\n");
        printf("3. Atualizar Item\n");
        printf("4. Deletar Item\n");
        printf("5. Sair\n");
        printf("Opção: ");
        scanf("%d", &escolha);

        switch (escolha) {
            case 1:
                printf("Inserir novo item:\n");
                printf("Num Item: ");
                scanf("%d", &item.num_item);
                printf("ID Pedido: ");
                scanf("%d", &item.id_pedido);
                printf("ID Produto: ");
                scanf("%d", &item.id_produto);
                printf("Quantidade: ");
                scanf("%d", &item.quantidade);
                printf("Valor Unitário: ");
                scanf("%f", &item.valor_unitario);
                item.valor_total_item = item.quantidade * item.valor_unitario;
                createItem(conn, item);
                break;
            case 2:
                printf("Itens cadastrados:\n");
                readItems(conn);
                break;
            case 3:
                printf("Atualizar item:\n");
                printf("Num Item: ");
                scanf("%d", &num_item);
                printf("Novo ID Pedido: ");
                scanf("%d", &item.id_pedido);
                printf("Novo ID Produto: ");
                scanf("%d", &item.id_produto);
                printf("Nova Quantidade: ");
                scanf("%d", &item.quantidade);
                printf("Novo Valor Unitário: ");
                scanf("%f", &item.valor_unitario);
                item.valor_total_item = item.quantidade * item.valor_unitario;
                updateItem(conn, num_item, item);
                break;
            case 4:
                printf("Deletar item:\n");
                printf("Num Item: ");
                scanf("%d", &num_item);
                deleteItem(conn, num_item);
                break;
            case 5:
                PQfinish(conn);
                printf("Saindo...\n");
                return;
            default:
                printf("Opção inválida!\n");
        }
    }
}
