/***
 * @file main.c
 * @brief Programa principal para o problema das antenas
 * @author David Costa
 */
#include <stdio.h>
#include <stdlib.h>
#include "funcoes.c"

int main() {
    Antena* listaAntenas = NULL; // Inicializa a lista de antenas

    /***
     * @brief Função para carregar as antenas do ficheiro
     */
    printf("Carregando antenas do ficheiro...\n");
    carregarAntenasDoFicheiro(&listaAntenas, "antenas.txt");

    /***
     * @brief Função para listar as antenas da lista
     */
    listarAntenas(listaAntenas);

    adicionarAntena(&listaAntenas, 'C', 6, 2); // Adiciona uma nova antena
    adicionarAntena(&listaAntenas, 'C', 7, 3); // Adiciona outra antena

    listarAntenas(listaAntenas); // Lista as antenas novamente

    /***
     * @brief Função para listar os efeitos nefastos das antenas
     */
    listarEfeitosNefastos(listaAntenas);

    listarMatriz(listaAntenas);

    /***
     * @brief Função para liberar a memória alocada para a lista de antenas
     */
    liberarLista(listaAntenas);

    return 0;
}
