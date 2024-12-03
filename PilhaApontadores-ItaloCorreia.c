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

// Estrutura para representar o n� da pilha de m�sicas
typedef struct NoPilha {
    Musica musica;
    struct NoPilha* proximo;  // Ponteiro para o pr�ximo n� (elemento da pilha)
} NoPilha;

// Estrutura para representar a pilha de m�sicas
typedef struct PilhaMusicas {
    NoPilha* topo;           // Ponteiro para o topo da pilha
} PilhaMusicas;

// Fun��o para criar uma pilha vazia
PilhaMusicas* criarPilha() {
    PilhaMusicas* pilha = (PilhaMusicas*)malloc(sizeof(PilhaMusicas));
    pilha->topo = NULL;  // Inicializa o topo como NULL
    return pilha;
}

// Fun��o para inserir uma m�sica no topo da pilha
void push(PilhaMusicas* pilha, Musica* novaMusica) {
    NoPilha* novoNo = (NoPilha*)malloc(sizeof(NoPilha));
    novoNo->musica = *novaMusica;  // Atribui a m�sica ao novo n�
    novoNo->proximo = pilha->topo;  // Aponta para o n� anterior
    pilha->topo = novoNo;  // Atualiza o topo para o novo n�
}

// Fun��o para remover uma m�sica do topo da pilha
Musica* pop(PilhaMusicas* pilha) {
    if (pilha->topo == NULL) {
        printf("A pilha est� vazia.\n");
        return NULL;
    }

    NoPilha* removido = pilha->topo;
    pilha->topo = pilha->topo->proximo;  // Atualiza o topo para o pr�ximo n�
    Musica* musicaRemovida = &removido->musica;
    free(removido);  // Libera o n� removido
    return musicaRemovida;
}

// Fun��o para verificar se a pilha est� vazia
int ehVazia(PilhaMusicas* pilha) {
    return pilha->topo == NULL;
}

// Fun��o para ver o topo da pilha sem remover
Musica* verTopo(PilhaMusicas* pilha) {
    if (pilha->topo == NULL) {
        printf("A pilha est� vazia.\n");
        return NULL;
    }
    return &pilha->topo->musica;  // Retorna a m�sica no topo
}

// Fun��o para excluir a pilha e liberar a mem�ria
void excluirPilha(PilhaMusicas* pilha) {
    while (pilha->topo != NULL) {
        pop(pilha);  // Remove todos os elementos da pilha
    }
    free(pilha);  // Libera a estrutura da pilha
}

// Fun��o para carregar dados de um arquivo e preencher a pilha
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
        push(pilha, &musica);  // Insere cada m�sica na pilha
    }
    fclose(arquivo);
}

// Fun��o para salvar os dados da pilha em um arquivo
void salvarDados(PilhaMusicas* pilha, const char* nomeArquivo) {
    FILE* arquivo = fopen(nomeArquivo, "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return;
    }
    
    NoPilha* atual = pilha->topo;
    while (atual != NULL) {
        Musica musica = atual->musica;
        fprintf(arquivo, "%s\n%s\n%s\n%s\n%d\n%s\n%c\n%.2f\n", 
                musica.nomeArtista, musica.nomeMusica, musica.duracao, musica.nomeAlbum, 
                musica.streamingsMensais, musica.dataLancamento, musica.planoPremium, musica.precoPremium);
        atual = atual->proximo;
    }
    fclose(arquivo);
}

// Fun��o principal para testar a pilha
int main() {
    setlocale(LC_ALL, "Portuguese");

    PilhaMusicas* pilha = criarPilha();

    Musica musica1 = {"Frank Ocean", "Ivy", "4:09", "Blonde", 1000000, "20/08/2016", 's', 9.99};
    Musica musica2 = {"Beyonc�", "Formation", "4:50", "Lemonade", 5000000, "15/04/2016", 'n', 0.00};

    push(pilha, &musica1);
    push(pilha, &musica2);

    Musica* topo = verTopo(pilha);
    if (topo != NULL) {
        printf("M�sica no topo da pilha: %s\n", topo->nomeMusica);
    }

    Musica* removida = pop(pilha);
    if (removida != NULL) {
        printf("M�sica removida: %s\n", removida->nomeMusica);
    }

    salvarDados(pilha, "musicas.txt");

    excluirPilha(pilha);
    return 0;
}
