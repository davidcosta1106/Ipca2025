/**
 * @file struct.h
 * @brief Definições das estruturas de dados para antenas, tipos de antenas, adjacências, filas e caminhos em grafos.
 * @author David Costa (a24609@alunos.ipca.pt)
 */
#ifndef STRUCT_H
#define STRUCT_H



/**
 * @brief Estrutura que representa uma antena.
 * 
 * Contém a frequência, coordenadas (x,y), um ponteiro para a próxima antena na lista
 * e uma lista de adjacentes.
 */
typedef struct Antena {
    char frequencia;
    int x, y;
    struct Antena *proximo;
    struct Adjacente *adjacentes;
} Antena;

/**
 * @brief Estrutura que representa um tipo de antena.
 * 
 * Cada tipo contém um identificador (char) e uma lista ligada de antenas desse tipo.
 */
typedef struct TipoAntena {
    char tipo;                 // Exemplo: 'A', 'B', etc.
    Antena *listaAntenas;      // Lista ligada das antenas deste tipo
    struct TipoAntena *proximo;
} TipoAntena;

/**
 * @brief Estrutura para armazenar as coordenadas das antenas visitadas durante a DFS.
 * 
 * Usada para armazenar o resultado da busca em profundidade.
 */
typedef struct ResultadoDFS {
    int x;
    int y;
    struct Antena *antena; 
    struct ResultadoDFS *proximo;
} ResultadoDFS;

/**
 * @brief Estrutura para representar um nó da fila usada na BFS.
 * 
 * Contém um ponteiro para a antena e para o próximo nó na fila.
 */
typedef struct NoFila {
    Antena *antena;
    struct NoFila *proximo;
} NoFila;

/**
 * @brief Estrutura para representar a fila usada na BFS.
 * 
 * Contém ponteiros para o início e fim da fila.
 */
typedef struct {
    NoFila *inicio;
    NoFila *fim;
} Fila;

/**
 * @brief Estrutura para representar um caminho (sequência de coordenadas) entre antenas.
 */
typedef struct Caminho {
    int x;
    int y;
    struct Caminho *proximo;
} Caminho;

/**
 * @brief Lista ligada que contém múltiplos caminhos possíveis entre antenas.
 */
typedef struct ListaCaminhos {
    Caminho *caminho;
    struct ListaCaminhos *proximo;
} ListaCaminhos;

#endif // STRUCT_H


#ifndef ADJACENTE_STRUCT
#define ADJACENTE_STRUCT

/**
 * @brief Estrutura para representar um nó adjacente (antena vizinha).
 * 
 * Contém as coordenadas da antena adjacente e um ponteiro para o próximo adjacente.
 */
typedef struct Adjacente {
    int x, y;
    struct Adjacente *proximo;
} Adjacente;

#endif // ADJACENTE_STRUCT
