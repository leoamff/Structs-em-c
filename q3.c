#include <stdio.h>
#include <string.h>

struct conta {
    int numeroConta;
    char nome[50];
    char cpf[12];
    char telefone[15];
    float saldo;
};

int buscarConta(struct conta contas[], int totalContas, int numeroConta) {
    if (totalContas == 0) return -1;
    for (int i = 0; i < totalContas; i++) {
        if (contas[i].numeroConta == numeroConta) {
            return i;
        }
    }
    return -2;
}

void cadastrarConta(struct conta contas[], int* totalContas, int numeroConta) {
    if (*totalContas >= 100) {
        printf("Limite de contas atingido.\n");
        return;
    }
    if (buscarConta(contas, *totalContas, numeroConta) >= 0) {
        printf("Número da conta já cadastrado.\n");
        return;
    }
    contas[*totalContas].numeroConta = numeroConta;
    printf("Informe o nome do titular: ");
    scanf(" %[^\n]", contas[*totalContas].nome);
    printf("Informe o CPF do titular: ");
    scanf(" %[^\n]", contas[*totalContas].cpf);
    printf("Informe o telefone de contato: ");
    scanf(" %[^\n]", contas[*totalContas].telefone);
    contas[*totalContas].saldo = 0.0;
    (*totalContas)++;
}

void consultarSaldo(struct conta contas[], int totalContas, int numeroConta) {
    int pos = buscarConta(contas, totalContas, numeroConta);
    if (pos >= 0) {
        printf("Saldo da conta %d: %.2f\n", contas[pos].numeroConta, contas[pos].saldo);
    } else {
        printf("Conta não cadastrada.\n");
    }
}

void deposito(struct conta contas[], int totalContas, int numeroConta) {
    int pos = buscarConta(contas, totalContas, numeroConta);
    if (pos >= 0) {
        float valor;
        printf("Informe o valor do depósito: ");
        scanf("%f", &valor);
        contas[pos].saldo += valor;
        printf("Depósito efetuado. Novo saldo: %.2f\n", contas[pos].saldo);
    } else {
        printf("Conta não cadastrada.\n");
    }
}

void saque(struct conta contas[], int totalContas, int numeroConta) {
    int pos = buscarConta(contas, totalContas, numeroConta);
    if (pos >= 0) {
        float valor;
        printf("Informe o valor do saque: ");
        scanf("%f", &valor);
        if (valor > contas[pos].saldo) {
            printf("Saldo insuficiente.\n");
        } else {
            contas[pos].saldo -= valor;
            printf("Saque efetuado. Novo saldo: %.2f\n", contas[pos].saldo);
        }
    } else {
        printf("Conta não cadastrada.\n");
    }
}

void exibirContas(struct conta contas[], int totalContas) {
    printf("Contas cadastradas:\n");
    for (int i = 0; i < totalContas; i++) {
        printf("Número da conta: %d, Nome: %s, Telefone: %s\n",
               contas[i].numeroConta, contas[i].nome, contas[i].telefone);
    }
}

int main() {
    struct conta contas[100];
    int totalContas = 0;
    int opcao;

    do {
        printf("\nMenu:\n");
        printf("1. Cadastrar nova conta\n");
        printf("2. Consultar saldo\n");
        printf("3. Fazer depósito\n");
        printf("4. Fazer saque\n");
        printf("5. Exibir todas as contas\n");
        printf("6. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: {
                int numeroConta;
                printf("Informe o número da nova conta: ");
                scanf("%d", &numeroConta);
                cadastrarConta(contas, &totalContas, numeroConta);
                break;
            }
            case 2: {
                int numeroConta;
                printf("Informe o número da conta: ");
                scanf("%d", &numeroConta);
                consultarSaldo(contas, totalContas, numeroConta);
                break;
            }
            case 3: {
                int numeroConta;
                printf("Informe o número da conta: ");
                scanf("%d", &numeroConta);
                deposito(contas, totalContas, numeroConta);
                break;
            }
            case 4: {
                int numeroConta;
                printf("Informe o número da conta: ");
                scanf("%d", &numeroConta);
                saque(contas, totalContas, numeroConta);
                break;
            }
            case 5: exibirContas(contas, totalContas); break;
            case 6: printf("Saindo...\n"); break;
            default: printf("Opção inválida.\n"); break;
        }
    } while (opcao != 6);

    return 0;
}
