#include <stdio.h>
#include <stdlib.h>
#include <libpq-fe.h>
#include <string.h>
#include "common.h"  // Inclui as funções auxiliares como exit_nicely
#include "produto_header.h"  // Inclui as declarações das funções CRUD de produto

// Função para criar um produto na tabela 'produto'
void create_produto(PGconn *conn, const char *id_produto, const char *descricao, const char *unidade) {
    const char *paramValues[3] = {id_produto, descricao, unidade};
    PGresult *res = PQexecParams(conn,
        "INSERT INTO produto (id_produto, descricao, unidade) VALUES ($1, $2, $3)",
        3,   // Número de parâmetros
        NULL, // Tipos de parâmetros
        paramValues,
        NULL, // Comprimentos dos parâmetros
        NULL, // Formatos dos parâmetros
        0);   // Formato do resultado

    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        fprintf(stderr, "INSERT produto failed: %s", PQerrorMessage(conn));
        PQclear(res);
        exit_nicely(conn);
    }
    PQclear(res);
}

// Função para ler todos os produtos da tabela 'produto'
void read_produto(PGconn *conn) {
    PGresult *res = PQexec(conn, "SELECT * FROM produto");

    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        fprintf(stderr, "SELECT failed: %s", PQerrorMessage(conn));
        PQclear(res);
        exit_nicely(conn);
    }

    int rows = PQntuples(res);
    for (int i = 0; i < rows; i++) {
        printf("ID: %s, Descrição: %s, Unidade: %s\n", PQgetvalue(res, i, 0), PQgetvalue(res, i, 1), PQgetvalue(res, i, 2));
    }


    PQclear(res);
}

// Função para atualizar um produto na tabela 'produto'
void update_produto(PGconn *conn, const char *id_produto, const char *nova_descricao, const char *nova_unidade) {
    const char *paramValues[3] = {nova_descricao, nova_unidade, id_produto};
    PGresult *res = PQexecParams(conn,
        "UPDATE produto SET descricao = $1, unidade = $2 WHERE id_produto = $3",
        3,
        NULL,
        paramValues,
        NULL,
        NULL,
        0);

    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        fprintf(stderr, "UPDATE produto failed: %s", PQerrorMessage(conn));
        PQclear(res);
        exit_nicely(conn);
    }

    PQclear(res);
}

// Função para deletar um produto da tabela 'produto'
void delete_produto(PGconn *conn, const char *id_produto) {
    const char *paramValues[1] = {id_produto};
    PGresult *res = PQexecParams(conn,
        "DELETE FROM produto WHERE id_produto = $1",
        1,
        NULL,
        paramValues,
        NULL,
        NULL,
        0);

    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        fprintf(stderr, "DELETE produto failed: %s", PQerrorMessage(conn));
        PQclear(res);
        exit_nicely(conn);
    }

    PQclear(res);
}

// Função de menu para operações CRUD de Produto
void produto_menu(PGconn *conn) {
    int opcao;
    char id_produto[20], descricao[100], unidade[50];

    do {
        printf(" ______              _       _        \n");
        printf("| ___ \\            | |     | |       \n");
        printf("| |_/ / __ ___   __| |_   _| |_ ___  \n");
        printf("|  __/ '__/ _ \\ / _` | | | | __/ _ \\ \n");
        printf("| |  | | | (_) | (_| | |_| | || (_) |\n");
        printf("\\_|  |_|  \\___/ \\__,_|\\__,_|\\__\\___/ \n");
        printf("                                     \n");
        printf("                                     \n");
        printf("\nMenu de Produto\n");
        printf("1. Criar Produto\n");
        printf("2. Ler Produtos\n");
        printf("3. Atualizar Produto\n");
        printf("4. Deletar Produto\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar();  // Limpar o buffer do teclado

        switch(opcao) {
            case 1: // Criar Produto
                printf("Digite o ID do Produto: ");
                fgets(id_produto, 20, stdin);
                id_produto[strcspn(id_produto, "\n")] = 0;  // Remover o \n
                printf("Digite a Descrição do Produto: ");
                fgets(descricao, 100, stdin);
                descricao[strcspn(descricao, "\n")] = 0;  // Remover o \n
                printf("Digite a Unidade do Produto: ");
                fgets(unidade, 50, stdin);
                unidade[strcspn(unidade, "\n")] = 0;  // Remover o \n
                create_produto(conn, id_produto, descricao, unidade);
                break;

            case 2: // Ler Produtos
                read_produto(conn);
                break;

            case 3: // Atualizar Produto
                printf("Digite o ID do Produto a atualizar: ");
                fgets(id_produto, 20, stdin);
                id_produto[strcspn(id_produto, "\n")] = 0;  // Remover o \n
                printf("Digite a nova Descrição do Produto: ");
                fgets(descricao, 100, stdin);
                descricao[strcspn(descricao, "\n")] = 0;  // Remover o \n
                printf("Digite a nova Unidade do Produto: ");
                fgets(unidade, 50, stdin);
                unidade[strcspn(unidade, "\n")] = 0;  // Remover o \n
                update_produto(conn, id_produto, descricao, unidade);
                break;

            case 4: // Deletar Produto
                printf("Digite o ID do Produto a deletar: ");
                fgets(id_produto, 20, stdin);
                id_produto[strcspn(id_produto, "\n")] = 0;  // Remover o \n
                delete_produto(conn, id_produto);
                break;

            case 0: // Sair
                printf("Saindo...\n");
                break;

            default:
                printf("Opcao invalida!\n");
        }
    } while(opcao != 0);
}

void painel_produto() {
    const char *conninfo = "dbname=datafourth user=devfalconsz password=TheFalconsz";
    PGconn *conn = PQconnectdb(conninfo);

    if (PQstatus(conn) != CONNECTION_OK) {
        fprintf(stderr, "Connection to database failed: %s", PQerrorMessage(conn));
        exit_nicely(conn);
    }

    // Exibe o menu de produto
    produto_menu(conn);

    PQfinish(conn);
}