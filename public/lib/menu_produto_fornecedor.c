#include <stdio.h>
#include <stdlib.h>
#include <libpq-fe.h>
#include <string.h>
#include "common.h"

// Função para buscar o id_produto com base na descrição
int get_id_produto(PGconn *conn, const char *descricao) {
    const char *paramValues[1] = {descricao};
    PGresult *res = PQexecParams(conn,
        "SELECT id_produto FROM produto WHERE descricao = $1",
        1,   // Número de parâmetros
        NULL, // Tipos de parâmetros
        paramValues,
        NULL,
        NULL,
        0);

    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        fprintf(stderr, "Falha ao buscar id_produto: %s", PQerrorMessage(conn));
        PQclear(res);
        exit_nicely(conn);
    }

    if (PQntuples(res) == 0) {
        printf("Produto não encontrado.\n");
        PQclear(res);
        return -1;
    }

    int id_produto = atoi(PQgetvalue(res, 0, 0));
    PQclear(res);
    return id_produto;
}

// Função para buscar o id_fornecedor com base no nome
int get_id_fornecedor(PGconn *conn, const char *nome) {
    const char *paramValues[1] = {nome};
    PGresult *res = PQexecParams(conn,
        "SELECT id_fornecedor FROM fornecedor WHERE nome = $1",
        1,
        NULL,
        paramValues,
        NULL,
        NULL,
        0);

    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        fprintf(stderr, "Falha ao buscar id_fornecedor: %s", PQerrorMessage(conn));
        PQclear(res);
        exit_nicely(conn);
    }

    if (PQntuples(res) == 0) {
        printf("Fornecedor não encontrado.\n");
        PQclear(res);
        return -1;
    }

    int id_fornecedor = atoi(PQgetvalue(res, 0, 0));
    PQclear(res);
    return id_fornecedor;
}

// Função para criar uma entrada na tabela produto_fornecedor
void create_produto_fornecedor(PGconn *conn, int id_produto, int id_fornecedor, int quantidade, float valor_produto) {
    const char *paramValues[4];
    char id_produto_str[12], id_fornecedor_str[12], quantidade_str[12], valor_produto_str[12];

    snprintf(id_produto_str, sizeof(id_produto_str), "%d", id_produto);
    snprintf(id_fornecedor_str, sizeof(id_fornecedor_str), "%d", id_fornecedor);
    snprintf(quantidade_str, sizeof(quantidade_str), "%d", quantidade);
    snprintf(valor_produto_str, sizeof(valor_produto_str), "%.2f", valor_produto);

    paramValues[0] = id_produto_str;
    paramValues[1] = id_fornecedor_str;
    paramValues[2] = quantidade_str;
    paramValues[3] = valor_produto_str;

    PGresult *res = PQexecParams(conn,
        "INSERT INTO produto_fornecedor (id_produto, id_fornecedor, quantidade, valor_produto) VALUES ($1, $2, $3, $4)",
        4,
        NULL,
        paramValues,
        NULL,
        NULL,
        0);

    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        fprintf(stderr, "Falha ao inserir produto_fornecedor: %s", PQerrorMessage(conn));
        PQclear(res);
        exit_nicely(conn);
    }

    printf("Produto e fornecedor inseridos na tabela produto_fornecedor.\n");
    PQclear(res);
}

// Função que integra todas as operações
void inserir_produto_fornecedor(PGconn *conn) {
    char descricao[255], nome_fornecedor[255];
    int quantidade;
    float valor_produto;

    printf("______              _       _                       \n");
    printf("| ___ \\            | |     | |                      \n");
    printf("| |_/ / __ ___   __| |_   _| |_ ___                 \n");
    printf("|  __/ '__/ _ \\ / _` | | | | __/ _ \\                \n");
    printf("| |  | | | (_) | (_| | |_| | || (_) |               \n");
    printf("\\_|  |_|  \\___/ \\__,_|\\__,_|\\__\\___/               \n");
    printf("                                                    \n");
    printf("                                                    \n");
    printf("______                                 _            \n");
    printf("|  ___|                               | |           \n");
    printf("| |_ ___  _ __ _ __   ___  ___ ___  __| | ___  _ __ \n");
    printf("|  _/ _ \\| '__| '_ \\ / _ \\/ __/ _ \\/ _` |/ _ \\| '__|\n");
    printf("| || (_) | |  | | | |  __/ (_|  __/ (_| | (_) | |   \n");
    printf("\\_| \\___/|_|  |_| |_|\\___|\\___\\___|\\__,_|\\___/|_|   \n");
    printf("                                                    \n");
    printf("                                                    \n");

    // Captura o nome do produto
    printf("Digite a descrição do produto: ");
    fgets(descricao, 255, stdin);
    descricao[strcspn(descricao, "\n")] = 0;  // Remover o \n

    // Captura o nome do fornecedor
    printf("Digite o nome do fornecedor: ");
    fgets(nome_fornecedor, 255, stdin);
    nome_fornecedor[strcspn(nome_fornecedor, "\n")] = 0;  // Remover o \n

    // Captura a quantidade e o valor do produto
    printf("Digite a quantidade do produto: ");
    scanf("%d", &quantidade);
    printf("Digite o valor do produto: ");
    scanf("%f", &valor_produto);
    getchar();  // Limpar o buffer

    // Buscar o id_produto com base na descrição
    int id_produto = get_id_produto(conn, descricao);
    if (id_produto == -1) {
        printf("Erro ao buscar o produto.\n");
        return;
    }

    // Buscar o id_fornecedor com base no nome
    int id_fornecedor = get_id_fornecedor(conn, nome_fornecedor);
    if (id_fornecedor == -1) {
        printf("Erro ao buscar o fornecedor.\n");
        return;
    }

    // Inserir na tabela produto_fornecedor
    create_produto_fornecedor(conn, id_produto, id_fornecedor, quantidade, valor_produto);
}

void painel_produto_fornecedor() {
    const char *conninfo = "dbname=datafourth user=devfalconsz password=TheFalconsz";
    PGconn *conn = PQconnectdb(conninfo);

    if (PQstatus(conn) != CONNECTION_OK) {
        fprintf(stderr, "Connection to database failed: %s", PQerrorMessage(conn));
        exit_nicely(conn);
    }

    // Chama a função para inserir na tabela produto_fornecedor
    inserir_produto_fornecedor(conn);

    PQfinish(conn);
}
