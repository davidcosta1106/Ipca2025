/**
 * @file main.c
 * @author David Costa (a24609@alunos.ipca.pt)~
 * @brief Programa principal para testar as funções de manipulação de antenas e algoritmos de grafos.
 */
#include <stdio.h>
#include <stdlib.h>
#include "struct.h"
#include "funcoes.h"

int main() {
    TipoAntena *listaTipos = NULL;

    Antena *a1 = CriarAntena('A', 1, 1);
    Antena *a2 = CriarAntena('B', 1, 2);
    Antena *a3 = CriarAntena('A', 2, 2);

    listaTipos = AdicionarTipoAntena(listaTipos, 'A');
    listaTipos = AdicionarTipoAntena(listaTipos, 'B');

    listaTipos = InserirAntenaEmTipo(listaTipos, 'A', a1);
    listaTipos = InserirAntenaEmTipo(listaTipos, 'B', a2);
    listaTipos = InserirAntenaEmTipo(listaTipos, 'A', a3);

    InterligarAntenasMesmoTipo(listaTipos);

    printf("Resultado da DFS:\n");
    ResultadoDFS *resDFS = BuscaEmProfundidade(a1, listaTipos,10, 10);
    ResultadoDFS *tmp = resDFS;
    while (tmp) {
        printf("(%d, %d) %c\n", tmp->x, tmp->y, tmp->antena->frequencia);
        ResultadoDFS *anterior = tmp;
        tmp = tmp->proximo;
        free(anterior);
    }

    printf("\nResultado da BFS:\n");
    ResultadoDFS *resBFS = BuscaEmLargura(a1, listaTipos, 10, 10);
    ResultadoDFS *tmp = resBFS;
    while (tmp) {
        printf("(%d, %d) %c\n", tmp->x, tmp->y, tmp->antena->frequencia);
        ResultadoDFS *anterior = tmp;
        tmp = tmp->proximo;
        free(anterior);
    }

    return 0;
}
