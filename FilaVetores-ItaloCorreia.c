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

// Estrutura para representar a fila de m�sicas
typedef struct FilaMusicas {
    Musica* elementos;  // Vetor para armazenar as m�sicas
    int inicio;         // �ndice do in�cio da fila
    int fim;            // �ndice do pr�ximo espa�o dispon�vel
    int capacidade;     // Capacidade m�xima da fila
} FilaMusicas;

// Fun��o para criar uma fila vazia
FilaMusicas* criarFila(int capacidade) {
    FilaMusicas* fila = (FilaMusicas*)malloc(sizeof(FilaMusicas));
    fila->capacidade = capacidade;
    fila->inicio = 0;
    fila->fim = 0;
    fila->elementos = (Musica*)malloc(capacidade * sizeof(Musica));
    return fila;
}

// Fun��o para adicionar uma m�sica na fila (enqueue)
void enqueue(FilaMusicas* fila, Musica* novaMusica) {
    if (fila->fim >= fila->capacidade) {
        printf("A fila est� cheia.\n");
        return;
    }
    fila->elementos[fila->fim] = *novaMusica;
    fila->fim++;
}

// Fun��o para remover uma m�sica da fila (dequeue)
Musica* dequeue(FilaMusicas* fila) {
    if (fila->inicio == fila->fim) {
        printf("A fila est� vazia.\n");
        return NULL;
    }
    Musica* musicaRemovida = &fila->elementos[fila->inicio];
    fila->inicio++;
    return musicaRemovida;
}

// Fun��o para verificar se a fila est� vazia
int ehVazia(FilaMusicas* fila) {
    return fila->inicio == fila->fim;
}

// Fun��o para ver a m�sica no in�cio da fila sem remov�-la
Musica* verFrente(FilaMusicas* fila) {
    if (fila->inicio == fila->fim) {
        printf("A fila est� vazia.\n");
        return NULL;
    }
    return &fila->elementos[fila->inicio];
}

// Fun��o para excluir a fila e liberar a mem�ria
void excluirFila(FilaMusicas* fila) {
    free(fila->elementos);
    free(fila);
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
    
    for (int i = fila->inicio; i < fila->fim; i++) {
        Musica musica = fila->elementos[i];
        fprintf(arquivo, "%s\n%s\n%s\n%s\n%d\n%s\n%c\n%.2f\n", 
                musica.nomeArtista, musica.nomeMusica, musica.duracao, musica.nomeAlbum, 
                musica.streamingsMensais, musica.dataLancamento, musica.planoPremium, musica.precoPremium);
    }
    fclose(arquivo);
}

// Fun��o principal para testar a fila
int main() {
    setlocale(LC_ALL, "Portuguese");

    FilaMusicas* fila = criarFila(10);

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
