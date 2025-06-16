typedef struct Vertice {
    char freq;                  // Frequência da antena (A-Z)
    int x, y;                   // Coordenadas
    int visitado;               // Flag para visitação
    struct Vertice* prox;       // Próximo vértice na lista de antenas
    struct Aresta* adj;         // Lista ligada de arestas (ligações)
} Vertice;

typedef struct Aresta {
    int peso;                   // Distância entre antenas
    struct Vertice* destino;    // Vértice de destino da aresta
    struct Aresta* prox;        // Próxima aresta da lista de adjacência
} Aresta;

typedef struct Grafo {
    Vertice* h;                 // Início da lista de vértices
    int numVertices;            // Número total de vértices
} Grafo;
