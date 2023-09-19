// Guilherme Barreto, Higor Brandão, Micaella Pereira, Vinicius Monteiro

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>

#define MAX_VERTICES 100 // Número máximo de vértices
#define MAX_ARESTAS 1000 // Número máximo de arestas
#define MAX_ITERACOES 100 // Número máximo de iterações

// Estrutura para representar o grafo
typedef struct
{
    int numVertices;
    int numArestas;
    double matrizAdj[MAX_VERTICES][MAX_VERTICES];
} Grafo;

// Função para ler o grafo do arquivo de entrada
Grafo lerGrafo()
{
    printf("lerGrafo\n");
    Grafo grafo;
    FILE *arquivo;
    arquivo = fopen("grafo.txt", "r");

    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo de entrada.\n");
        exit(1);
    }

    fscanf(arquivo, "%d %d", &grafo.numVertices, &grafo.numArestas);

    for (int i = 0; i < grafo.numVertices; i++)
    {
        for (int j = 0; j < grafo.numVertices; j++)
        {
            fscanf(arquivo, "%lf", &grafo.matrizAdj[i][j]);
        }
    }

    fclose(arquivo);
    return grafo;
}

// Função para calcular o custo total de um ciclo hamiltoniano
double calcularCusto(int ciclo[], Grafo grafo)
{
    printf("calcularCusto\n");
    double custo = 0.0;
    for (int i = 0; i < grafo.numVertices - 1; i++)
    {
        custo += grafo.matrizAdj[ciclo[i]][ciclo[i + 1]];
    }
    custo += grafo.matrizAdj[ciclo[grafo.numVertices - 1]][ciclo[0]]; // Volta para o início
    printf("\nCusto: %.2f\n", custo);
    return custo;
}

// Função para trocar duas cidades em um ciclo
void trocarCidades(int ciclo[], int cidade1, int cidade2)
{
    printf("trocarCidades\n");
    int temp = ciclo[cidade1];
    ciclo[cidade1] = ciclo[cidade2];
    ciclo[cidade2] = temp;
}

// Função que implementa a Busca em Vizinhança Variável (VNS)
void buscaVizinhancaVariavel(Grafo grafo)
{
    printf("buscaVizinhancaVariavel \n");
    int melhorCiclo[grafo.numVertices]; // n = numVertices
    int cicloAtual[grafo.numVertices];
    int iteracoes = 0;

    // Gere um ciclo inicial aleatório
    for (int i = 0; i < grafo.numVertices; i++)
    {
        cicloAtual[i] = i;
    }

    double melhorCusto = calcularCusto(cicloAtual, grafo);

    while (iteracoes < MAX_ITERACOES)
    {
        int vizinhanca = 1;
        while (vizinhanca <= 3)
        { // Experimente diferentes vizinhanças
            int cidade1, cidade2;
            do
            {
                cidade1 = rand() % grafo.numVertices;
                cidade2 = rand() % grafo.numVertices;
            } while ((cidade1 == 0) || (cidade2 == 0));

             trocarCidades(cicloAtual, cidade1, cidade2);

            double custoAtual = calcularCusto(cicloAtual, grafo);

            if (custoAtual < melhorCusto)
            {
                melhorCusto = custoAtual;
                for (int i = 0; i < grafo.numVertices; i++)
                {
                    melhorCiclo[i] = cicloAtual[i];
                }
                vizinhanca = 1; // Reinicie a vizinhança após uma melhoria
            }
            else
            {
                trocarCidades(cicloAtual, cidade1, cidade2);
                vizinhanca++;
            }
            printf("\nVIZINHANCA: %d\n", vizinhanca);
        }

        iteracoes++;
    }

    printf("Melhor ciclo encontrado: ");
    for (int i = 0; i < grafo.numVertices; i++)
    {
        printf("%d -> ", melhorCiclo[i]);
    }
    printf("%d\n", melhorCiclo[0]); // Volta para o início

    printf("Custo total do ciclo: %.2lf\n", melhorCusto);
}

int main()
{
    srand(time(NULL));

    Grafo grafo = lerGrafo();

    buscaVizinhancaVariavel(grafo);

    return 0;
}