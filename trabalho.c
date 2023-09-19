#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define MAX_N 100 // N�mero m�ximo de cidades

int n; // N�mero de cidades
double dist[MAX_N][MAX_N]; // Matriz de dist�ncias

// Fun��o para calcular o custo de um tour
double calcularCusto(int tour[], int tamanho) {
    double custo = 0.0;
    for (int i = 0; i < tamanho - 1; i++) {
        custo += dist[tour[i]][tour[i + 1]];
    }
    custo += dist[tour[tamanho - 1]][tour[0]]; // Voltar � cidade de origem
    return custo;
}

// Fun��o para trocar dois elementos em um array
void swap(int tour[], int i, int j) {
    int temp = tour[i];
    tour[i] = tour[j];
    tour[j] = temp;
}

// Implementa��o da metaheur�stica VNS
void VNS(double melhorCusto, int melhorTour[]) {
    int maxVizinhanca = 3; // N�mero m�ximo de vizinhan�as
    int k = 1; // Inicializa��o do tamanho da vizinhan�a

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
    srand(time(NULL)); // Inicializa a semente do gerador de n�meros aleat�rios

    FILE *arquivo;
    arquivo = fopen("grafo.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    fscanf(arquivo, "%d", &n); // L� o n�mero de cidades do arquivo

    // L� a matriz de dist�ncias do arquivo
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
