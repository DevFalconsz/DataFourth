#ifndef FORNECEDOR_HEADER_H
#define FORNECEDOR_HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <libpq-fe.h>
#include <string.h>
#include "common.h"  // Certifique-se de que common.h contém a função validar_cnpj

// Declaração da função validar_cnpj (caso não esteja no common.h)
int validar_cnpj(const char *cnpj);

// Exemplo de Validação do CNPJ

// Função para criar um fornecedor na tabela 'fornecedor'
void create_fornecedor(PGconn *conn, const char *id_fornecedor, const char *cnpj, const char *nome) {
    // Validação do CNPJ
    if (!validar_cnpj(cnpj)) {
        fprintf(stderr, "CNPJ inválido: %s\n", cnpj);
        exit_nicely(conn);
    }
    const char *paramValues[3] = {id_fornecedor, cnpj, nome};
    PGresult *res = PQexecParams(conn,
    "INSERT INTO fornecedor (id_fornecedor, cnpj, nome) VALUES ($1, $2, $3)",
    3, /* número de parâmetros */
    NULL, /* tipos dos parâmetros */
    paramValues,
    NULL, /* comprimentos dos parâmetros */
    NULL, /* formatos dos parâmetros */
    0); /* formato do resultado */

    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        fprintf(stderr, "INSERT fornecedor failed: %s", PQerrorMessage(conn));
        PQclear(res);
        exit_nicely(conn);
    }
    PQclear(res);
}

// Função para ler todos os fornecedores da tabela 'fornecedor'
void read_fornecedor(PGconn *conn) {
    PGresult *res = PQexec(conn, "SELECT * FROM fornecedor");

    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        fprintf(stderr, "SELECT failed: %s", PQerrorMessage(conn));
        PQclear(res);
        exit_nicely(conn);
    }

    int rows = PQntuples(res);
    for (int i = 0; i < rows; i++) {
        printf("ID: %s, CNPJ: %s, Nome: %s\n", PQgetvalue(res, i, 0), PQgetvalue(res, i, 1), PQgetvalue(res, i, 2));
    }

    PQclear(res);
}

// Função para atualizar um fornecedor na tabela 'fornecedor'
void update_fornecedor(PGconn *conn, const char *id_fornecedor, const char *novo_cnpj, const char *novo_nome) {
    // Use novo_cnpj no lugar de cnpj
    if (!validar_cnpj(novo_cnpj)) {
        fprintf(stderr, "CNPJ inválido: %s\n", novo_cnpj);
        exit_nicely(conn);
    }
    const char *paramValues[3] = {novo_cnpj, novo_nome, id_fornecedor};
    PGresult *res = PQexecParams(conn,
    "UPDATE fornecedor SET cnpj = $1, nome = $2 WHERE id_fornecedor = $3",
    3,
    NULL,
    paramValues,
    NULL,
    NULL,
    0);

    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        fprintf(stderr, "UPDATE fornecedor failed: %s", PQerrorMessage(conn));
        PQclear(res);
        exit_nicely(conn);
    }

    PQclear(res);
}

// Função para deletar um fornecedor da tabela 'fornecedor'
void delete_fornecedor(PGconn *conn, const char *id_fornecedor) {
    const char *paramValues[1] = {id_fornecedor};
    PGresult *res = PQexecParams(conn,
    "DELETE FROM fornecedor WHERE id_fornecedor = $1",
    1,
    NULL,
    paramValues,
    NULL,
    NULL,
    0);

    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        fprintf(stderr, "DELETE fornecedor failed: %s", PQerrorMessage(conn));
        PQclear(res);
        exit_nicely(conn);
    }

    PQclear(res);
}

// Função de menu para operações CRUD de Fornecedor
void fornecedor_menu(PGconn *conn) {
    int opcao;
    char id_fornecedor[20], cnpj[20], nome[50];

    do {
        printf("______                                 _            \n");
        printf("|  ___|                               | |           \n");
        printf("| |_ ___  _ __ _ __   ___  ___ ___  __| | ___  _ __ \n");
        printf("|  _/ _ \\| '__| '_ \\ / _ \\/ __/ _ \\/ _` |/ _ \\| '__|\n");
        printf("| || (_) | |  | | | |  __/ (_|  __/ (_| | (_) | |   \n");
        printf("\\_| \\___/|_|  |_| |_|\\___|\\___\\___|\\__,_|\\___/|_|   \n");
        printf("                                                    \n");
        printf("                                                    \n");
        printf("\nMenu de Fornecedor\n");
        printf("1. Criar Fornecedor\n");
        printf("2. Ler Fornecedores\n");
        printf("3. Atualizar Fornecedor\n");
        printf("4. Deletar Fornecedor\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar();  // Limpar o buffer do teclado

        switch(opcao) {
            case 1: // Criar Fornecedor
                printf("Digite o ID do Fornecedor: ");
                fgets(id_fornecedor, 20, stdin);
                id_fornecedor[strcspn(id_fornecedor, "\n")] = 0;  // Remover \n
                printf("Digite o CNPJ do Fornecedor: ");
                fgets(cnpj, 20, stdin);
                cnpj[strcspn(cnpj, "\n")] = 0;  // Remover \n
                printf("Digite o Nome do Fornecedor: ");
                fgets(nome, 50, stdin);
                nome[strcspn(nome, "\n")] = 0;  // Remover \n
                create_fornecedor(conn, id_fornecedor, cnpj, nome);
                break;

            case 2: // Ler Fornecedores
                read_fornecedor(conn);
                break;

            case 3: // Atualizar Fornecedor
                printf("Digite o ID do Fornecedor a atualizar: ");
                fgets(id_fornecedor, 20, stdin);
                id_fornecedor[strcspn(id_fornecedor, "\n")] = 0;  // Remover \n
                printf("Digite o novo CNPJ: ");
                fgets(cnpj, 20, stdin);
                cnpj[strcspn(cnpj, "\n")] = 0;  // Remover \n
                printf("Digite o novo Nome: ");
                fgets(nome, 50, stdin);
                nome[strcspn(nome, "\n")] = 0;  // Remover \n
                update_fornecedor(conn, id_fornecedor, cnpj, nome);
                break;

            case 4: // Deletar Fornecedor
                printf("Digite o ID do Fornecedor a deletar: ");
                fgets(id_fornecedor, 20, stdin);
                id_fornecedor[strcspn(id_fornecedor, "\n")] = 0;  // Remover \n
                delete_fornecedor(conn, id_fornecedor);
                break;

            case 0: // Sair
                printf("Saindo...\n");
                break;

            default:
                printf("Opcao invalida!\n");
        }
    } while(opcao != 0);
}

#endif /* FORNECEDOR_HEADER_H */


