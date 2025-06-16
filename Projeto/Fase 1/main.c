/**
 * @file main.c
 * @author (...)
 * @version 0.2
 * @date 2025-05-26
 * 
 * @brief Programa principal para gestão de antenas.
 */

#include <stdio.h>
#include "struct.h"
#include "funcoes.c"

int main() {
    Antena* lista = NULL;
    RedeAntenas* listaNefastos = NULL;
    bool removida;

    // Inserção manual de antenas
    lista = inserirAntena(lista, criarAntena('A', 3, 2));
    lista = inserirAntena(lista, criarAntena('B', 4, 2));
    lista = inserirAntena(lista, criarAntena('C', 1, 2));

    printf("Lista de Antenas (depois de inserção):\n");
    printf("| Frequência | Linha | Coluna |\n");
    printf("|------------|-------|--------|\n");
    imprimirAntenas(lista);
    printf("\n");

    // Remoção de uma antena
    lista = removerAntena(lista, 3, 2, &removida);
    if (removida) {
        printf("Antena removida com sucesso.\n");
    } else {
        printf("Antena não encontrada para remoção.\n");
    }

    printf("Lista de Antenas (depois da remoção):\n");
    imprimirAntenas(lista);
    printf("\n");

    // Carregar antenas de um ficheiro
    lista = carregarAntenas("antenas.txt");
    if (lista == NULL) {
        printf("Erro ao carregar antenas do ficheiro.\n");
        return 1;
    }

    printf("Antenas carregadas do ficheiro:\n");
    imprimirAntenas(lista);
    printf("\n");

    // Detetar efeitos nefastos
    listaNefastos = calcularEfeitosNefastos(lista);

    if (listaNefastos != NULL) {
        printf("Posições com efeitos nefastos:\n");
        printf("| Linha | Coluna |\n");
        printf("|-------|--------|\n");
        imprimirEfeitosNefastos(listaNefastos);
    } else {
        printf("Não há efeitos nefastos detetados.\n");
    }
    printf("\n");

    // Gerar ficheiro com o mapa atualizado
    if (imprimirAntenasNefastos("antenas.txt", listaNefastos)) {
        printf("\nMapa atualizado com efeitos nefastos criado com sucesso.\n");
    } else {
        printf("Falha ao criar o mapa atualizado com efeitos nefastos.\n");
    }

    return 0;
}
