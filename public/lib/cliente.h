#ifndef CLIENTE_H
#define CLIENTE_H

#include <libpq-fe.h>

typedef struct {
    char nome[100];
    char documento[20];
    int tipoDocumento; // 1 para CPF, 2 para CNPJ
} Cliente;

void conectarBanco();
void desconectarBanco();
int validarCPF(char *cpf);
int validarCNPJ(const char *cnpj);
void criarCliente();
void listarClientes();
void atualizarCliente();
void deletarCliente();
void exibirMenu();

#endif