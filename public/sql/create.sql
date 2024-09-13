CREATE DATABASE datafourth;

-- Tabela Cliente
CREATE TABLE Cliente (
    cpf_cnpj VARCHAR(20) PRIMARY KEY,
    nome VARCHAR(100) NOT NULL
);

-- Tabela Atendente
CREATE TABLE Atendente (
    id_atendente INT PRIMARY KEY AUTO_INCREMENT,
    nome VARCHAR(100) NOT NULL
);

-- Tabela Produto
CREATE TABLE Produto (
    id_produto INT PRIMARY KEY,
    descricao VARCHAR(255),
    unidade VARCHAR(50)
);

-- Tabela Fornecedor
CREATE TABLE Fornecedor (
    id_fornecedor INT PRIMARY KEY,
    cnpj VARCHAR(20) UNIQUE NOT NULL,
    nome VARCHAR(100) NOT NULL
);

-- Tabela Produto_Fornecedor (Entidade Fraca)
CREATE TABLE Produto_Fornecedor (
    id_produto INT,
    id_fornecedor INT,
    quantidade INT,
    valor_produto DECIMAL(10, 2),
    PRIMARY KEY (id_produto, id_fornecedor),
    FOREIGN KEY (id_produto) REFERENCES Produto(id_produto),
    FOREIGN KEY (id_fornecedor) REFERENCES Fornecedor(id_fornecedor)
);

-- Tabela Pedido
CREATE TABLE Pedido (
    id_pedido INT PRIMARY KEY,
    cpf_cnpj VARCHAR(20),
    data_entrega DATE,
    valor_total_pedido DECIMAL(10, 2),
    FOREIGN KEY (cpf_cnpj) REFERENCES Cliente(cpf_cnpj)
);

-- Tabela associativa Pedido_Atendente para o relacionamento muitos-para-muitos
CREATE TABLE Pedido_Atendente (
    id_pedido INT,
    id_atendente INT,
    data DATE,
    PRIMARY KEY (id_pedido, id_atendente, data),
    FOREIGN KEY (id_pedido) REFERENCES Pedido(id_pedido),
    FOREIGN KEY (id_atendente) REFERENCES Atendente(id_atendente)
);

-- Tabela Itens (Entidade Fraca em relação ao Pedido)
CREATE TABLE Itens (
    num_item INT,
    id_pedido INT,
    id_produto INT,
    quantidade INT,
    valor_unitario DECIMAL(10, 2),
    valor_total_item DECIMAL(10, 2),
    PRIMARY KEY (num_item, id_pedido),
    FOREIGN KEY (id_pedido) REFERENCES Pedido(id_pedido),
    FOREIGN KEY (id_produto) REFERENCES Produto(id_produto)
);
