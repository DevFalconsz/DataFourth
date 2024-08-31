# DataOlegario
O projeto 'DataOlegario' consiste na criação de um banco de dados compartilhado para consolidar e organizar todo o conteúdo da disciplina ministrada pelo professor Olegário.


## Organização do projeto:
```bash
/public
│
├── /source
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
├── README.md                         # Descrição geral do projeto e instruções de uso
└── LICENSE                           # Arquivo de licença do projeto

