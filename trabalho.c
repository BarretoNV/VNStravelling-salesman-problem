#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define MAX_N 100 // Número máximo de cidades

int n; // Número de cidades
double dist[MAX_N][MAX_N]; // Matriz de distâncias

// Função para calcular o custo de um tour
double calcularCusto(int tour[], int tamanho) {
    double custo = 0.0;
    for (int i = 0; i < tamanho - 1; i++) {
        custo += dist[tour[i]][tour[i + 1]];
    }
    custo += dist[tour[tamanho - 1]][tour[0]]; // Voltar à cidade de origem
    return custo;
}

// Função para trocar dois elementos em um array
void swap(int tour[], int i, int j) {
    int temp = tour[i];
    tour[i] = tour[j];
    tour[j] = temp;
}

// Implementação da metaheurística VNS
void VNS(double melhorCusto, int melhorTour[]) {
    int maxVizinhanca = 3; // Número máximo de vizinhanças
    int k = 1; // Inicialização do tamanho da vizinhança

    int *atualTour = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        atualTour[i] = melhorTour[i];
    }

    while (k <= maxVizinhanca) {
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                swap(atualTour, i, j);
                double custoAtual = calcularCusto(atualTour, n);
                if (custoAtual < melhorCusto) {
                    melhorCusto = custoAtual;
                    for (int x = 0; x < n; x++) {
                        melhorTour[x] = atualTour[x];
                    }
                }
                swap(atualTour, i, j); // Desfaz a troca
            }
        }
        k++;
    }

    free(atualTour);
}

int main() {
    srand(time(NULL)); // Inicializa a semente do gerador de números aleatórios

    FILE *arquivo;
    arquivo = fopen("grafo.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    fscanf(arquivo, "%d", &n); // Lê o número de cidades do arquivo

    // Lê a matriz de distâncias do arquivo
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            fscanf(arquivo, "%lf", &dist[i][j]);
        }
    }

    fclose(arquivo); // Fecha o arquivo

    int tour[MAX_N]; // Array para armazenar o tour
    for (int i = 0; i < n; i++) {
        tour[i] = i;
    }

    double custoInicial = calcularCusto(tour, n);
    double melhorCusto = custoInicial;

    printf("Tour inicial (custo = %.2lf): ", custoInicial);
    for (int i = 0; i < n; i++) {
        printf("%d ", tour[i]);
    }
    printf("\n");

    VNS(melhorCusto, tour);

    printf("Melhor tour encontrado (custo = %.2lf): ", melhorCusto);
    for (int i = 0; i < n; i++) {
        printf("%d ", tour[i]);
    }
    printf("\n");

    return 0;
}
