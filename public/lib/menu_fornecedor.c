#include "fornecedor_header.h"

void painel_fornecedor() {
    const char *conninfo = "dbname=datafourth user=devfalconsz password=TheFalconsz";
    PGconn *conn = PQconnectdb(conninfo);

    if (PQstatus(conn) != CONNECTION_OK) {
        fprintf(stderr, "Connection to database failed: %s", PQerrorMessage(conn));
        exit_nicely(conn);
    }

    // Chama o menu de fornecedor
    fornecedor_menu(conn);

    PQfinish(conn);
}
