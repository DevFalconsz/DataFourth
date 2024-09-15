#ifndef ATENDENTE_H
#define ATENDENTE_H

#include <libpq-fe.h>

typedef struct {
    char nome[100];
} Atendente;

// Funções para conexão ao banco de dados
void conectarBancoAtendente();
void desconectarBancoAtendente();

// Funções CRUD para Atendente
void criarAtendente();
void listarAtendentes();
void atualizarAtendente();
void deletarAtendente();

// Função para exibir o menu de Atendente
void menuAtendente();

#endif
