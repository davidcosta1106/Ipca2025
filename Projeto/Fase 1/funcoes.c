/***
 * @file funcoes.c
 * @brief Implementação das funções para manipulação de antenas
 * @author David Costa
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "struct.h"

Antena *criarAntena(char freq, int x, int y)
{
    Antena *nova = (Antena *)malloc(sizeof(Antena));
    if (!nova)
    {
        printf("Erro de alocacao de memoria!\n");
        exit(1);
    }
    nova->freq = freq;
    nova->x = x;
    nova->y = y;
    nova->prox = NULL; // Inicializa o ponteiro para NULL
    return nova;
}

Antena* carregarAntenas(char* nomeFicheiro) {
    char c;
    Antena* h = NULL;
    Antena* aux;

    int x = 0;
    int y = 0;

    //Abre o ficheiro em modo de leitura
    FILE *f = fopen(nomeFicheiro, "r");

    //Verifica se não conseguiu abrir
    if (f == NULL) {
        return NULL;
    }

    //Percorre cada caractere até ao final do ficheiro
    while ((c = fgetc(f))!=EOF) {
            //Se o caractere for uma letra, cria uma antena nova
            if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) {
                aux = (Antena*)malloc(sizeof(Antena));
                if (aux == NULL) {
                    fclose(f);
                    return NULL;    //Se o ficheiro não alocar espaço devolve NULL depois de fechar o ficheiro
                }

                aux->freq = c;
                aux->x = x;
                aux->y = y;
                aux->prox = h;
                h = aux;
            }

            //Se encontrar uma mudança de linha, incrementa 1 linha e volta a coluna ao 0
            if (c == '\n') {
                x++;
                y=0;
            } else {
                y++;
            }
        }  
    fclose(f);
    return h;   //Devolve a lista completa depois de fechar o ficheiro
}

Antena *inserirAntena(Antena *h, Antena *nova)
{
    // Se a lista estiver vazia ou se a nova antena for menor que a primeira
    if (h == NULL || (nova->x < h->x || (nova->x == h->x && nova->y < h->y)))
    {
        nova->prox = h;
        return nova; // Retorna a nova antena como o novo início da lista
    }

    Antena *atual = h;
    // Percorre a lista até encontrar a posição correta para inserir
    while (atual->prox != NULL && (atual->prox->x < nova->x || (atual->prox->x == nova->x && atual->prox->y < nova->y)))
    {
        atual = atual->prox;
    }

    // Insere a nova antena na posição correta
    nova->prox = atual->prox;
    atual->prox = nova;

    return h; // Retorna o início da lista
}

Antena *removerAntena(Antena *h, int x, int y, bool *res)
{
    Antena *atual = h, *anterior = NULL;

    // Percorre a lista para encontrar a antena a remover
    while (atual != NULL && (atual->x != x || atual->y != y))
    {
        anterior = atual;
        atual = atual->prox;
    }

    // Se a antena não foi encontrada, retorna a lista original
    if (atual == NULL)
    {
        *res = false; // Define o resultado como falso
        return h;
    }

    // Se for o primeiro elemento da lista
    if (anterior == NULL)
    {
        *res = true;     // Define o resultado como verdadeiro
        h = atual->prox; // Atualiza o início da lista
    }
    else
    {
        *res = true;                  // Define o resultado como verdadeiro
        anterior->prox = atual->prox; // Remove a antena da lista
    }

    free(atual); // Libera a memória da antena removida

    return h; // Retorna o início da lista atualizado
}

bool imprimirAntenas(Antena *h)
{
    if (h == NULL)
    {
        return false;
    }

    while (h != NULL)
    {
        printf("     %c     |   (%d, %d)\n", h->freq, h->x, h->y);
        h = h->prox;
    }
    return true;
}

bool gravarAntenasBinario(char *nomeFicheiro, Antena *h)
{
    FILE *f = fopen(nomeFicheiro, "wb");
    if (!f)
    {
        return false;
    }

    while (h != NULL)
    {
        fwrite(&h->freq, sizeof(char), 1, f);
        fwrite(&h->x, sizeof(int), 1, f);
        fwrite(&h->y, sizeof(int), 1, f);
        h = h->prox;
    }

    fclose(f);
    return true;
}

RedeAntenas *criarEfeitoNefasto(int x, int y)
{
    RedeAntenas *novo = (RedeAntenas *)malloc(sizeof(RedeAntenas));
    if (!novo)
    {
        exit(1);
    }
    novo->x = x;
    novo->y = y;
    novo->prox = NULL; // Inicializa o ponteiro para NULL
    return novo;
}

RedeAntenas *inserirEfeitoNefasto(RedeAntenas *h, RedeAntenas *novo)
{
    // Se a lista estiver vazia ou se o novo efeito for menor que o primeiro
    if (h == NULL || (novo->x < h->x || (novo->x == h->x && novo->y < h->y)))
    {
        novo->prox = h;
        return novo; // Retorna o novo efeito como o início da lista
    }

    RedeAntenas *atual = h;
    // Percorre a lista até encontrar a posição correta para inserir
    while (atual->prox != NULL && (atual->prox->x < novo->x || (atual->prox->x == novo->x && atual->prox->y < novo->y)))
    {
        atual = atual->prox;
    }

    // Insere o novo efeito na posição correta
    novo->prox = atual->prox;
    atual->prox = novo;

    return h;
}

RedeAntenas *calcularEfeitosNefastos(Antena *h)
{
    RedeAntenas *efeitos = NULL;
    Antena *a1, *a2;

    // Percorre todas as antenas
    for (a1 = h; a1 != NULL; a1 = a1->prox)
    {
        for (a2 = h; a2 != NULL; a2 = a2->prox)
        {
            if (a1 != a2 && a1->freq == a2->freq)
            {
                int dx = a2->x - a1->x;
                int dy = a2->y - a1->y;

                // Só há efeito se não estiverem na mesma posição
                if (dx != 0 || dy != 0)
                {
                    // Calcula as duas posições com efeito nefasto
                    int x1 = a1->x - dx;
                    int y1 = a1->y - dy;
                    int x2 = a2->x + dx;
                    int y2 = a2->y + dy;

                    // Adiciona os pontos sem restrição de matriz
                    efeitos = inserirEfeitoNefasto(efeitos, criarEfeitoNefasto(x1, y1));
                    efeitos = inserirEfeitoNefasto(efeitos, criarEfeitoNefasto(x2, y2));
                }
            }
        }
    }

    return efeitos;
}

bool imprimirEfeitosNefastos(RedeAntenas *h)
{
    if (h == NULL)
    {
        return false;
    }

    while (h != NULL)
    {
        printf("     (%d, %d)\n", h->y, h->x);
        h = h->prox;
    }
    return true;
}

bool imprimirAntenasNefastos(const char *nomeFicheiro, RedeAntenas *h)
{
    FILE *f = fopen(nomeFicheiro, "r");
    if (!f)
    {
        return false;
    }

    char c;
    int y = 0, x = 0; // Coordenadas
    RedeAntenas *aux;

    while ((c = fgetc(f)) != EOF)
    {
        if (c == '\n')
        {
            printf("\n");
            y++;
            x = 0;
        }
        else
        {
            // Verifica se a posição atual tem efeito nefasto
            int ehNefasto = 0;
            aux = h;
            while (aux != NULL)
            {
                if (aux->x == x && aux->y == y)
                {
                    ehNefasto = 1;
                    break;
                }
                aux = aux->prox;
            }

            if (ehNefasto)
            {
                printf("#"); // Substitui por '#' se for nefasto
            }
            else
            {
                printf("%c", c); // Caso contrário, imprime o original
            }

            x++;
        }
    }

    fclose(f);

    return true;
}

/*

bool posicaoNefasta(Antena *lista, char freq, int x, int y)
{
    Antena *a1, *a2;

    for (a1 = lista; a1 != NULL; a1 = a1->prox)
    {
        if (a1->frequencia == freq)
        {
            for (a2 = lista; a2 != NULL; a2 = a2->prox)
            {
                // Garante que a1 e a2 não sejam a mesma antena e que ambas tenham a mesma frequência
                if (a2 != a1 && a2->frequencia == freq)
                {
                    int dx = a2->x - a1->x;
                    int dy = a2->y - a1->y;


                    // Verifica se a posição (x, y) está alinhada de forma a formar um efeito nefasto
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


bool verificaInterferencia(Antena *lista, char freq, int x, int y)
{
    Antena *a1, *a2;

    for (a1 = lista; a1 != NULL; a1 = a1->prox)
    {
        if (a1->frequencia == freq)
        {
             // Percorre novamente a lista para encontrar outra antena com a mesma frequência
            for (a2 = lista; a2 != NULL; a2 = a2->prox)
            {
                // Garante que a1 e a2 não sejam a mesma antena e que ambas tenham a mesma frequência
                if (a2 != a1 && a2->frequencia == freq)
                {
                     // Diferença nas coordenadas
                    int dx = a2->x - a1->x;
                    int dy = a2->y - a1->y;

                    // Verifica linha
                    if (a1->y == a2->y && a1->y == y)
                    {
                        if (x == a1->x - dx * 2 || x == a2->x + dx * 2)
                        {
                            return true;
                        }
                    }

                    // Verifica coluna
                    if (a1->x == a2->x && a1->x == x)
                    {
                        if (y == a1->y - dy * 2 || y == a2->y + dy * 2)
                        {
                            return true;
                        }
                    }

                    // Verifica diagonal
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
        matriz[aux->y - 1][aux->x - 1] = aux->frequencia;

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

                if (dx != 0 || dy != 0)// Garante que não está verificando a mesma antena
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

void adicionarAntena(Antena **lista, char freq, int x, int y)
{
    // Verifica se está dentro dos limites da matriz
    if (x < 0 || x >= TAMANHO_MATRIZ || y < 0 || y >= TAMANHO_MATRIZ)
    {
        printf("Erro: A posicao (%d, %d) esta fora dos limites da matriz!\n", y, x);
        return;
    }

    // Verifica se a posição tem efeito nefasto
    if (posicaoNefasta(*lista, freq, x, y)) // <- Corrigido para passar (x, y) corretamente
    {
        printf("Erro: A posicao (%d, %d) tem efeito nefasto e nao pode ser usada!\n", y, x);
        return;
    }

    // Verifica interferência com outras antenas
    if (verificaInterferencia(*lista, freq, x, y)) // <- Corrigido para manter (x, y)
    {
        printf("Erro: A antena na posicao (%d, %d) com frequencia %c causaria interferencia!\n", y, x, freq);
        return;
    }

    Antena *nova = criarAntena(freq, x, y); // <- Alterado para criar antena com (x, y) correto
    nova->prox = *lista;
    *lista = nova;

    printf("Antena adicionada na posicao (%d, %d) com frequencia %c.\n", y, x, freq);
}

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

void listarAntenas(Antena *lista)
{
    printf("Lista de Antenas:\n");
    while (lista)
    {
        printf("Frequencia: %c - Posicao: (%d, %d)\n", lista->frequencia, lista->y, lista->x);
        lista = lista->prox;
    }
}

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

void listarEfeitosNefastos(Antena *lista)
{
    // Exibe as localizações onde ocorre efeito nefasto devido à interferência entre antenas
    printf("Localizacoes com efeito nefasto:\n");

    // Declaração de ponteiros para percorrer a lista de antenas
    Antena *a1, *a2;

    // Matriz booleana para marcar posições que já foram impressas, evitando duplicatas
    bool matrizMarcada[TAMANHO_MATRIZ][TAMANHO_MATRIZ] = {false};

    // Percorre todas as antenas na lista
    for (a1 = lista; a1 != NULL; a1 = a1->prox)
    {
        // Compara cada antena com todas as outras
        for (a2 = lista; a2 != NULL; a2 = a2->prox)
        {
            // Verifica se são antenas diferentes e operam na mesma frequência
            if (a1 != a2 && a1->frequencia == a2->frequencia)
            {
                // Calcula a diferença de coordenadas entre as duas antenas
                int dx = a2->x - a1->x;
                int dy = a2->y - a1->y;

                // Se as antenas não estão na mesma posição
                if (dx != 0 || dy != 0)
                {
                    // Calcula posições afetadas pelo efeito nefasto
                    int x1 = a1->x - dx; // Ponto na direção oposta a a2
                    int y1 = a1->y - dy;
                    int x2 = a2->x + dx; // Ponto na mesma direção de a2
                    int y2 = a2->y + dy;

                    // Verifica se a posição (x1, y1) está dentro da matriz e ainda não foi marcada
                    if (x1 >= 0 && x1 < TAMANHO_MATRIZ && y1 >= 0 && y1 < TAMANHO_MATRIZ && !matrizMarcada[y1][x1])
                    {
                        printf("Efeito nefasto em (%d, %d)\n", y1, x1);
                        matrizMarcada[y1][x1] = true; // Marca para evitar duplicação
                    }

                    // Verifica se a posição (x2, y2) está dentro da matriz e ainda não foi marcada
                    if (x2 >= 0 && x2 < TAMANHO_MATRIZ && y2 >= 0 && y2 < TAMANHO_MATRIZ && !matrizMarcada[y2][x2])
                    {
                        printf("Efeito nefasto em (%d, %d)\n", y2, x2);
                        matrizMarcada[y2][x2] = true; // Marca para evitar duplicação
                    }
                }
            }
        }
    }
}

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
                adicionarAntena(lista, linha[x], x + 1, y + 1);
            }
        }
        y++; // Avança para a próxima linha
    }

    fclose(f);
    printf("Carregamento do ficheiro concluído.\n");
}


*/