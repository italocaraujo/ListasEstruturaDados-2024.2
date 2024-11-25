#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

// Definição da estrutura para representar uma música
typedef struct {
    char nomeArtista[50];       // Nome do artista
    char nomeMusica[50];        // Nome da música
    char duracao[10];           // Duração da música
    char nomeAlbum[50];         // Nome do álbum
    int streamingsMensais;      // Número de streamings mensais
    char dataLancamento[15];    // Data de lançamento da música
    char planoPremium;          // 's' se o usuário tiver plano premium, 'n' se não tiver
    double precoPremium;        // Preço do plano premium
} Musica;

// Definição da estrutura para representar a lista de músicas
typedef struct {
    Musica *musicas;            // Vetor de músicas
    int tamanho;                // Quantidade de músicas na lista
    int capacidade;             // Capacidade máxima atual do vetor
} ListaMusicas;

// Função para criar a lista de músicas com capacidade inicial
ListaMusicas* criarLista(int capacidadeInicial) {
    ListaMusicas* lista = (ListaMusicas*)malloc(sizeof(ListaMusicas));  // Alocando memória para a lista
    lista->musicas = (Musica*)malloc(capacidadeInicial * sizeof(Musica));  // Alocando memória para o vetor de músicas
    lista->tamanho = 0;         // Inicializando a lista vazia
    lista->capacidade = capacidadeInicial;  // Definindo a capacidade inicial da lista
    return lista;               // Retorna o ponteiro para a lista
}

// Função para inserir uma nova música no final da lista
void inserirElemento(ListaMusicas* lista, Musica novaMusica) {
    // Verifica se a lista está cheia, se sim, dobra a capacidade
    if (lista->tamanho == lista->capacidade) {
        lista->capacidade *= 2;  // Dobra a capacidade
        lista->musicas = (Musica*)realloc(lista->musicas, lista->capacidade * sizeof(Musica));  // Realoca a memória
    }
    lista->musicas[lista->tamanho] = novaMusica;  // Adiciona a nova música no final da lista
    lista->tamanho++;         // Incrementa o tamanho da lista
}

// Função para inserir uma nova música em uma posição específica da lista
void inserirElementoID(ListaMusicas* lista, Musica novaMusica, int posicao) {
    // Verifica se a posição é válida
    if (posicao < 0 || posicao > lista->tamanho) {
        printf("Posição inválida\n");
        return;
    }
    // Verifica se a lista está cheia, se sim, dobra a capacidade
    if (lista->tamanho == lista->capacidade) {
        lista->capacidade *= 2;
        lista->musicas = (Musica*)realloc(lista->musicas, lista->capacidade * sizeof(Musica));
    }
    // Desloca os elementos para abrir espaço para a nova música
    int i;  // Declarando a variável antes do laço
    for (i = lista->tamanho; i > posicao; i--) {
        lista->musicas[i] = lista->musicas[i - 1];
    }
    lista->musicas[posicao] = novaMusica;  // Insere a nova música na posição desejada
    lista->tamanho++;  // Incrementa o tamanho da lista
}

// Função para inserir uma nova música no início da lista
void inserirElementoInicio(ListaMusicas* lista, Musica novaMusica) {
    inserirElementoID(lista, novaMusica, 0);  // Chama a função de inserção na posição 0 (início)
}

// Função para listar todas as músicas presentes na lista
void listarElementos(ListaMusicas* lista) {
    int i;
    for (i = 0; i < lista->tamanho; i++) {  // Itera sobre todos os elementos da lista
        // Exibe as informações de cada música
        printf("Artista: %s\n", lista->musicas[i].nomeArtista);
        printf("Música: %s\n", lista->musicas[i].nomeMusica);
        printf("Duração: %s\n", lista->musicas[i].duracao);
        printf("Álbum: %s\n", lista->musicas[i].nomeAlbum);
        printf("Streamings Mensais: %d\n", lista->musicas[i].streamingsMensais);
        printf("Data de Lançamento: %s\n", lista->musicas[i].dataLancamento);
        printf("Plano Premium: %c\n", lista->musicas[i].planoPremium);
        printf("Preço Plano Premium: %.2f\n", lista->musicas[i].precoPremium);
        printf("---------------------------\n");
    }
}

// Função para remover uma música pela posição
void removerElemento(ListaMusicas* lista, int posicao) {
    // Verifica se a posição é válida
    if (posicao < 0 || posicao >= lista->tamanho) {
        printf("Posição inválida\n");
        return;
    }
    // Desloca os elementos para preencher o espaço deixado pelo elemento removido
    int i;
    for (i = posicao; i < lista->tamanho - 1; i++) {
        lista->musicas[i] = lista->musicas[i + 1];
    }
    lista->tamanho--;  // Decrementa o tamanho da lista
}

// Função para atualizar as informações de uma música em uma posição específica
void atualizar(ListaMusicas* lista, int posicao, Musica novaMusica) {
    // Verifica se a posição é válida
    if (posicao < 0 || posicao >= lista->tamanho) {
        printf("Posição inválida\n");
        return;
    }
    lista->musicas[posicao] = novaMusica;  // Atualiza a música na posição indicada
}

// Função para buscar uma música pelo nome
Musica* buscarElemento(ListaMusicas* lista, char* nomeMusica) {
    int i;
    for (i = 0; i < lista->tamanho; i++) {  // Itera sobre a lista de músicas
        // Compara o nome da música com o nome buscado
        if (strcmp(lista->musicas[i].nomeMusica, nomeMusica) == 0) {
            return &lista->musicas[i];  // Retorna o ponteiro para a música encontrada
        }
    }
    return NULL;  // Retorna NULL se a música não for encontrada
}

// Função para retornar o tamanho atual da lista
int tamanho(ListaMusicas* lista) {
    return lista->tamanho;
}

// Função para excluir a lista e liberar a memória alocada
void excluirLista(ListaMusicas* lista) {
    free(lista->musicas);  // Libera a memória do vetor de músicas
    free(lista);  // Libera a memória da lista
}

// Função para carregar os dados de músicas de um arquivo
void carregarDados(ListaMusicas* lista, const char* nomeArquivo) {
    FILE* arquivo = fopen(nomeArquivo, "r");  // Abre o arquivo para leitura
    if (arquivo == NULL) {  // Verifica se o arquivo foi aberto corretamente
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    Musica musica;
    // Lê os dados do arquivo e insere as músicas na lista
    while (fscanf(arquivo, "%s %s %s %s %d %s %c %lf",
                  musica.nomeArtista, musica.nomeMusica, musica.duracao,
                  musica.nomeAlbum, &musica.streamingsMensais, musica.dataLancamento,
                  &musica.planoPremium, &musica.precoPremium) != EOF) {
        inserirElemento(lista, musica);  // Insere a música lida na lista
    }

    fclose(arquivo);  // Fecha o arquivo
}

// Função para salvar os dados da lista de músicas em um arquivo
void salvarDados(ListaMusicas* lista, const char* nomeArquivo) {
    FILE* arquivo = fopen(nomeArquivo, "w");  // Abre o arquivo para escrita
    if (arquivo == NULL) {  // Verifica se o arquivo foi aberto corretamente
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    int i;
    // Escreve as informações das músicas no arquivo
    for (i = 0; i < lista->tamanho; i++) {
        fprintf(arquivo, "%s %s %s %s %d %s %c %.2f\n",
                lista->musicas[i].nomeArtista, lista->musicas[i].nomeMusica,
                lista->musicas[i].duracao, lista->musicas[i].nomeAlbum,
                lista->musicas[i].streamingsMensais, lista->musicas[i].dataLancamento,
                lista->musicas[i].planoPremium, lista->musicas[i].precoPremium);
    }

    fclose(arquivo);  // Fecha o arquivo
}

int main() {
	setlocale(LC_ALL, "Portuguese"); // Define o idioma para português
    ListaMusicas* lista = criarLista(10);
	
	Musica musica1 = {"Frank Ocean", "Ivy", "4:09", "Blonde", 1000000, "20/08/2016", 's', 9.99};
	inserirElemento(lista, musica1);
	
    // Aqui você pode adicionar músicas de teste ou carregar do arquivo
    listarElementos(lista);  // Para listar as músicas no terminal

    excluirLista(lista);
    return 0;
}