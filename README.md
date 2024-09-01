# DataFourth
O projeto 'DataFourth' consiste na criação de um banco de dados compartilhado para consolidar e organizar todo o conteúdo da disciplina ministrada pelo professor Olegário.


## Organização do projeto:
```bash
/public
│
├── /src
│   └── main.c                        # Programa principal que integra todas os cabeçalhos
│
├── /lib
│   ├── cliente.h                     # Cabeçalho da entidade Cliente
│   ├── pedido.h                      # Cabeçalho da entidade Pedido
│   ├── itens.h                       # Cabeçalho da entidade Itens
│   ├── atendente.h                   # Cabeçalho da entidade Atendente
│   ├── fornecedor.h                  # Cabeçalho da entidade Fornecedor
│   ├── produto.h                     # Cabeçalho da entidade Produto
│   ├── produto_fornecedor.h          # Cabeçalho da entidade Produto_Fornecedor
│   └── pedido_atendente.h            # Cabeçalho da entidade Pedido_Atendente
│
├── /sql
│   └── create.sql                    # Código de criação do banco de dados para testes unitários
│
├── README.md                         # Descrição geral do projeto e instruções de uso
└── LICENSE                           # Arquivo de licença do projeto
```
## Modo de utilização dos cabeçalhos:
Para garantir que o arquivo main.c possa utilizar os cabeçalhos (*.h) localizados na pasta lib, você deve especificar o caminho completo para cada cabeçalho na inclusão no seu código. Aqui está como você deve prosseguir:
```c
#include "../lib/cliente.h"                 // Inclusão do cabeçalho da entidade Cliente
#include "../lib/pedido.h"                  // Inclusão do cabeçalho da entidade Pedido
#include "../lib/itens.h"                   // Inclusão do cabeçalho da entidade Itens
#include "../lib/atendente.h"               // Inclusão do cabeçalho da entidade Atendente
#include "../lib/fornecedor.h"              // Inclusão do cabeçalho da entidade Fornecedor
#include "../lib/produto.h"                 // Inclusão do cabeçalho da entidade Produto
#include "../lib/produto_fornecedor.h"      // Inclusão do cabeçalho da entidade Produto_Fornecedor
#include "../lib/pedido_atendente.h"        // Inclusão do cabeçalho da entidade Pedido_Atendente
```
