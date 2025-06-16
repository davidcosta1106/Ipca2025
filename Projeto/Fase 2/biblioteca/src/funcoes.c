/**
 * @file funcoes.c
 * @author David Costa
 * @brief Implementação das funções para manipulação de antenas, tipos de antenas e algoritmos de grafos.
 */

#include "struct.h"
#include "funcoes.h"
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_LINHA 20

/**
 * @brief Cria um novo nodo adjacente.
 * 
 * @param x Coordenada X da antena adjacente.
 * @param y Coordenada Y da antena adjacente.
 * @return Adjacente* Ponteiro para o nodo criado, ou NULL em caso de erro.
 */
Adjacente *CriarAdjacente(int x, int y) {
    Adjacente *novo = (Adjacente *)malloc(sizeof(Adjacente));
    if (!novo)
        return NULL;

    novo->x = x;
    novo->y = y;
    novo->proximo = NULL;
    return novo;
}

/**
 * @brief Procura um tipo de antena numa lista pelo seu identificador.
 * 
 * @param lista Lista de tipos de antenas.
 * @param tipo Caracter identificador do tipo de antena.
 * @return TipoAntena* Ponteiro para o tipo encontrado, ou NULL se não encontrado.
 */
TipoAntena *ProcurarTipo(TipoAntena *lista, char tipo);

#pragma region Vertices

#pragma region Criar

/**
 * @brief Cria uma nova antena com os parâmetros dados.
 * 
 * @param frequencia Frequência da antena.
 * @param x Coordenada X da antena.
 * @param y Coordenada Y da antena.
 * @return Antena* Ponteiro para a antena criada, ou NULL em caso de erro.
 */
Antena *CriarAntena(char frequencia, int x, int y)
{
    Antena *aux = (Antena *)malloc(sizeof(Antena));
    if (!aux)
        return NULL;

    aux->frequencia = frequencia;
    aux->x = x;
    aux->y = y;
    aux->proximo = NULL;
    aux->adjacentes = NULL;

    return aux;
}

/**
 * @brief Cria um novo tipo de antena.
 * 
 * @param tipo Caracter que identifica o tipo.
 * @return TipoAntena* Ponteiro para o novo tipo criado, ou NULL em caso de erro.
 */
TipoAntena *CriarTipoAntena(char tipo) {
    TipoAntena *novo = (TipoAntena *)malloc(sizeof(TipoAntena));
    if (!novo) return NULL;

    novo->tipo = tipo;
    novo->listaAntenas = NULL;
    novo->proximo = NULL;
    return novo;
}

#pragma endregion

#pragma region Inserir

/**
 * @brief Insere uma antena no final da lista ligada de antenas.
 * 
 * @param lista Lista de antenas.
 * @param aux Antena a inserir.
 * @return Antena* Ponteiro para a lista atualizada.
 */
Antena* InserirAntena(Antena *lista, Antena *aux)// meter em bool para conseguir depois mandar e resultado se e veradeiro ou falso
{
    if (aux == NULL)
        return lista;

    if (lista == NULL) {
        return aux;
    }
    else {
        Antena *atual = lista;
        while (atual->proximo != NULL)
        {
            atual = atual->proximo;
        }
        atual->proximo = aux;
    }
    return lista;
}

/**
 * @brief Insere uma antena numa lista do seu tipo correspondente.
 * 
 * @param listaTipos Lista de tipos de antenas.
 * @param tipo Tipo da antena a inserir.
 * @param novaAntena Ponteiro para a antena a inserir.
 * @return TipoAntena* Ponteiro para a lista atualizada de tipos.
 */
TipoAntena *InserirAntenaEmTipo(TipoAntena *listaTipos, char tipo, Antena *novaAntena) {
    TipoAntena *tipoEncontrado = ProcurarTipo(listaTipos, tipo);
    if (!tipoEncontrado) return listaTipos;

    tipoEncontrado->listaAntenas = InserirAntena(tipoEncontrado->listaAntenas, novaAntena);
    return listaTipos;
}

#pragma endregion

#pragma region Adicionar

/**
 * @brief Adiciona um nodo adjacente a uma antena.
 * 
 * @param antena Ponteiro para a antena a modificar.
 * @param x Coordenada X do adjacente.
 * @param y Coordenada Y do adjacente.
 * @return true Se a operação foi bem-sucedida.
 * @return false Se ocorreu erro (ponteiro NULL ou malloc falhou).
 */
bool AdicionarAdjacenteAntena(Antena *antena, int x, int y)
{
    if (!antena)
        return false;

    Adjacente *novo = CriarAdjacente(x, y);
    if (!novo)
        return false;

    if (antena->adjacentes == NULL)
    {
        antena->adjacentes = novo;
    }
    else
    {
        Adjacente *atual = antena->adjacentes;
        while (atual->proximo != NULL)
        {
            atual = atual->proximo;
        }
        atual->proximo = novo;
    }

    return true;
}

/**
 * @brief Adiciona um novo tipo de antena na lista de tipos (se não existir).
 * 
 * @param lista Lista de tipos de antenas.
 * @param tipo Tipo a adicionar.
 * @return TipoAntena* Ponteiro para a lista atualizada.
 */
TipoAntena *AdicionarTipoAntena(TipoAntena *lista, char tipo) {
    TipoAntena *existe = lista;
    while (existe) {
        if (existe->tipo == tipo)
            return lista;
        existe = existe->proximo;
    }

    TipoAntena *novo = CriarTipoAntena(tipo);
    if (!novo) return lista;

    novo->proximo = lista;
    return novo;
}

/**
 * @brief Adiciona um nodo de resultado na lista de resultados da DFS.
 * 
 * @param lista Lista atual de resultados.
 * @param x Coordenada X da antena visitada.
 * @param y Coordenada Y da antena visitada.
 * @param antenaAtual Ponteiro para a antena visitada.
 * @return ResultadoDFS* Ponteiro para a lista atualizada.
 */
ResultadoDFS *AdicionarResultado(ResultadoDFS *lista, int x, int y, Antena *antenaAtual) {
    ResultadoDFS *novo = (ResultadoDFS *)malloc(sizeof(ResultadoDFS));
    if (!novo) return lista;

    novo->x = x;
    novo->y = y;
    novo->antena = antenaAtual;
    novo->proximo = NULL;

    if (!lista) return novo;

    ResultadoDFS *atual = lista;
    while (atual->proximo)
        atual = atual->proximo;
    atual->proximo = novo;
    return lista;
}

#pragma endregion

#pragma region Interligar

/**
 * @brief Interliga antenas do mesmo tipo que têm a mesma frequência.
 * 
 * @param listaTipos Lista de tipos de antenas.
 * @return true Se operação concluída.
 * @return false Se listaTipos for NULL.
 */
bool InterligarAntenasMesmoTipo(TipoAntena *listaTipos) {
    if (!listaTipos) return false;

    TipoAntena *atualTipo = listaTipos;
    while (atualTipo != NULL) {
        Antena *a1 = atualTipo->listaAntenas;
        while (a1 != NULL) {
            Antena *a2 = atualTipo->listaAntenas;
            while (a2 != NULL) {
                if (a1 != a2 && a1->frequencia == a2->frequencia) {
                    AdicionarAdjacenteAntena(a1, a2->x, a2->y);
                    AdicionarAdjacenteAntena(a2, a1->x, a1->y);
                }
                a2 = a2->proximo;
            }
            a1 = a1->proximo;
        }
        atualTipo = atualTipo->proximo;
    }

    return true;
}

#pragma endregion

#pragma region Funções de procura

/**
 * @brief Procura um tipo de antena numa lista pelo seu caracter identificador.
 * 
 * @param lista Lista de tipos de antenas.
 * @param tipo Caracter identificador.
 * @return TipoAntena* Ponteiro para o tipo encontrado ou NULL.
 */
TipoAntena *ProcurarTipo(TipoAntena *lista, char tipo) {
    while (lista) {
        if (lista->tipo == tipo)
            return lista;
        lista = lista->proximo;
    }
    return NULL;
}

/**
 * @brief Procura uma antena nas listas de tipos por suas coordenadas.
 * 
 * @param listaTipos Lista de tipos de antenas.
 * @param x Coordenada X da antena procurada.
 * @param y Coordenada Y da antena procurada.
 * @return Antena* Ponteiro para a antena encontrada, ou NULL se não existir.
 */
Antena *ProcurarAntenaPorCoordenadas(TipoAntena *listaTipos, int x, int y) {
    while (listaTipos) {
        Antena *a = listaTipos->listaAntenas;
        while (a) {
            if (a->x == x && a->y == y)
                return a;
            a = a->proximo;
        }
        listaTipos = listaTipos->proximo;
    }
    return NULL;
}

#pragma endregion

#pragma region Buscas

/**
 * @brief Função recursiva auxiliar para DFS.
 * 
 * @param antena Antena atual.
 * @param visitado Matriz de visitados.
 * @param max_x Tamanho máximo eixo X.
 * @param max_y Tamanho máximo eixo Y.
 * @param resultado Lista com resultado da DFS.
 * @param listaTipos Lista de tipos de antenas para procurar adjacentes.
 * @return ResultadoDFS* Lista atualizada com resultados.
 */
ResultadoDFS *DFSRecursiva(Antena *antena, bool visitado[MAX_LINHA][MAX_LINHA], int max_x, int max_y, ResultadoDFS *resultado, TipoAntena *listaTipos) {
    if (!antena) return resultado;

    int x = antena->x;
    int y = antena->y;

    if (x < 0 || x >= max_x || y < 0 || y >= max_y)
        return resultado;

    if (visitado[x][y])
        return resultado;

    visitado[x][y] = true;
    resultado = AdicionarResultado(resultado, x, y, antena);

    Adjacente *adj = antena->adjacentes;
    while (adj) {
        Antena *proximo = ProcurarAntenaPorCoordenadas(listaTipos, adj->x, adj->y);
        resultado = DFSRecursiva(proximo, visitado, max_x, max_y, resultado, listaTipos);
        adj = adj->proximo;
    }

    return resultado;
}

/**
 * @brief Realiza busca em profundidade (DFS) a partir de uma antena inicial.
 * 
 * @param listaTipos Lista de tipos de antenas.
 * @param x_inicial Coordenada X inicial.
 * @param y_inicial Coordenada Y inicial.
 * @param max_x Tamanho máximo eixo X.
 * @param max_y Tamanho máximo eixo Y.
 * @return ResultadoDFS* Lista com resultado da DFS.
 */
ResultadoDFS *BuscaEmProfundidade(TipoAntena *listaTipos, int x_inicial, int y_inicial, int max_x, int max_y) {
    bool visitado[MAX_LINHA][MAX_LINHA] = { false };

    Antena *inicio = ProcurarAntenaPorCoordenadas(listaTipos, x_inicial, y_inicial);
    if (!inicio) return NULL;

    ResultadoDFS *resultado = NULL;
    resultado = DFSRecursiva(inicio, visitado, max_x, max_y, resultado, listaTipos);
    return resultado;
}

/**
 * @brief Realiza busca em largura (BFS) a partir de uma antena inicial.
 * 
 * @param listaTipos Lista de tipos de antenas.
 * @param x_inicial Coordenada X inicial.
 * @param y_inicial Coordenada Y inicial.
 * @param max_x Tamanho máximo eixo X.
 * @param max_y Tamanho máximo eixo Y.
 * @return ResultadoDFS* Lista com resultado da BFS.
 */
ResultadoDFS *BuscaEmLargura(TipoAntena *listaTipos, int x_inicial, int y_inicial, int max_x, int max_y) {
    bool visitado[MAX_LINHA][MAX_LINHA] = { false };

    ResultadoDFS *resultado = NULL;

    Antena *inicio = ProcurarAntenaPorCoordenadas(listaTipos, x_inicial, y_inicial);
    if (!inicio) return NULL;

    Antena **fila = (Antena **)malloc(sizeof(Antena *) * (max_x * max_y));
    if (!fila) return NULL;

    int inicioFila = 0, fimFila = 0;
    fila[fimFila++] = inicio;
    visitado[inicio->x][inicio->y] = true;

    while (inicioFila < fimFila) {
        Antena *atual = fila[inicioFila++];
        resultado = AdicionarResultado(resultado, atual->x, atual->y, atual);

        Adjacente *adj = atual->adjacentes;
        while (adj) {
            if (!visitado[adj->x][adj->y]) {
                Antena *vizinho = ProcurarAntenaPorCoordenadas(listaTipos, adj->x, adj->y);
                if (vizinho) {
                    fila[fimFila++] = vizinho;
                    visitado[adj->x][adj->y] = true;
                }
            }
            adj = adj->proximo;
        }
    }

    free(fila);
    return resultado;
}

#pragma endregion

#pragma region Liberar memória

/**
 * @brief Libera toda a lista ligada de adjacentes.
 * 
 * @param lista Lista de adjacentes.
 * @return true Se a operação foi bem-sucedida.
 */
bool LiberarAdjacentes(Adjacente *lista) {
    while (lista) {
        Adjacente *temp = lista;
        lista = lista->proximo;
        free(temp);
    }
    return true;
}

/**
 * @brief Libera toda a lista ligada de antenas e seus adjacentes.
 * 
 * @param lista Lista de antenas.
 * @return true Se a operação foi bem-sucedida.
 */
bool LiberarAntenas(Antena *lista) {
    while (lista) {
        Antena *temp = lista;
        lista = lista->proximo;
        LiberarAdjacentes(temp->adjacentes);
        free(temp);
    }
    return true;
}

/**
 * @brief Libera toda a lista ligada de tipos de antenas e suas antenas.
 * 
 * @param lista Lista de tipos de antenas.
 * @return true Se a operação foi bem-sucedida.
 */
bool LiberarTiposAntenas(TipoAntena *lista) {
    while (lista) {
        TipoAntena *temp = lista;
        lista = lista->proximo;
        LiberarAntenas(temp->listaAntenas);
        free(temp);
    }
    return true;
}

/**
 * @brief Libera toda a lista ligada de resultados da DFS/BFS.
 * 
 * @param lista Lista de resultados.
 * @return true Se a operação foi bem-sucedida.
 */
bool LiberarResultados(ResultadoDFS *lista) {
    while (lista) {
        ResultadoDFS *temp = lista;
        lista = lista->proximo;
        free(temp);
    }
    return true;
}

#pragma endregion
