#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

// Defini��o da estrutura para representar uma m�sica
typedef struct {
    char nomeArtista[50];       // Nome do artista
    char nomeMusica[50];        // Nome da m�sica
    char duracao[10];           // Dura��o da m�sica
    char nomeAlbum[50];         // Nome do �lbum
    int streamingsMensais;      // N�mero de streamings mensais
    char dataLancamento[15];    // Data de lan�amento da m�sica
    char planoPremium;          // 's' se o usu�rio tiver plano premium, 'n' se n�o tiver
    double precoPremium;        // Pre�o do plano premium
} Musica;

// Defini��o da estrutura para representar a lista de m�sicas
typedef struct {
    Musica *musicas;            // Vetor de m�sicas
    int tamanho;                // Quantidade de m�sicas na lista
    int capacidade;             // Capacidade m�xima atual do vetor
} ListaMusicas;

// Fun��o para criar a lista de m�sicas com capacidade inicial
ListaMusicas* criarLista(int capacidadeInicial) {
    ListaMusicas* lista = (ListaMusicas*)malloc(sizeof(ListaMusicas));  // Alocando mem�ria para a lista
    lista->musicas = (Musica*)malloc(capacidadeInicial * sizeof(Musica));  // Alocando mem�ria para o vetor de m�sicas
    lista->tamanho = 0;         // Inicializando a lista vazia
    lista->capacidade = capacidadeInicial;  // Definindo a capacidade inicial da lista
    return lista;               // Retorna o ponteiro para a lista
}

// Fun��o para inserir uma nova m�sica no final da lista
void inserirElemento(ListaMusicas* lista, Musica novaMusica) {
    // Verifica se a lista est� cheia, se sim, dobra a capacidade
    if (lista->tamanho == lista->capacidade) {
        lista->capacidade *= 2;  // Dobra a capacidade
        lista->musicas = (Musica*)realloc(lista->musicas, lista->capacidade * sizeof(Musica));  // Realoca a mem�ria
    }
    lista->musicas[lista->tamanho] = novaMusica;  // Adiciona a nova m�sica no final da lista
    lista->tamanho++;         // Incrementa o tamanho da lista
}

// Fun��o para inserir uma nova m�sica em uma posi��o espec�fica da lista
void inserirElementoID(ListaMusicas* lista, Musica novaMusica, int posicao) {
    // Verifica se a posi��o � v�lida
    if (posicao < 0 || posicao > lista->tamanho) {
        printf("Posi��o inv�lida\n");
        return;
    }
    // Verifica se a lista est� cheia, se sim, dobra a capacidade
    if (lista->tamanho == lista->capacidade) {
        lista->capacidade *= 2;
        lista->musicas = (Musica*)realloc(lista->musicas, lista->capacidade * sizeof(Musica));
    }
    // Desloca os elementos para abrir espa�o para a nova m�sica
    int i;  // Declarando a vari�vel antes do la�o
    for (i = lista->tamanho; i > posicao; i--) {
        lista->musicas[i] = lista->musicas[i - 1];
    }
    lista->musicas[posicao] = novaMusica;  // Insere a nova m�sica na posi��o desejada
    lista->tamanho++;  // Incrementa o tamanho da lista
}

// Fun��o para inserir uma nova m�sica no in�cio da lista
void inserirElementoInicio(ListaMusicas* lista, Musica novaMusica) {
    inserirElementoID(lista, novaMusica, 0);  // Chama a fun��o de inser��o na posi��o 0 (in�cio)
}

// Fun��o para listar todas as m�sicas presentes na lista
void listarElementos(ListaMusicas* lista) {
    int i;
    for (i = 0; i < lista->tamanho; i++) {  // Itera sobre todos os elementos da lista
        // Exibe as informa��es de cada m�sica
        printf("Artista: %s\n", lista->musicas[i].nomeArtista);
        printf("M�sica: %s\n", lista->musicas[i].nomeMusica);
        printf("Dura��o: %s\n", lista->musicas[i].duracao);
        printf("�lbum: %s\n", lista->musicas[i].nomeAlbum);
        printf("Streamings Mensais: %d\n", lista->musicas[i].streamingsMensais);
        printf("Data de Lan�amento: %s\n", lista->musicas[i].dataLancamento);
        printf("Plano Premium: %c\n", lista->musicas[i].planoPremium);
        printf("Pre�o Plano Premium: %.2f\n", lista->musicas[i].precoPremium);
        printf("---------------------------\n");
    }
}

// Fun��o para remover uma m�sica pela posi��o
void removerElemento(ListaMusicas* lista, int posicao) {
    // Verifica se a posi��o � v�lida
    if (posicao < 0 || posicao >= lista->tamanho) {
        printf("Posi��o inv�lida\n");
        return;
    }
    // Desloca os elementos para preencher o espa�o deixado pelo elemento removido
    int i;
    for (i = posicao; i < lista->tamanho - 1; i++) {
        lista->musicas[i] = lista->musicas[i + 1];
    }
    lista->tamanho--;  // Decrementa o tamanho da lista
}

// Fun��o para atualizar as informa��es de uma m�sica em uma posi��o espec�fica
void atualizar(ListaMusicas* lista, int posicao, Musica novaMusica) {
    // Verifica se a posi��o � v�lida
    if (posicao < 0 || posicao >= lista->tamanho) {
        printf("Posi��o inv�lida\n");
        return;
    }
    lista->musicas[posicao] = novaMusica;  // Atualiza a m�sica na posi��o indicada
}

// Fun��o para buscar uma m�sica pelo nome
Musica* buscarElemento(ListaMusicas* lista, char* nomeMusica) {
    int i;
    for (i = 0; i < lista->tamanho; i++) {  // Itera sobre a lista de m�sicas
        // Compara o nome da m�sica com o nome buscado
        if (strcmp(lista->musicas[i].nomeMusica, nomeMusica) == 0) {
            return &lista->musicas[i];  // Retorna o ponteiro para a m�sica encontrada
        }
    }
    return NULL;  // Retorna NULL se a m�sica n�o for encontrada
}

// Fun��o para retornar o tamanho atual da lista
int tamanho(ListaMusicas* lista) {
    return lista->tamanho;
}

// Fun��o para excluir a lista e liberar a mem�ria alocada
void excluirLista(ListaMusicas* lista) {
    free(lista->musicas);  // Libera a mem�ria do vetor de m�sicas
    free(lista);  // Libera a mem�ria da lista
}

// Fun��o para carregar os dados de m�sicas de um arquivo
void carregarDados(ListaMusicas* lista, const char* nomeArquivo) {
    FILE* arquivo = fopen(nomeArquivo, "r");  // Abre o arquivo para leitura
    if (arquivo == NULL) {  // Verifica se o arquivo foi aberto corretamente
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    Musica musica;
    // L� os dados do arquivo e insere as m�sicas na lista
    while (fscanf(arquivo, "%s %s %s %s %d %s %c %lf",
                  musica.nomeArtista, musica.nomeMusica, musica.duracao,
                  musica.nomeAlbum, &musica.streamingsMensais, musica.dataLancamento,
                  &musica.planoPremium, &musica.precoPremium) != EOF) {
        inserirElemento(lista, musica);  // Insere a m�sica lida na lista
    }

    fclose(arquivo);  // Fecha o arquivo
}

// Fun��o para salvar os dados da lista de m�sicas em um arquivo
void salvarDados(ListaMusicas* lista, const char* nomeArquivo) {
    FILE* arquivo = fopen(nomeArquivo, "w");  // Abre o arquivo para escrita
    if (arquivo == NULL) {  // Verifica se o arquivo foi aberto corretamente
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    int i;
    // Escreve as informa��es das m�sicas no arquivo
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
	setlocale(LC_ALL, "Portuguese"); // Define o idioma para portugu�s
    ListaMusicas* lista = criarLista(10);
	
	Musica musica1 = {"Frank Ocean", "Ivy", "4:09", "Blonde", 1000000, "20/08/2016", 's', 9.99};
	inserirElemento(lista, musica1);
	
    // Aqui voc� pode adicionar m�sicas de teste ou carregar do arquivo
    listarElementos(lista);  // Para listar as m�sicas no terminal

    excluirLista(lista);
    return 0;
}