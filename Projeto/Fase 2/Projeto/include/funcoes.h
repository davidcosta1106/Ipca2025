

/**
 * @file funcoes.h
 * @brief Declarações das funções para manipulação de antenas, tipos de antenas e algoritmos de grafos.
 * @author David Costa (a24609@alunos.ipca.pt)
 *  
 * Este ficheiro contém as declarações das funções usadas para criar, inserir, interligar antenas e tipos,
 * bem como funções para buscas em grafos (DFS, BFS) e verificações relacionadas à interferência e efeitos nefastos.
 */

/*

#ifndef FUNCOES_H
#define FUNCOES_H

#include "struct.h"
#include <stdbool.h>

/// @name Criação e inserção de antenas
///@{
Antena* CriarAntena(char frequencia, int x, int y);
Antena* InserirAntena(Antena* lista, Antena* novaAntena);
///@}

/// @name Adjacências
///@{
Adjacente* CriarAdjacente(int x, int y);
bool InserirAdjacente(Adjacente* lista, Adjacente* novo);
bool AdicionarAdjacenteAntena(Antena* antena, int x, int y);
///@}

/// @name Interligação de antenas
///@{
Antena* InterligarTodasAntenasMesmoTipo(Antena* lista);
bool interligarAntenasTipo(TipoAntena* listaTipos);
///@}

/// @name Manipulação de tipos de antenas
///@{
TipoAntena* CriarTipoAntena(char tipo);
TipoAntena* InserirTipoAntena(TipoAntena* lista, TipoAntena* novo);
TipoAntena* ProcurarTipo(TipoAntena* lista, char tipo);
TipoAntena* AdicionarAntenaTipo(TipoAntena* listaTipos, char tipo, Antena* novaAntena);
///@}

/// @name Algoritmos de grafos
///@{
bool DFS(Antena* antena, bool* visitado);
bool BFS(Antena* antena);
bool ExisteCaminhoEntreAntenas(Antena* origem, Antena* destino);
bool CaminhoDFS(Antena* atual, Antena* destino, bool* visitado, bool* caminhoEncontrado);
///@}

/// @name Verificações
///@{
bool AntenaExiste(Antena* lista, int x, int y);
bool VerificarInterferencia(Antena* novaAntena, Antena* lista);
bool VerificarEfeitosNefastos(Antena* novaAntena, Antena* lista);
///@}

#endif // FUNCOES_H

*/



#ifndef FUNCOES_H
#define FUNCOES_H

#include "struct.h"
#include <stdbool.h>

Antena* CriarAntena(char frequencia, int x, int y);
Antena* InserirAntena(Antena* lista, Antena* novaAntena);

Adjacente* CriarAdjacente(int x, int y);
bool InserirAdjacente(Adjacente* lista, Adjacente* novo);
bool AdicionarAdjacenteAntena(Antena* antena, int x, int y);

TipoAntena* CriarTipoAntena(char tipo);
TipoAntena* AdicionarTipoAntena(TipoAntena* lista, char tipo);
TipoAntena* InserirAntenaEmTipo(TipoAntena* listaTipos, char tipo, Antena* novaAntena);
TipoAntena* ProcurarTipo(TipoAntena* lista, char tipo);

bool InterligarAntenasMesmoTipo(TipoAntena* listaTipos);

Antena* ProcurarAntenaPorCoordenadas(TipoAntena* listaTipos, int x, int y);

ResultadoDFS* BuscaEmProfundidade(Antena* inicio, TipoAntena* listaTipos, int maxLin, int maxCol);
ResultadoDFS* BuscaEmLargura(Antena* inicio, TipoAntena* listaTipos, int maxLin, int maxCol);

#endif
