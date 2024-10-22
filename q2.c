#include <stdio.h>
#include <string.h>

struct produto {
    int codigo;
    char descricao[50];
    float valorUnitario;
    int quantidadeEstoque;
};

void cadastrarProduto(struct produto produtos[], int* totalProdutos) {
    if (*totalProdutos < 40) {
        printf("Informe o código do produto: ");
        scanf("%d", &produtos[*totalProdutos].codigo);
        printf("Informe a descrição do produto: ");
        scanf(" %[^\n]", produtos[*totalProdutos].descricao);
        printf("Informe o valor unitário do produto: ");
        scanf("%f", &produtos[*totalProdutos].valorUnitario);
        printf("Informe a quantidade em estoque: ");
        scanf("%d", &produtos[*totalProdutos].quantidadeEstoque);
        (*totalProdutos)++;
    } else {
        printf("Capacidade de cadastro atingida.\n");
    }
}

void alterarValorUnitario(struct produto produtos[], int totalProdutos) {
    int codigo;
    printf("Informe o código do produto: ");
    scanf("%d", &codigo);
    for (int i = 0; i < totalProdutos; i++) {
        if (produtos[i].codigo == codigo) {
            printf("Informe o novo valor unitário: ");
            scanf("%f", &produtos[i].valorUnitario);
            return;
        }
    }
    printf("Produto não encontrado.\n");
}

float obterValorUnitario(struct produto produtos[], int totalProdutos, int codigo) {
    for (int i = 0; i < totalProdutos; i++) {
        if (produtos[i].codigo == codigo) {
            return produtos[i].valorUnitario;
        }
    }
    return -1;
}

int obterQuantidadeEstoque(struct produto produtos[], int totalProdutos, int codigo) {
    for (int i = 0; i < totalProdutos; i++) {
        if (produtos[i].codigo == codigo) {
            return produtos[i].quantidadeEstoque;
        }
    }
    return -1;
}

void realizarVenda(struct produto produtos[], int totalProdutos) {
    int codigo, quantidade;
    printf("Informe o código do produto: ");
    scanf("%d", &codigo);
    
    int index = -1;
    for (int i = 0; i < totalProdutos; i++) {
        if (produtos[i].codigo == codigo) {
            index = i;
            break;
        }
    }
    
    if (index == -1) {
        printf("Produto não encontrado.\n");
        return;
    }
    
    int estoque = produtos[index].quantidadeEstoque;
    if (estoque == 0) {
        printf("Produto com estoque zero.\n");
        return;
    }

    printf("Informe a quantidade desejada: ");
    scanf("%d", &quantidade);
    
    if (quantidade > estoque) {
        printf("Quantidade desejada maior que a disponível. Deseja efetivar a compra? (1 - Sim / 0 - Não): ");
        int resposta;
        scanf("%d", &resposta);
        if (resposta == 1) {
            printf("Valor a ser pago: %.2f\n", produtos[index].valorUnitario * estoque);
            produtos[index].quantidadeEstoque = 0;
        }
    } else {
        produtos[index].quantidadeEstoque -= quantidade;
        printf("Valor a ser pago: %.2f\n", produtos[index].valorUnitario * quantidade);
    }
}

void atualizarQuantidadeEstoque(struct produto produtos[], int totalProdutos) {
    int codigo, novaQuantidade;
    printf("Informe o código do produto: ");
    scanf("%d", &codigo);
    for (int i = 0; i < totalProdutos; i++) {
        if (produtos[i].codigo == codigo) {
            printf("Informe a nova quantidade em estoque: ");
            scanf("%d", &novaQuantidade);
            produtos[i].quantidadeEstoque = novaQuantidade;
            return;
        }
    }
    printf("Produto não encontrado.\n");
}

void exibirProdutos(struct produto produtos[], int totalProdutos) {
    printf("Produtos cadastrados:\n");
    for (int i = 0; i < totalProdutos; i++) {
        printf("Código: %d, Descrição: %s\n", produtos[i].codigo, produtos[i].descricao);
    }
}

void exibirProdutosEstoqueZero(struct produto produtos[], int totalProdutos) {
    printf("Produtos com estoque zero:\n");
    for (int i = 0; i < totalProdutos; i++) {
        if (produtos[i].quantidadeEstoque == 0) {
            printf("Código: %d, Descrição: %s\n", produtos[i].codigo, produtos[i].descricao);
        }
    }
}

int main() {
    struct produto produtos[40];
    int totalProdutos = 0;
    int opcao;

    do {
        printf("\nMenu:\n");
        printf("1. Cadastrar produto\n");
        printf("2. Alterar valor unitário\n");
        printf("3. Consultar valor unitário\n");
        printf("4. Consultar quantidade em estoque\n");
        printf("5. Realizar venda\n");
        printf("6. Atualizar quantidade em estoque\n");
        printf("7. Exibir todos os produtos\n");
        printf("8. Exibir produtos com estoque zero\n");
        printf("9. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: cadastrarProduto(produtos, &totalProdutos); break;
            case 2: alterarValorUnitario(produtos, totalProdutos); break;
            case 3: {
                int codigo;
                printf("Informe o código do produto: ");
                scanf("%d", &codigo);
                float valor = obterValorUnitario(produtos, totalProdutos, codigo);
                if (valor != -1) {
                    printf("Valor unitário: %.2f\n", valor);
                } else {
                    printf("Produto não encontrado.\n");
                }
                break;
            }
            case 4: {
                int codigo;
                printf("Informe o código do produto: ");
                scanf("%d", &codigo);
                int quantidade = obterQuantidadeEstoque(produtos, totalProdutos, codigo);
                if (quantidade != -1) {
                    printf("Quantidade em estoque: %d\n", quantidade);
                } else {
                    printf("Produto não encontrado.\n");
                }
                break;
            }
            case 5: realizarVenda(produtos, totalProdutos); break;
            case 6: atualizarQuantidadeEstoque(produtos, totalProdutos); break;
            case 7: exibirProdutos(produtos, totalProdutos); break;
            case 8: exibirProdutosEstoqueZero(produtos, totalProdutos); break;
            case 9: printf("Saindo...\n"); break;
            default: printf("Opção inválida.\n"); break;
        }
    } while (opcao != 9);

    return 0;
}
