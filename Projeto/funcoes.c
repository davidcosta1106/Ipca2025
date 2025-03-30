/***
 * @file funcoes.c
 * @brief Implementação das funções para manipulação de antenas
 * @author David Costa
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "struct.h"

/***
 * @brief Função para criar uma nova antena
 * @param freq Frequência da antena
 * @param x Coordenada x da posição da antena
 * @param y Coordenada y da posição da antena
 * @return Ponteiro para a nova antena
 */
Antena *criarAntena(char freq, int x, int y)
{
    Antena *nova = (Antena *)malloc(sizeof(Antena));
    if (!nova)
    {
        printf("Erro de alocacao de memoria!\n");
        exit(1);
    }
    nova->frequencia = freq;
    nova->x = x;
    nova->y = y;
    nova->prox = NULL;
    return nova;
}

/***
 * @brief Função para verificar se a posição (x, y) tem efeito nefasto
 * @param lista Ponteiro para a lista de antenas
 * @param freq Frequência da antena
 * @param x Coordenada x da posição a ser verificada
 * @param y Coordenada y da posição a ser verificada
 * @return true se a posição tem efeito nefasto, senão false
 */
bool posicaoNefasta(Antena *lista, char freq, int x, int y)
{
    Antena *a1, *a2;

    for (a1 = lista; a1 != NULL; a1 = a1->prox)
    {
        if (a1->frequencia == freq)
        {
            for (a2 = lista; a2 != NULL; a2 = a2->prox)
            {
                if (a2 != a1 && a2->frequencia == freq)
                {
                    int dx = a2->x - a1->x;
                    int dy = a2->y - a1->y;

                    if ((x == a1->x - dx && y == a1->y - dy) ||
                        (x == a2->x + dx && y == a2->y + dy))
                    {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

/***
  * @brief Função para verificar se a posição (x, y) tem efeito nefasto
  * @param lista Ponteiro para a lista de antenas
  * @param freq Frequência da antena
  * @param x Coordenada x da posição a ser verificada
  * @param y Coordenada y da posição a ser verificada
  * @return true se a posição tem efeito nefasto, senão false
  */
 bool verificaInterferencia(Antena *lista, char freq, int x, int y)
 {
     Antena *a1, *a2;
 
     for (a1 = lista; a1 != NULL; a1 = a1->prox)
     {
         if (a1->frequencia == freq)
         {
             for (a2 = lista; a2 != NULL; a2 = a2->prox)
             {
                 if (a2 != a1 && a2->frequencia == freq)
                 {
                     int dx = a2->x - a1->x;
                     int dy = a2->y - a1->y;
 
                     if (a1->y == a2->y && a1->y == y)
                     {
                         if (x == a1->x - dx * 2 || x == a2->x + dx * 2)
                         {
                             return true;
                         }
                     }
 
                     if (a1->x == a2->x && a1->x == x)
                     {
                         if (y == a1->y - dy * 2 || y == a2->y + dy * 2)
                         {
                             return true;
                         }
                     }
 
                     if (abs(dx) == abs(dy))
                     {
                         if ((x == a1->x - dx * 2 && y == a1->y - dy * 2) ||
                             (x == a2->x + dx * 2 && y == a2->y + dy * 2))
                         {
                             return true;
                         }
                     }
                 }
             }
         }
     }
 
     return false;
 }
 
/***
 * @brief Função para listar de forma tabular as antenas e efeitos nefastos
 * @param lista Ponteiro para a lista de antenas
 * @return void
 */
void listarMatriz(Antena *lista)
{
    char matriz[TAMANHO_MATRIZ][TAMANHO_MATRIZ];
    bool matrizMarcada[TAMANHO_MATRIZ][TAMANHO_MATRIZ] = {false}; // Para armazenar os efeitos nefastos

    // Inicializa a matriz com '.'
    for (int i = 0; i < TAMANHO_MATRIZ; i++)
        for (int j = 0; j < TAMANHO_MATRIZ; j++)
            matriz[i][j] = '.';

    // Preenche a matriz com as antenas
    for (Antena *aux = lista; aux != NULL; aux = aux->prox)
        matriz[aux->y-1][aux->x-1] = aux->frequencia;

    // Identifica e marca os efeitos nefastos na matriz booleana
    Antena *a1, *a2;
    for (a1 = lista; a1 != NULL; a1 = a1->prox)
    {
        for (a2 = lista; a2 != NULL; a2 = a2->prox)
        {
            if (a1 != a2 && a1->frequencia == a2->frequencia)
            {
                int dx = a2->x - a1->x;
                int dy = a2->y - a1->y;

                if (dx != 0 || dy != 0)
                {
                    int x1 = a1->x - dx;
                    int y1 = a1->y - dy;
                    int x2 = a2->x + dx;
                    int y2 = a2->y + dy;

                    if (x1 >= 0 && x1 < TAMANHO_MATRIZ && y1 >= 0 && y1 < TAMANHO_MATRIZ)
                        matrizMarcada[y1][x1] = true;

                    if (x2 >= 0 && x2 < TAMANHO_MATRIZ && y2 >= 0 && y2 < TAMANHO_MATRIZ)
                        matrizMarcada[y2][x2] = true;
                }
            }
        }
    }

    // Atualiza a matriz visual para incluir os efeitos nefastos
    // Marca os efeitos nefastos com '#'
for (int i = 0; i < TAMANHO_MATRIZ; i++)
{
    for (int j = 0; j < TAMANHO_MATRIZ; j++)
    {
        if (matriz[i][j] == '.') // Apenas se a posição estiver vazia
        {
            for (Antena *aux = lista; aux != NULL; aux = aux->prox)
            {
                if (posicaoNefasta(lista, aux->frequencia, j, i)) 
                {
                    matriz[i - 1][j - 1] = '#';
                    break; // Evita sobreposição desnecessária
                }
            }
        }
    }
}


    // Exibe a matriz no terminal
    printf("   ");
    for (int x = 1; x <= TAMANHO_MATRIZ; x++)
        printf("%2d ", x);
    printf("\n   ");
    for (int x = 0; x < TAMANHO_MATRIZ; x++)
        printf("---");
    printf("\n");

    for (int i = 0; i < TAMANHO_MATRIZ; i++)
    {
        printf("%2d| ", i + 1);
        for (int j = 0; j < TAMANHO_MATRIZ; j++)
        {
            printf("%c  ", matriz[i][j]);
        }
        printf("\n");
    }
}

/***
 * @brief Função para adicionar uma antena à lista
 * @brief Primeiro Coluna e depois Linha ex: (x, y) -> (coluna, linha)
 * @param lista Ponteiro para a lista de antenas
 * @param freq Frequência da antena
 * @param x Coordenada x da posição da antena
 * @param y Coordenada y da posição da antena
 * @return void
 */
void adicionarAntena(Antena **lista, char freq, int x, int y)
{
    // Verifica se está dentro dos limites da matriz
    if (x < 0 || x >= TAMANHO_MATRIZ || y < 0 || y >= TAMANHO_MATRIZ)
    {
        printf("Erro: A posicao (%d, %d) esta fora dos limites da matriz!\n", y, x);
        return;
    }

    // Verifica se a posição tem efeito nefasto
    if (posicaoNefasta(*lista, freq, x, y))  // <- Corrigido para passar (x, y) corretamente
    {
        printf("Erro: A posicao (%d, %d) tem efeito nefasto e nao pode ser usada!\n", y, x);
        return;
    }

    // Verifica interferência com outras antenas
    if (verificaInterferencia(*lista, freq, x, y))  // <- Corrigido para manter (x, y)
    {
        printf("Erro: A antena na posicao (%d, %d) com frequencia %c causaria interferencia!\n", y, x, freq);
        return;
    }

    Antena *nova = criarAntena(freq, x, y);  // <- Alterado para criar antena com (x, y) correto
    nova->prox = *lista;
    *lista = nova;

    printf("Antena adicionada na posicao (%d, %d) com frequencia %c.\n", y, x, freq);
}

/***
 * @brief Função para remover uma antena da lista
 * @param lista Ponteiro para a lista de antenas
 * @param x Coordenada x da posição da antena
 * @param y Coordenada y da posição da antena
 * @return void
 */
void removerAntena(Antena **lista, int x, int y)
{
    Antena *atual = *lista, *anterior = NULL;
    while (atual != NULL && (atual->x != x || atual->y != y))
    {
        anterior = atual;
        atual = atual->prox;
    }
    if (atual == NULL)
    {
        printf("Erro: Antena na posicao (%d, %d) nao encontrada!\n", y, x);
        return;
    }
    if (anterior == NULL)
    {
        *lista = atual->prox;
    }
    else
    {
        anterior->prox = atual->prox;
    }
    free(atual);
    printf("Antena removida da posicao (%d, %d).\n", y, x);
}

/***
 * @brief Função para listar as antenas da lista
 * @param lista Ponteiro para a lista de antenas
 * @return void
 */
void listarAntenas(Antena *lista)
{
    printf("Lista de Antenas:\n");
    while (lista)
    {
        printf("Frequencia: %c - Posicao: (%d, %d)\n", lista->frequencia, lista->y, lista->x);
        lista = lista->prox;
    }
}

/***
 * @brief Função para liberar a memória alocada para a lista de antenas
 * @param lista Ponteiro para a lista de antenas
 * @return void
 */
void liberarLista(Antena *lista)
{
    Antena *temp;
    while (lista)
    {
        temp = lista;
        lista = lista->prox;
        free(temp);
    }
    printf("Lista de antenas liberada.\n");
}

/***
 * @brief Função para listar as localizações com efeito nefasto
 * @param lista Ponteiro para a lista de antenas
 * @return void
 */
void listarEfeitosNefastos(Antena *lista)
{
    printf("Localizacoes com efeito nefasto:\n");
    Antena *a1, *a2;
    bool matrizMarcada[TAMANHO_MATRIZ][TAMANHO_MATRIZ] = {false};

    for (a1 = lista; a1 != NULL; a1 = a1->prox)
    {
        for (a2 = lista; a2 != NULL; a2 = a2->prox)
        {
            if (a1 != a2 && a1->frequencia == a2->frequencia)
            {
                int dx = a2->x - a1->x;
                int dy = a2->y - a1->y;

                if (dx != 0 || dy != 0)
                {
                    int x1 = a1->x - dx;
                    int y1 = a1->y - dy;
                    int x2 = a2->x + dx;
                    int y2 = a2->y + dy;

                    if (x1 >= 0 && x1 < TAMANHO_MATRIZ && y1 >= 0 && y1 < TAMANHO_MATRIZ && !matrizMarcada[y1][x1])
                    {
                        printf("Efeito nefasto em (%d, %d)\n", y1, x1);
                        matrizMarcada[y1][x1] = true;
                    }
                    
                    if (x2 >= 0 && x2 < TAMANHO_MATRIZ && y2 >= 0 && y2 < TAMANHO_MATRIZ && !matrizMarcada[y2][x2])
                    {
                        printf("Efeito nefasto em (%d, %d)\n", y2, x2);
                        matrizMarcada[y2][x2] = true;
                    }
                }
            }
        }
    }
}

/***
 * @brief Função para carregar as antenas do ficheiro
 * @param lista Ponteiro para a lista de antenas
 * @param nomeFicheiro Nome do ficheiro a ser carregado
 * @return void
 */
void carregarAntenasDoFicheiro(Antena **lista, const char *nomeFicheiro)
{
    FILE *f = fopen(nomeFicheiro, "r");
    if (!f)
    {
        printf("Erro ao abrir o ficheiro!\n");
        return;
    }

    char linha[TAMANHO_MATRIZ + 1]; // Para armazenar uma linha do ficheiro
    int y = 0;

    // Percorre o ficheiro linha por linha
    while (fgets(linha, sizeof(linha), f))
    {
        for (int x = 0; linha[x] != '\n' && linha[x] != '\0'; x++)
        {

            if (linha[x] != '.' && linha[x] != '\n' && linha[x] != '\0')
            {
                // Se não for um ponto, considera como antena
                adicionarAntena(lista, linha[x], x+1, y+1);
            }
        }
        y++; // Avança para a próxima linha
    }

    fclose(f);
    printf("Carregamento do ficheiro concluído.\n");
}
