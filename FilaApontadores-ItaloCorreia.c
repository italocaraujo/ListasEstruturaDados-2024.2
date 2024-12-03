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

// Estrutura para representar o nó da fila
typedef struct NoFila {
    Musica musica;           // Música armazenada no nó
    struct NoFila* proximo;  // Ponteiro para o próximo nó
} NoFila;

// Estrutura para representar a fila de músicas
typedef struct FilaMusicas {
    NoFila* inicio;   // Ponteiro para o início da fila
    NoFila* fim;      // Ponteiro para o fim da fila
} FilaMusicas;

// Função para criar uma fila vazia
FilaMusicas* criarFila() {
    FilaMusicas* fila = (FilaMusicas*)malloc(sizeof(FilaMusicas));
    fila->inicio = NULL;
    fila->fim = NULL;
    return fila;
}

// Função para adicionar uma música na fila (enqueue)
void enqueue(FilaMusicas* fila, Musica* novaMusica) {
    NoFila* novoNo = (NoFila*)malloc(sizeof(NoFila));
    novoNo->musica = *novaMusica;
    novoNo->proximo = NULL;  // Novo nó aponta para NULL (fim da fila)
    
    if (fila->fim == NULL) {
        fila->inicio = novoNo;  // Se a fila estava vazia, o novo nó é o início
    } else {
        fila->fim->proximo = novoNo;  // Se a fila não estava vazia, adiciona no final
    }
    fila->fim = novoNo;  // Atualiza o ponteiro fim para o novo nó
}

// Função para remover uma música da fila (dequeue)
Musica* dequeue(FilaMusicas* fila) {
    if (fila->inicio == NULL) {
        printf("A fila está vazia.\n");
        return NULL;
    }

    NoFila* removido = fila->inicio;
    Musica* musicaRemovida = &removido->musica;
    fila->inicio = fila->inicio->proximo;  // Atualiza o início para o próximo nó

    // Se a fila ficar vazia após a remoção, o ponteiro fim também precisa ser NULL
    if (fila->inicio == NULL) {
        fila->fim = NULL;
    }

    free(removido);  // Libera o nó removido
    return musicaRemovida;
}

// Função para verificar se a fila está vazia
int ehVazia(FilaMusicas* fila) {
    return fila->inicio == NULL;
}

// Função para ver a música no início da fila sem removê-la
Musica* verFrente(FilaMusicas* fila) {
    if (fila->inicio == NULL) {
        printf("A fila está vazia.\n");
        return NULL;
    }
    return &fila->inicio->musica;  // Retorna a música do início da fila
}

// Função para excluir a fila e liberar a memória
void excluirFila(FilaMusicas* fila) {
    while (fila->inicio != NULL) {
        dequeue(fila);  // Remove todos os elementos da fila
    }
    free(fila);  // Libera a estrutura da fila
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

// Função principal para testar a fila
int main() {
    setlocale(LC_ALL, "Portuguese");

    FilaMusicas* fila = criarFila();

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
