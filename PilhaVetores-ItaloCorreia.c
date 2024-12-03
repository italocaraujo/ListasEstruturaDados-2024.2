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

// Estrutura para representar a pilha de músicas
typedef struct PilhaMusicas {
    Musica* elementos;  // Vetor para armazenar as músicas
    int topo;           // Índice do topo da pilha
    int capacidade;     // Capacidade máxima da pilha
} PilhaMusicas;

// Função para criar uma pilha vazia
PilhaMusicas* criarPilha(int capacidade) {
    PilhaMusicas* pilha = (PilhaMusicas*)malloc(sizeof(PilhaMusicas));
    pilha->capacidade = capacidade;
    pilha->topo = -1;
    pilha->elementos = (Musica*)malloc(capacidade * sizeof(Musica));
    return pilha;
}

// Função para inserir uma música no topo da pilha
void push(PilhaMusicas* pilha, Musica* novaMusica) {
    if (pilha->topo >= pilha->capacidade - 1) {
        printf("A pilha está cheia.\n");
        return;
    }
    pilha->topo++;
    pilha->elementos[pilha->topo] = *novaMusica;
}

// Função para remover uma música do topo da pilha
Musica* pop(PilhaMusicas* pilha) {
    if (pilha->topo == -1) {
        printf("A pilha está vazia.\n");
        return NULL;
    }
    return &pilha->elementos[pilha->topo--];
}

// Função para verificar se a pilha está vazia
int ehVazia(PilhaMusicas* pilha) {
    return pilha->topo == -1;
}

// Função para ver o topo da pilha sem remover
Musica* verTopo(PilhaMusicas* pilha) {
    if (pilha->topo == -1) {
        printf("A pilha está vazia.\n");
        return NULL;
    }
    return &pilha->elementos[pilha->topo];
}

// Função para excluir a pilha e liberar a memória
void excluirPilha(PilhaMusicas* pilha) {
    free(pilha->elementos);
    free(pilha);
}

// Função para carregar dados de um arquivo e preencher a pilha
void carregarDados(PilhaMusicas* pilha, const char* nomeArquivo) {
    FILE* arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para leitura.\n");
        return;
    }
    
    Musica musica;
    while (fscanf(arquivo, "%49[^\n]%*c %49[^\n]%*c %9[^\n]%*c %49[^\n]%*c %d %14[^\n]%*c %c %lf\n", 
                  musica.nomeArtista, musica.nomeMusica, musica.duracao, musica.nomeAlbum, 
                  &musica.streamingsMensais, musica.dataLancamento, &musica.planoPremium, &musica.precoPremium) == 8) {
        push(pilha, &musica);
    }
    fclose(arquivo);
}

// Função para salvar os dados da pilha em um arquivo
void salvarDados(PilhaMusicas* pilha, const char* nomeArquivo) {
    FILE* arquivo = fopen(nomeArquivo, "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return;
    }
    
    for (int i = 0; i <= pilha->topo; i++) {
        Musica musica = pilha->elementos[i];
        fprintf(arquivo, "%s\n%s\n%s\n%s\n%d\n%s\n%c\n%.2f\n", 
                musica.nomeArtista, musica.nomeMusica, musica.duracao, musica.nomeAlbum, 
                musica.streamingsMensais, musica.dataLancamento, musica.planoPremium, musica.precoPremium);
    }
    fclose(arquivo);
}

// Função principal para testar a pilha
int main() {
    setlocale(LC_ALL, "Portuguese");

    PilhaMusicas* pilha = criarPilha(10);

    Musica musica1 = {"Frank Ocean", "Ivy", "4:09", "Blonde", 1000000, "20/08/2016", 's', 9.99};
    Musica musica2 = {"Beyoncé", "Formation", "4:50", "Lemonade", 5000000, "15/04/2016", 'n', 0.00};

    push(pilha, &musica1);
    push(pilha, &musica2);

    Musica* topo = verTopo(pilha);
    if (topo != NULL) {
        printf("Música no topo da pilha: %s\n", topo->nomeMusica);
    }

    Musica* removida = pop(pilha);
    if (removida != NULL) {
        printf("Música removida: %s\n", removida->nomeMusica);
    }

    salvarDados(pilha, "musicas.txt");

    excluirPilha(pilha);
    return 0;
}
