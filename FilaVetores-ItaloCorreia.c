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
} Musica;

// Estrutura para representar a fila de músicas
typedef struct FilaMusicas {
    Musica* elementos;  // Vetor para armazenar as músicas
    int inicio;         // Índice do início da fila
    int fim;            // Índice do próximo espaço disponível
    int capacidade;     // Capacidade máxima da fila
} FilaMusicas;

// Função para criar uma fila vazia
FilaMusicas* criarFila(int capacidade) {
    FilaMusicas* fila = (FilaMusicas*)malloc(sizeof(FilaMusicas));
    fila->capacidade = capacidade;
    fila->inicio = 0;
    fila->fim = 0;
    fila->elementos = (Musica*)malloc(capacidade * sizeof(Musica));
    return fila;
}

// Função para adicionar uma música na fila (enqueue)
void enqueue(FilaMusicas* fila, Musica* novaMusica) {
    if (fila->fim >= fila->capacidade) {
        printf("A fila está cheia.\n");
        return;
    }
    fila->elementos[fila->fim] = *novaMusica;
    fila->fim++;
}

// Função para remover uma música da fila (dequeue)
Musica* dequeue(FilaMusicas* fila) {
    if (fila->inicio == fila->fim) {
        printf("A fila está vazia.\n");
        return NULL;
    }
    Musica* musicaRemovida = &fila->elementos[fila->inicio];
    fila->inicio++;
    return musicaRemovida;
}

// Função para verificar se a fila está vazia
int ehVazia(FilaMusicas* fila) {
    return fila->inicio == fila->fim;
}

// Função para ver a música no início da fila sem removê-la
Musica* verFrente(FilaMusicas* fila) {
    if (fila->inicio == fila->fim) {
        printf("A fila está vazia.\n");
        return NULL;
    }
    return &fila->elementos[fila->inicio];
}

// Função para excluir a fila e liberar a memória
void excluirFila(FilaMusicas* fila) {
    free(fila->elementos);
    free(fila);
}

// Função para carregar dados de um arquivo e preencher a fila
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
        enqueue(fila, &musica);  // Adiciona cada música na fila
    }
    fclose(arquivo);
}

// Função para salvar os dados da fila em um arquivo
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

// Função principal para testar a fila
int main() {
    setlocale(LC_ALL, "Portuguese");

    FilaMusicas* fila = criarFila(10);

    Musica musica1 = {"Frank Ocean", "Ivy", "4:09", "Blonde", 1000000, "20/08/2016", 's', 9.99};
    Musica musica2 = {"Beyoncé", "Formation", "4:50", "Lemonade", 5000000, "15/04/2016", 'n', 0.00};

    enqueue(fila, &musica1);
    enqueue(fila, &musica2);

    Musica* frente = verFrente(fila);
    if (frente != NULL) {
        printf("Música na frente da fila: %s\n", frente->nomeMusica);
    }

    Musica* removida = dequeue(fila);
    if (removida != NULL) {
        printf("Música removida: %s\n", removida->nomeMusica);
    }

    salvarDados(fila, "musicas_fila.txt");

    excluirFila(fila);
    return 0;
}
