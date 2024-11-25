#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

// Estrutura para representar uma música
typedef struct Musica {
    char nomeArtista[50];
    char nomeMusica[50];
    char duracao[10];
    char nomeAlbum[50];
    int streamingsMensais;
    char dataLancamento[15];
    char planoPremium;
    double precoPremium;
    struct Musica* proxima; // Ponteiro para a próxima música
    struct Musica* anterior; // Ponteiro para a música anterior
} Musica;

// Estrutura para representar a lista duplamente ligada
typedef struct ListaMusicas {
    Musica* cabeca; // Ponteiro para o primeiro elemento da lista
    Musica* cauda;  // Ponteiro para o último elemento da lista
    int tamanho;    // Quantidade de elementos na lista
} ListaMusicas;

// Função para criar uma lista vazia
ListaMusicas* criarLista() {
    ListaMusicas* lista = (ListaMusicas*)malloc(sizeof(ListaMusicas));
    lista->cabeca = NULL;
    lista->cauda = NULL;
    lista->tamanho = 0;
    return lista;
}

// Função para criar uma nova música
Musica* criarMusica(const char* nomeArtista, const char* nomeMusica, const char* duracao,
                    const char* nomeAlbum, int streamingsMensais, const char* dataLancamento,
                    char planoPremium, double precoPremium) {
    Musica* nova = (Musica*)malloc(sizeof(Musica));
    strcpy(nova->nomeArtista, nomeArtista);
    strcpy(nova->nomeMusica, nomeMusica);
    strcpy(nova->duracao, duracao);
    strcpy(nova->nomeAlbum, nomeAlbum);
    nova->streamingsMensais = streamingsMensais;
    strcpy(nova->dataLancamento, dataLancamento);
    nova->planoPremium = planoPremium;
    nova->precoPremium = precoPremium;
    nova->proxima = NULL;
    nova->anterior = NULL;
    return nova;
}

// Função para inserir uma música no final da lista
void inserirElemento(ListaMusicas* lista, Musica* novaMusica) {
    if (lista->cauda == NULL) {
        lista->cabeca = novaMusica;
        lista->cauda = novaMusica;
    } else {
        lista->cauda->proxima = novaMusica;
        novaMusica->anterior = lista->cauda;
        lista->cauda = novaMusica;
    }
    lista->tamanho++;
}

// Função para inserir uma música no início da lista
void inserirElementoInicio(ListaMusicas* lista, Musica* novaMusica) {
    if (lista->cabeca == NULL) {
        lista->cabeca = novaMusica;
        lista->cauda = novaMusica;
    } else {
        novaMusica->proxima = lista->cabeca;
        lista->cabeca->anterior = novaMusica;
        lista->cabeca = novaMusica;
    }
    lista->tamanho++;
}

// Função para inserir uma música em uma posição específica
void inserirElementoID(ListaMusicas* lista, Musica* novaMusica, int posicao) {
    if (posicao < 0 || posicao > lista->tamanho) {
        printf("Posição inválida.\n");
        return;
    }

    if (posicao == 0) {
        inserirElementoInicio(lista, novaMusica);
        return;
    }

    if (posicao == lista->tamanho) {
        inserirElemento(lista, novaMusica);
        return;
    }

    Musica* atual = lista->cabeca;
    for (int i = 0; i < posicao; i++) {
        atual = atual->proxima;
    }

    novaMusica->proxima = atual;
    novaMusica->anterior = atual->anterior;
    atual->anterior->proxima = novaMusica;
    atual->anterior = novaMusica;

    lista->tamanho++;
}

// Função para listar todas as músicas
void listarElementos(ListaMusicas* lista) {
    Musica* atual = lista->cabeca;
    while (atual != NULL) {
        printf("Artista: %s\n", atual->nomeArtista);
        printf("Música: %s\n", atual->nomeMusica);
        printf("Duração: %s\n", atual->duracao);
        printf("Álbum: %s\n", atual->nomeAlbum);
        printf("Streamings Mensais: %d\n", atual->streamingsMensais);
        printf("Data de Lançamento: %s\n", atual->dataLancamento);
        printf("Plano Premium: %c\n", atual->planoPremium);
        printf("Preço Plano Premium: %.2f\n", atual->precoPremium);
        printf("---------------------------\n");
        atual = atual->proxima;
    }
}

// Função para listar todas as músicas na ordem inversa
void listarElementosOrdemInversa(ListaMusicas* lista) {
    Musica* atual = lista->cauda;
    while (atual != NULL) {
        printf("Artista: %s\n", atual->nomeArtista);
        printf("Música: %s\n", atual->nomeMusica);
        printf("Duração: %s\n", atual->duracao);
        printf("Álbum: %s\n", atual->nomeAlbum);
        printf("Streamings Mensais: %d\n", atual->streamingsMensais);
        printf("Data de Lançamento: %s\n", atual->dataLancamento);
        printf("Plano Premium: %c\n", atual->planoPremium);
        printf("Preço Plano Premium: %.2f\n", atual->precoPremium);
        printf("---------------------------\n");
        atual = atual->anterior;
    }
}

// Função para remover uma música pela posição
void removerElemento(ListaMusicas* lista, int posicao) {
    if (posicao < 0 || posicao >= lista->tamanho) {
        printf("Posição inválida.\n");
        return;
    }

    Musica* atual = lista->cabeca;
    for (int i = 0; i < posicao; i++) {
        atual = atual->proxima;
    }

    if (atual->anterior != NULL) {
        atual->anterior->proxima = atual->proxima;
    } else {
        lista->cabeca = atual->proxima;
    }

    if (atual->proxima != NULL) {
        atual->proxima->anterior = atual->anterior;
    } else {
        lista->cauda = atual->anterior;
    }

    free(atual);
    lista->tamanho--;
}

// Função para buscar uma música pelo nome
Musica* buscarElemento(ListaMusicas* lista, const char* nomeMusica) {
    Musica* atual = lista->cabeca;
    while (atual != NULL) {
        if (strcmp(atual->nomeMusica, nomeMusica) == 0) {
            return atual;
        }
        atual = atual->proxima;
    }
    return NULL;
}

// Função para atualizar uma música em uma posição específica
void atualizar(ListaMusicas* lista, int posicao, Musica* novaMusica) {
    if (posicao < 0 || posicao >= lista->tamanho) {
        printf("Posição inválida.\n");
        return;
    }

    Musica* atual = lista->cabeca;
    for (int i = 0; i < posicao; i++) {
        atual = atual->proxima;
    }

    strcpy(atual->nomeArtista, novaMusica->nomeArtista);
    strcpy(atual->nomeMusica, novaMusica->nomeMusica);
    strcpy(atual->duracao, novaMusica->duracao);
    strcpy(atual->nomeAlbum, novaMusica->nomeAlbum);
    atual->streamingsMensais = novaMusica->streamingsMensais;
    strcpy(atual->dataLancamento, novaMusica->dataLancamento);
    atual->planoPremium = novaMusica->planoPremium;
    atual->precoPremium = novaMusica->precoPremium;
}

// Função para excluir toda a lista
void excluirLista(ListaMusicas* lista) {
    Musica* atual = lista->cabeca;
    while (atual != NULL) {
        Musica* proxima = atual->proxima;
        free(atual);
        atual = proxima;
    }
    free(lista);
}

// Função principal
int main() {
    setlocale(LC_ALL, "Portuguese");

    ListaMusicas* lista = criarLista();

    Musica* musica1 = criarMusica("Frank Ocean", "Ivy", "4:09", "Blonde", 1000000, "20/08/2016", 's', 9.99);
    inserirElemento(lista, musica1);

    listarElementos(lista);

    printf("Ordem inversa:\n");
    listarElementosOrdemInversa(lista);

    excluirLista(lista);
    return 0;
}
