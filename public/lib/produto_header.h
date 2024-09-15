#ifndef PRODUTO_HEADER_H
#define PRODUTO_HEADER_H

#include <libpq-fe.h>  // Inclui as funções da libpq para PostgreSQL

// Declaração da função para criar um produto na tabela 'produto'
void create_produto(PGconn *conn, const char *id_produto, const char *descricao, const char *unidade);

// Declaração da função para ler todos os produtos da tabela 'produto'
void read_produto(PGconn *conn);

// Declaração da função para atualizar um produto na tabela 'produto'
void update_produto(PGconn *conn, const char *id_produto, const char *nova_descricao, const char *nova_unidade);

// Declaração da função para deletar um produto na tabela 'produto'
void delete_produto(PGconn *conn, const char *id_produto);

#endif /* PRODUTO_HEADER_H */
