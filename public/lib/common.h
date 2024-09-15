#ifndef COMMON_H
#define COMMON_H

#include <libpq-fe.h>

// Declaração da função exit_nicely
void exit_nicely(PGconn *conn);

#endif // COMMON_H