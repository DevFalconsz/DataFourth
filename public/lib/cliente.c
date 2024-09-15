#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <libpq-fe.h>
#include "cliente.h"
// Conexão global com o banco de dados
PGconn *conn;

// Função para conectar ao banco de dados
void conectarBanco() {
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
void desconectarBanco() {
    PQfinish(conn);
}

// Função para validar CPF
int validarCPF(char *cpf) {
    int i, j, digito1 = 0, digito2 = 0;
    if(strlen(cpf) != 11) return 0;

    if((strcmp(cpf,"00000000000") == 0) || (strcmp(cpf,"11111111111") == 0) ||
       (strcmp(cpf,"22222222222") == 0) || (strcmp(cpf,"33333333333") == 0) ||
       (strcmp(cpf,"44444444444") == 0) || (strcmp(cpf,"55555555555") == 0) ||
       (strcmp(cpf,"66666666666") == 0) || (strcmp(cpf,"77777777777") == 0) ||
       (strcmp(cpf,"88888888888") == 0) || (strcmp(cpf,"99999999999") == 0))
        return 0;

    for(i = 0, j = 10; i < 9; i++, j--)
        digito1 += (cpf[i]-'0') * j;

    digito1 = (digito1 % 11) < 2 ? 0 : 11 - (digito1 % 11);
    if(digito1 != (cpf[9] - '0')) return 0;

    for(i = 0, j = 11; i < 10; i++, j--)
        digito2 += (cpf[i]-'0') * j;

    digito2 = (digito2 % 11) < 2 ? 0 : 11 - (digito2 % 11);
    if(digito2 != (cpf[10] - '0')) return 0;

    return 1;
}

// Função para validar CNPJ
int validarCNPJ(const char *cnpj) {
    int i, j, digito1 = 0, digito2 = 0;
    if(strlen(cnpj) != 14) return 0;

    if((strcmp(cnpj,"00000000000000") == 0) || (strcmp(cnpj,"11111111111111") == 0>       (strcmp(cnpj,"22222222222222") == 0) || (strcmp(cnpj,"33333333333333") == 0>       (strcmp(cnpj,"44444444444444") == 0) || (strcmp(cnpj,"55555555555555") == 0>       (strcmp(cnpj,"66666666666666") == 0) || (strcmp(cnpj,"77777777777777") == 0>       (strcmp(cnpj,"88888888888888") == 0) || (strcmp(cnpj,"99999999999999") == 0>        return 0;

    for(i = 0, j = 5; i < 12; i++, j--) {
        if (j < 2) j = 9;
        digito1 += (cnpj[i] - '0') * j;
    }
    digito1 = (digito1 % 11) < 2 ? 0 : 11 - (digito1 % 11);
    if(digito1 != (cnpj[12] - '0')) return 0;

    for(i = 0, j = 6; i < 13; i++, j--) {
        if (j < 2) j = 9;
        digito2 += (cnpj[i] - '0') * j;
    }
    digito2 = (digito2 % 11) < 2 ? 0 : 11 - (digito2 % 11);
    if(digito2 != (cnpj[13] - '0')) return 0;

    return 1;
}

// Função para criar um cliente no banco de dados
void criarCliente() {
    Cliente novoCliente;
    printf("Digite o nome do cliente: ");
    scanf(" %[^\n]", novoCliente.nome);

    printf("Escolha o tipo de documento:\n1. CPF\n2. CNPJ\n");
    scanf("%d", &novoCliente.tipoDocumento);

    if (novoCliente.tipoDocumento == 1) {
        printf("Digite o CPF (somente numeros): ");
        scanf("%s", novoCliente.documento);
        if (!validarCPF(novoCliente.documento)) {
            printf("CPF invalido!\n");
            return;
        }
    } else if (novoCliente.tipoDocumento == 2) {
        printf("Digite o CNPJ (somente numeros): ");
        scanf("%s", novoCliente.documento);
        if (!validarCNPJ(novoCliente.documento)) {
            printf("CNPJ invalido!\n");
            return;
        }
    } else {
        printf("Tipo de documento invalido!\n");
        return;
    }

    char query[256];
    snprintf(query, sizeof(query),
             "INSERT INTO cliente (nome, cpf_cnpj) VALUES ('%s', '%s');",
             novoCliente.nome, novoCliente.documento);

    PGresult *res = PQexec(conn, query);
    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        fprintf(stderr, "Erro ao inserir cliente: %s", PQerrorMessage(conn));
        PQclear(res);
        return;
    }

    printf("Cliente criado com sucesso!\n");
    PQclear(res);
}

// Função para listar clientes do banco de dados
void listarClientes() {
    PGresult *res = PQexec(conn, "SELECT nome, cpf_cnpj FROM cliente;");
    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        fprintf(stderr, "Erro ao listar clientes: %s", PQerrorMessage(conn));
        PQclear(res);
        return;
    }

    int linhas = PQntuples(res);
    if (linhas == 0) {
        printf("Nenhum cliente cadastrado.\n");
    } else {
        for (int i = 0; i < linhas; i++) {
            printf("Nome: %s\n", PQgetvalue(res, i, 0));
            printf("Documento: %s\n", PQgetvalue(res, i, 1));
        }
    }

    PQclear(res);
}

// Função para atualizar um cliente no banco de dados
void atualizarCliente() {
    listarClientes();

    char novoNome[100];
    char cpf_cnpj[20];

    printf("Digite o CPF/CPNJ do cliente que deseja atualizar: ");
    scanf("%s", cpf_cnpj);  // Usar %s já que cpf_cnpj é uma string

    printf("Digite o novo nome: ");
    scanf(" %[^\n]", novoNome);

    char query[256];
    snprintf(query, sizeof(query),
             "UPDATE cliente SET nome = '%s' WHERE cpf_cnpj = '%s';", novoNome, cp>
    PGresult *res = PQexec(conn, query);
    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        fprintf(stderr, "Erro ao atualizar cliente: %s", PQerrorMessage(conn));
        PQclear(res);
        return;
    }

    printf("Cliente atualizado com sucesso!\n");
    PQclear(res);
}

void deletarCliente() {
    listarClientes();  // Exibe a lista de clientes para o usuário escolher o ID

    char cpf_cnpj[20];  // Supondo que o CPF/CNPJ tenha no máximo 20 caracteres
    printf("Digite o CPF/CNPJ do cliente que deseja deletar: ");
    scanf("%s", cpf_cnpj);  // Usar %s já que cpf_cnpj é uma string

    char query[256];
    snprintf(query, sizeof(query), "DELETE FROM cliente WHERE cpf_cnpj = '%s';", c>    PGresult *res = PQexec(conn, query);

    // Verificar o status da execução
    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        // Capturar o erro retornado pelo banco de dados
        if (strstr(PQerrorMessage(conn), "violates foreign key constraint")) {
            printf("Erro: Não é possível deletar o cliente, pois há pedidos associ>        } else {
            fprintf(stderr, "Erro ao deletar cliente: %s", PQerrorMessage(conn));
        }
        PQclear(res);
        return;
    }

    printf("Cliente deletado com sucesso!\n");
    PQclear(res);
}

// Função para exibir o menu
void exibirMenu() {
    int opcao;

    do {
        printf(" _____  _  _               _        \n");
        printf("/  __ \\| |(_)             | |       \n");
        printf("| /  \\/| | _   ___  _ __  | |_  ___ \n");
        printf("| |    | || | / _ \\| '_ \\ | __|/ _ \\\n");
        printf("| \\__/\\| || ||  __/| | | || |_|  __/\n");
        printf(" \\____/|_||_| \\___||_| |_| \\__/\\___|\n");
        printf("                                    \n");
        printf("                                    \n");
        printf("\nEscolha uma operação:\n");
        printf("1. Criar Cliente\n");
        printf("2. Listar Clientes\n");
        printf("3. Atualizar Cliente\n");
        printf("4. Deletar Cliente\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                criarCliente();
                break;
            case 2:
                listarClientes();
                break;
            case 3:
                atualizarCliente();
                break;
            case 4:
                deletarCliente();
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida!\n");
                break;
        }
    } while (opcao != 0);
}