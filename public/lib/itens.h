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
    const char *conninfo = "dbname=datafourth user=postgres password=ueg2024 hostaddr=10.150.1.220 port=5432";
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

int main() {
    PGconn *conn = connectDB();

    Item newItem = {1, 1, 1, 10, 15.50, 155.00};
    createItem(conn, newItem);

    printf("\nItens após inserção:\n");
    readItems(conn);

    newItem.quantidade = 20;
    newItem.valor_total_item = 310.00;
    updateItem(conn, 1, newItem);

    printf("\nItens após atualização:\n");
    readItems(conn);

    deleteItem(conn, 1);

    printf("\nItens após exclusão:\n");
    readItems(conn);

    PQfinish(conn);
    return 0;
}
