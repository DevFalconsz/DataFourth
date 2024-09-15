#include "common.h"
#include <string.h>
#include <stdlib.h>  // Inclua esta linha para declarar a função exit()

void exit_nicely(PGconn *conn) {
    PQfinish(conn);
    exit(1);
}

int validar_cnpj(const char *cnpj) {
    // Exemplo de validação simples
    if (strlen(cnpj) == 14) {  // Verifica se o CNPJ tem 14 caracteres
        return 1;
    }
    return 0;
}
