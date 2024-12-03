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
} Musica;

// Estrutura para representar o n� da fila
typedef struct NoFila {
    Musica musica;           // M�sica armazenada no n�
    struct NoFila* proximo;  // Ponteiro para o pr�ximo n�
} NoFila;

// Estrutura para representar a fila de m�sicas
typedef struct FilaMusicas {
    NoFila* inicio;   // Ponteiro para o in�cio da fila
    NoFila* fim;      // Ponteiro para o fim da fila
} FilaMusicas;

// Fun��o para criar uma fila vazia
FilaMusicas* criarFila() {
    FilaMusicas* fila = (FilaMusicas*)malloc(sizeof(FilaMusicas));
    fila->inicio = NULL;
    fila->fim = NULL;
    return fila;
}

// Fun��o para adicionar uma m�sica na fila (enqueue)
void enqueue(FilaMusicas* fila, Musica* novaMusica) {
    NoFila* novoNo = (NoFila*)malloc(sizeof(NoFila));
    novoNo->musica = *novaMusica;
    novoNo->proximo = NULL;  // Novo n� aponta para NULL (fim da fila)
    
    if (fila->fim == NULL) {
        fila->inicio = novoNo;  // Se a fila estava vazia, o novo n� � o in�cio
    } else {
        fila->fim->proximo = novoNo;  // Se a fila n�o estava vazia, adiciona no final
    }
    fila->fim = novoNo;  // Atualiza o ponteiro fim para o novo n�
}

// Fun��o para remover uma m�sica da fila (dequeue)
Musica* dequeue(FilaMusicas* fila) {
    if (fila->inicio == NULL) {
        printf("A fila est� vazia.\n");
        return NULL;
    }

    NoFila* removido = fila->inicio;
    Musica* musicaRemovida = &removido->musica;
    fila->inicio = fila->inicio->proximo;  // Atualiza o in�cio para o pr�ximo n�

    // Se a fila ficar vazia ap�s a remo��o, o ponteiro fim tamb�m precisa ser NULL
    if (fila->inicio == NULL) {
        fila->fim = NULL;
    }

    free(removido);  // Libera o n� removido
    return musicaRemovida;
}

// Fun��o para verificar se a fila est� vazia
int ehVazia(FilaMusicas* fila) {
    return fila->inicio == NULL;
}

// Fun��o para ver a m�sica no in�cio da fila sem remov�-la
Musica* verFrente(FilaMusicas* fila) {
    if (fila->inicio == NULL) {
        printf("A fila est� vazia.\n");
        return NULL;
    }
    return &fila->inicio->musica;  // Retorna a m�sica do in�cio da fila
}

// Fun��o para excluir a fila e liberar a mem�ria
void excluirFila(FilaMusicas* fila) {
    while (fila->inicio != NULL) {
        dequeue(fila);  // Remove todos os elementos da fila
    }
    free(fila);  // Libera a estrutura da fila
}

// Fun��o para carregar dados de um arquivo e preencher a fila
void carregarDados(FilaMusicas* fila, const char* nomeArquivo) {
    FILE* arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para leitura.\n");
        return;
    }
    
    Musica musica;
    while (fscanf(arquivo, "%49[^\n]%*c %49[^\n]%*c %9[^\n]%*c %49[^\n]%*c %d %14[^\n]%*c %c %lf\n", 
                  musica.nomeArtista, musica.nomeMusica, musica.duracao, musica.nomeAlbum, 
                  &musica.streamingsMensais, musica.dataLancamento, &musica.planoPremium, &musica.precoPremium) == 8) {
        enqueue(fila, &musica);  // Adiciona cada m�sica na fila
    }
    fclose(arquivo);
}

// Fun��o para salvar os dados da fila em um arquivo
void salvarDados(FilaMusicas* fila, const char* nomeArquivo) {
    FILE* arquivo = fopen(nomeArquivo, "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return;
    }
    
    NoFila* atual = fila->inicio;
    while (atual != NULL) {
        Musica musica = atual->musica;
        fprintf(arquivo, "%s\n%s\n%s\n%s\n%d\n%s\n%c\n%.2f\n", 
                musica.nomeArtista, musica.nomeMusica, musica.duracao, musica.nomeAlbum, 
                musica.streamingsMensais, musica.dataLancamento, musica.planoPremium, musica.precoPremium);
        atual = atual->proximo;
    }
    fclose(arquivo);
}

// Fun��o principal para testar a fila
int main() {
    setlocale(LC_ALL, "Portuguese");

    FilaMusicas* fila = criarFila();

    Musica musica1 = {"Frank Ocean", "Ivy", "4:09", "Blonde", 1000000, "20/08/2016", 's', 9.99};
    Musica musica2 = {"Beyonc�", "Formation", "4:50", "Lemonade", 5000000, "15/04/2016", 'n', 0.00};

    enqueue(fila, &musica1);
    enqueue(fila, &musica2);

    Musica* frente = verFrente(fila);
    if (frente != NULL) {
        printf("M�sica na frente da fila: %s\n", frente->nomeMusica);
    }

    Musica* removida = dequeue(fila);
    if (removida != NULL) {
        printf("M�sica removida: %s\n", removida->nomeMusica);
    }

    salvarDados(fila, "musicas_fila.txt");

    excluirFila(fila);
    return 0;
}
