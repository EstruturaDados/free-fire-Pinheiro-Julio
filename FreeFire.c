#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Define uma constante para o comprimento máximo que cada texto pode ter.
#define MAX_STR_LEN 50 // Tamanho máximo para as string/texto

// define uma constante para o número máximo de itens que nossa lista pode conter.
#define TAM_MAX 10 // Define o número máximo de itens na lista estática

// Estrutura que representa um item da mochila
typedef struct {
    char nome[MAX_STR_LEN];
    char tipo[MAX_STR_LEN];
    int quantidade;
} Item;

// Estrutura que representa a lista estática
typedef struct {
    Item dados[TAM_MAX]; 
    int quantidade; // Este é nosso contador de controle. Ele informa quantos itens estão realmente armazenados na lista
} ListaEstatica;


void inicializarListaEstatica(ListaEstatica *lista);

void inserirListaEstatica(ListaEstatica *lista, const char *nome, const char *tipo, int quantidade);
void removerListaEstatica(ListaEstatica *lista, const char *nome);
void listarListaEstatica(const ListaEstatica *lista);

//-------------------------------------------------------------
// PROGRAMA PRINCIPAL (main) e MENUS
//-------------------------------------------------------------




int main(){
     ListaEstatica lista;
    inicializarListaEstatica(&lista);
    int opcao;
    char texto[MAX_STR_LEN];
    do {
        printf("=======================================\n");
        printf("\nMOCHILA DE SOBREVIVENCIA - CODIGO DA ILHA\n");
        printf("=======================================\n");
        printf("Itens na Mochila: %d/%d\n\n", lista.quantidade, TAM_MAX);
        printf("1. Adicionar Item (Loot)\n");
        printf("2. Remover Item\n");
        printf("3. Listar Itens na Mochila\n");
        printf("0. Sair\n");
        printf("----------------------------------------\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar(); // Limpa o buffer do scanf

        switch (opcao) {
           case 1: {
                char nome[MAX_STR_LEN];
                char tipo[MAX_STR_LEN];
                int qtd;
                
                printf("Nome do Item: ");
                fgets(nome, MAX_STR_LEN, stdin);
                nome[strcspn(nome, "\n")] = '\0';

                printf("Tipo do Item (Arma, Municao, Cura, etc.): ");
                fgets(tipo, MAX_STR_LEN, stdin);
                tipo[strcspn(tipo, "\n")] = '\0';

                printf("Quantidade: ");
                scanf("%d", &qtd);
                getchar();
                
                inserirListaEstatica(&lista, nome, tipo, qtd);
                break;
            }
            case 2:
                printf("Nome do Item a remover: ");
                fgets(texto, MAX_STR_LEN, stdin);
                texto[strcspn(texto, "\n")] = '\0';
                removerListaEstatica(&lista, texto);
                break;
            case 3:
                listarListaEstatica(&lista);
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 0);

    return 0;
}

// -------------------------------------------------------------
// IMPLEMENTAÇÃO DAS FUNÇÕES - LISTA ESTÁTICA
// -------------------------------------------------------------

void inicializarListaEstatica(ListaEstatica *lista) {
    lista->quantidade = 0; // Inicializa o contador de itens com 0
}


void inserirListaEstatica(ListaEstatica *lista, const char *nome, const char *tipo, int quantidade) {
    // primeiro, ela verifica se lista->quantidade ja atingiu TAM_MAX
    // Se sim, a lista está cheia e a função retorna.
    if (lista->quantidade == TAM_MAX) {
        printf("Erro: Mochila cheia! Nao e possivel inserir.\n");
        return;
    }
    
    // Copia os dados para o item
    strcpy(lista->dados[lista->quantidade].nome, nome);
    strcpy(lista->dados[lista->quantidade].tipo, tipo);
    lista->dados[lista->quantidade].quantidade = quantidade;
    
    // Após a cópia, lista->quantidade é incrementado, pois agora temos mais um item na lista.
    lista->quantidade++;
    printf("\n");
    printf("Item \"%s\" adicionado com sucesso!\n", nome);
    
    printf("========== ITENS NA MOCHILA: %d/%d =========\n\n", lista->quantidade, TAM_MAX);

    printf("+----------------------+------------+------------+\n");
    printf("| %-20s | %-10s | %-10s |\n", "Item", "Tipo", "Quantidade");
    printf("+----------------------+------------+------------+\n");
    
   for (int i = 0; i < lista->quantidade; i++) {
   
     printf("| %-20s | %-10s | %-10d |\n",
               lista->dados[i].nome, lista->dados[i].tipo, lista->dados[i].quantidade);
    
    }
   printf("+----------------------+------------+------------+\n");
   printf("\n");

   printf("Pressione Enter para continuar...\n");
    getchar(); // Aguarda a tecla Enter ser pressionada
} 

void removerListaEstatica(ListaEstatica *lista, const char *nome) {
    int i, pos = -1;
    // Para comparar strings, usamos strcmp(). retorna 0 se forem iguais.
    // A função percorre os itens em uso na lista (de 0 até quantidade).
    for (i = 0; i < lista->quantidade; i++) {
        if (strcmp(lista->dados[i].nome, nome) == 0) {
            pos = i;
            break;
        }
    }

    // Tratamento de Erro: Se o loop terminar e pos continuar -1, o item não foi encontrado.
    if (pos == -1) {
        printf("Erro: Item \"%s\" nao encontrado na mochila.\n", nome);
        return;
    }

    // Fechar a lacuna: Se removermos um item do meio da lista, criamos um "buraco".
    // Movemos todos os itens subsequentes uma posição para a esquerda.
    for (i = pos; i < lista->quantidade - 1; i++) {
        lista->dados[i] = lista->dados[i + 1];
    }

    // Atualização do contador: finalmente, quantidade é decrementado para refletir que a lista tem um item a menos.
    lista->quantidade--;
    printf("Item \"%s\" removido com sucesso!\n", nome);

    printf("========== ITENS NA MOCHILA: %d/%d =========\n\n", lista->quantidade, TAM_MAX);

    printf("+----------------------+------------+------------+\n");
    printf("| %-20s | %-10s | %-10s |\n", "Item", "Tipo", "Quantidade");
    printf("+----------------------+------------+------------+\n");
    
   for (int i = 0; i < lista->quantidade; i++) {
   
     printf("| %-20s | %-10s | %-10d |\n",
               lista->dados[i].nome, lista->dados[i].tipo, lista->dados[i].quantidade);
    
    }
   printf("+----------------------+------------+------------+\n");
   printf("\n");

    printf("Pressione Enter para continuar...\n");
    getchar(); // Aguarda a tecla Enter ser pressionada
}

void listarListaEstatica(const ListaEstatica *lista) {
    if (lista->quantidade == 0) {
        printf("A mochila esta vazia.\n");
        return;
    }
    printf("\n========== ITENS NA MOCHILA =========\n");
    printf("Total de itens: %d/%d\n\n", lista->quantidade, TAM_MAX);

    printf("+----------------------+------------+------------+\n");
    printf("| %-20s | %-10s | %-10s |\n", "Item", "Tipo", "Quantidade");
    printf("+----------------------+------------+------------+\n");
    
   for (int i = 0; i < lista->quantidade; i++) {
   
     printf("| %-20s | %-10s | %-10d |\n",
               lista->dados[i].nome, lista->dados[i].tipo, lista->dados[i].quantidade);
    
    }
   printf("+----------------------+------------+------------+\n");
   printf("\n");

   printf("Pressione Enter para continuar...\n");
    getchar(); // Aguarda a tecla Enter ser pressionada
}