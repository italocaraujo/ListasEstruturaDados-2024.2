#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

// Estrutura para representar uma m�sica
typedef struct Musica {
    char nomeArtista[50];
    char nomeMusica[50];
    char duracao[10];
    char nomeAlbum[50];
    int streamingsMensais;
    char dataLancamento[15];
    char planoPremium;
    double precoPremium;
    struct Musica* proxima; // Ponteiro para a pr�xima m�sica
} Musica;

// Estrutura para representar a lista simplesmente ligada
typedef struct ListaMusicas {
    Musica* cabeca; // Ponteiro para o primeiro elemento da lista
    int tamanho;    // Quantidade de elementos na lista
} ListaMusicas;

// Fun��o para criar uma lista vazia
ListaMusicas* criarLista() {
    ListaMusicas* lista = (ListaMusicas*)malloc(sizeof(ListaMusicas));
    lista->cabeca = NULL;
    lista->tamanho = 0;
    return lista;
}

// Fun��o para criar uma nova m�sica
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
    return nova;
}

// Fun��o para inserir uma m�sica no final da lista
void inserirElemento(ListaMusicas* lista, Musica* novaMusica) {
    if (lista->cabeca == NULL) {
        lista->cabeca = novaMusica;
    } else {
        Musica* atual = lista->cabeca;
        while (atual->proxima != NULL) {
            atual = atual->proxima;
        }
        atual->proxima = novaMusica;
    }
    lista->tamanho++;
}

// Fun��o para inserir uma m�sica no in�cio da lista
void inserirElementoInicio(ListaMusicas* lista, Musica* novaMusica) {
    novaMusica->proxima = lista->cabeca;
    lista->cabeca = novaMusica;
    lista->tamanho++;
}

// Fun��o para inserir uma m�sica em uma posi��o espec�fica
void inserirElementoID(ListaMusicas* lista, Musica* novaMusica, int posicao) {
    if (posicao < 0 || posicao > lista->tamanho) {
        printf("Posi��o inv�lida.\n");
        return;
    }

    if (posicao == 0) {
        inserirElementoInicio(lista, novaMusica);
        return;
    }

    Musica* atual = lista->cabeca;
    for (int i = 0; i < posicao - 1; i++) {
        atual = atual->proxima;
    }
    novaMusica->proxima = atual->proxima;
    atual->proxima = novaMusica;
    lista->tamanho++;
}

// Fun��o para listar todas as m�sicas
void listarElementos(ListaMusicas* lista) {
    Musica* atual = lista->cabeca;
    while (atual != NULL) {
        printf("Artista: %s\n", atual->nomeArtista);
        printf("M�sica: %s\n", atual->nomeMusica);
        printf("Dura��o: %s\n", atual->duracao);
        printf("�lbum: %s\n", atual->nomeAlbum);
        printf("Streamings Mensais: %d\n", atual->streamingsMensais);
        printf("Data de Lan�amento: %s\n", atual->dataLancamento);
        printf("Plano Premium: %c\n", atual->planoPremium);
        printf("Pre�o Plano Premium: %.2f\n", atual->precoPremium);
        printf("---------------------------\n");
        atual = atual->proxima;
    }
}

// Fun��o para remover uma m�sica pela posi��o
void removerElemento(ListaMusicas* lista, int posicao) {
    if (posicao < 0 || posicao >= lista->tamanho) {
        printf("Posi��o inv�lida.\n");
        return;
    }

    Musica* atual = lista->cabeca;
    if (posicao == 0) {
        lista->cabeca = atual->proxima;
        free(atual);
    } else {
        Musica* anterior = NULL;
        for (int i = 0; i < posicao; i++) {
            anterior = atual;
            atual = atual->proxima;
        }
        anterior->proxima = atual->proxima;
        free(atual);
    }
    lista->tamanho--;
}

// Fun��o para buscar uma m�sica pelo nome
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

// Fun��o para atualizar uma m�sica em uma posi��o espec�fica
void atualizar(ListaMusicas* lista, int posicao, Musica* novaMusica) {
    if (posicao < 0 || posicao >= lista->tamanho) {
        printf("Posi��o inv�lida.\n");
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

// Fun��o para liberar toda a mem�ria da lista
void excluirLista(ListaMusicas* lista) {
    Musica* atual = lista->cabeca;
    while (atual != NULL) {
        Musica* proxima = atual->proxima;
        free(atual);
        atual = proxima;
    }
    free(lista);
}

// Fun��o principal
int main() {
    setlocale(LC_ALL, "Portuguese");

    ListaMusicas* lista = criarLista();

    Musica* musica1 = criarMusica("Frank Ocean", "Ivy", "4:09", "Blonde", 1000000, "20/08/2016", 's', 9.99);
    inserirElemento(lista, musica1);

    listarElementos(lista);

    excluirLista(lista);
    return 0;
}