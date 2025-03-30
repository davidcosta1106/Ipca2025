/***
 * @file struct.h
 * @brief Definição das estruturas de dados para o problema das antenas
 * @author David Costa
 */
#ifndef STRUCTS_H
#define STRUCTS_H

#define TAMANHO_MATRIZ 10  // Tamanho da matriz 10x10

/***
 * @brief Estrutura de dados para representar uma antena
 * @param frequencia Frequência da antena
 * @param x Coordenada x da posição da antena
 */
typedef struct Antena {
    char frequencia;  // Frequência da antena
    int x, y;         // Posições da antena
    struct Antena *prox;  // Ponteiro para a próxima antena
} Antena;

/***
 * @brief Estrutura de dados para representar a rede de antenas
 * @param lista Lista ligada de antenas
 * @param matriz Matriz de ocupação para verificar interferências
 */
typedef struct RedeAntenas{
    Antena *lista;    // Lista ligada de antenas
    char matriz[TAMANHO_MATRIZ][TAMANHO_MATRIZ];  // Matriz de ocupação para verificar interferências
} RedeAntenas;

#endif
