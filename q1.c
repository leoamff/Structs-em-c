#include <stdio.h>

struct estado {
    char nome[50];
    int numeroVeiculos;
    int numeroAcidentes;
};

void coletarDados(struct estado estados[]) {
    for (int i = 0; i < 26; i++) {
        printf("Informe o nome do estado %d: ", i + 1);
        scanf(" %[^\n]", estados[i].nome);
        printf("Informe o número de veículos que circulam no estado (em 2007): ");
        scanf("%d", &estados[i].numeroVeiculos);
        printf("Informe o número de acidentes de trânsito (em 2007): ");
        scanf("%d", &estados[i].numeroAcidentes);
    }
}

void encontrarMaiorMenorAcidentes(struct estado estados[], int* indiceMaior, int* indiceMenor) {
    *indiceMaior = *indiceMenor = 0;
    for (int i = 1; i < 26; i++) {
        if (estados[i].numeroAcidentes > estados[*indiceMaior].numeroAcidentes) {
            *indiceMaior = i;
        }
        if (estados[i].numeroAcidentes < estados[*indiceMenor].numeroAcidentes) {
            *indiceMenor = i;
        }
    }
}

float calcularPercentualVeiculos(struct estado estados[], int estado) {
    return ((float)estados[estado].numeroAcidentes / estados[estado].numeroVeiculos) * 100;
}

float calcularMediaAcidentes(struct estado estados[]) {
    int totalAcidentes = 0;
    for (int i = 0; i < 26; i++) {
        totalAcidentes += estados[i].numeroAcidentes;
    }
    return (float)totalAcidentes / 26;
}

void estadosAcimaDaMedia(struct estado estados[], float media) {
    printf("Estados acima da média de acidentes:\n");
    for (int i = 0; i < 26; i++) {
        if (estados[i].numeroAcidentes > media) {
            printf("%s\n", estados[i].nome);
        }
    }
}

int main() {
    struct estado estados[26];
    coletarDados(estados);
    
    int indiceMaior, indiceMenor;
    encontrarMaiorMenorAcidentes(estados, &indiceMaior, &indiceMenor);
    
    printf("Maior número de acidentes: %d em %s\n", estados[indiceMaior].numeroAcidentes, estados[indiceMaior].nome);
    printf("Menor número de acidentes: %d em %s\n", estados[indiceMenor].numeroAcidentes, estados[indiceMenor].nome);
    
    float media = calcularMediaAcidentes(estados);
    printf("Média de acidentes no país: %.2f\n", media);
    
    estadosAcimaDaMedia(estados, media);
    
    for (int i = 0; i < 26; i++) {
        float percentual = calcularPercentualVeiculos(estados, i);
        printf("Percentual de veículos envolvidos em acidentes no %s: %.2f%%\n", estados[i].nome, percentual);
    }
    
    return 0;
}
