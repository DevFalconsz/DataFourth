#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <libpq-fe.h>
#include "atendente.h"

// Conexão global com o banco de dados
PGconn *conn;

// Função para conectar ao banco de dados
void conectarBancoAtendente() {
    const char *conninfo = "host=localhost dbname=datafourth user=devfalconsz pass>    conn = PQconnectdb(conninfo);

    if (PQstatus(conn) != CONNECTION_OK) {
        fprintf(stderr, "Erro de conexão: %s", PQerrorMessage(conn));
        PQfinish(conn);
        exit(1);
    } else {
        printf("Conexão ao banco de dados realizada com sucesso!\n");
    }
}

// Função para desconectar do banco de dados
void desconectarBancoAtendente() {
    PQfinish(conn);
}

// Função para criar um atendente
void criarAtendente() {
    Atendente novoAtendente;
    printf("Digite o nome do Atendente: ");
    scanf(" %[^\n]", novoAtendente.nome);

    char query[256];
    snprintf(query, sizeof(query),
             "INSERT INTO atendente (nome) VALUES ('%s');",
             novoAtendente.nome);

    PGresult *res = PQexec(conn, query);
    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        fprintf(stderr, "Erro ao inserir Atendente: %s", PQerrorMessage(conn));
        PQclear(res);
        return;
    }

    printf("Atendente criado com sucesso!\n");
    PQclear(res);
}

// Função para listar clientes do banco de dados
void listarAtendentes() {
    PGresult *res = PQexec(conn, "SELECT nome, id_atendente FROM atendente;");
    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        fprintf(stderr, "Erro ao listar Atendente: %s", PQerrorMessage(conn));
        PQclear(res);
        return;
    }

    int linhas = PQntuples(res);
    if (linhas == 0) {
        printf("Nenhum Atendente cadastrado.\n");
    } else {
        for (int i = 0; i < linhas; i++) {
            printf("Nome: %s\n", PQgetvalue(res, i, 0));
            printf("ID Atendente: %s\n", PQgetvalue(res, i, 1));
        }
    }

    PQclear(res);
}

// Função para atualizar um cliente no banco de dados
void atualizarAtendente() {
    listarAtendentes();
    char novoNome[100];
    int id;
    printf("Digite o ID do Atendente que deseja atualizar: ");
    scanf("%d", &id);

    printf("Digite o novo nome: ");
    scanf(" %[^\n]", novoNome);

    char query[256];
    snprintf(query, sizeof(query),
             "UPDATE atendente SET nome = '%s' WHERE id_atendente = %d;", novoNome>
    PGresult *res = PQexec(conn, query);
    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        fprintf(stderr, "Erro ao atualizar Atendente: %s", PQerrorMessage(conn));
        PQclear(res);
        return;
    }

    printf("Atendente atualizado com sucesso!\n");
    PQclear(res);
}

// Função para deletar um atendente
void deletarAtendente() {
    listarAtendentes();  // Exibe a lista de clientes para o usuário escolher o ID

    int id;

    printf("Digite o ID do atendente que deseja deletar: ");
    scanf("%d", &id);  // Usar %s já que cpf_cnpj é uma string

    char query[256];
    snprintf(query, sizeof(query), "DELETE FROM atendente WHERE id_atendente = '%d>    PGresult *res = PQexec(conn, query);

    // Verificar o status da execução
    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        // Capturar o erro retornado pelo banco de dados
        if (strstr(PQerrorMessage(conn), "violates foreign key constraint")) {
            printf("Erro: Não é possível deletar o atendente, pois há pedidos asso>        } else {
            fprintf(stderr, "Erro ao deletar cliente: %s", PQerrorMessage(conn));
        }
        PQclear(res);
        return;
    }

    printf("Cliente deletado com sucesso!\n");
    PQclear(res);
}

// Função para exibir o menu e interagir com o usuário
void menuAtendente() {
    int opcao;

    do {
        printf("\nMenu de Atendentes:\n");
        printf("1. Criar Atendente\n");
        printf("2. Listar Atendentes\n");
        printf("3. Atualizar Atendente\n");
        printf("4. Deletar Atendente\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: {
                criarAtendente();
                break;
            }
            case 2:
                listarAtendentes();
                break;
            case 3: {
                atualizarAtendente();
                break;
            }
            case 4: {
                deletarAtendente();
                break;
            }
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida!\n");
                break;
        }
    } while (opcao != 0);
}