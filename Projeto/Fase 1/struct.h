/***
 * @file struct.h
 * @brief Definição das estruturas de dados para o problema das antenas
 * @author David Costa
 */
#ifndef STRUCTS_H
#define STRUCTS_H
#include <stdbool.h>

/***
 * @brief Estrutura de dados para representar uma antena
 * @param frequencia Frequência da antena
 * @param x Coordenada x da posição da antena
 */
typedef struct Antena {
    char freq;  // Frequência da antena
    int x, y;         // Posições da antena
    struct Antena *prox;  // Ponteiro para a próxima antena
} Antena;

/***
 * @brief Estrutura de dados para representar um efeito nefasto
 * @param tipo Tipo do efeito nefasto
 */
typedef struct RedeAntenas{
    int x, y;               //Coordenadas (linha, coluna)
    struct RedeAntenas* prox;   //Apontador para o próximo efeito na lista
} RedeAntenas;

#endif

Antena *criarAntena(char freq, int x, int y);

Antena *carregarAntenas(char *nomeFicheiro);

Antena *inserirAntena(Antena *h, Antena *nova);

Antena *removerAntena(Antena *lista, int x, int y, bool *res);

bool imprimirAntenas(Antena *lista);

bool gravarAntenasBinario(char *nomeFicheiro, Antena *h);

RedeAntenas *criarEfeitoNefasto(int x, int y);

RedeAntenas *inserirEfeitoNefasto(RedeAntenas *h, RedeAntenas *novo);

RedeAntenas *calcularEfeitosNefastos(Antena *h);

bool imprimirEfeitosNefastos(RedeAntenas *h);

bool imprimirAntenasNefastos(const char *nomeFicheiro, RedeAntenas *h);