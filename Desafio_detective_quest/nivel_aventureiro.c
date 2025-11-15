#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura do nó da árvore binária
typedef struct Sala {
    char nome[50];
    char pista[100];
    struct Sala* esquerda;
    struct Sala* direita;

} Sala;

// Funcao que cria a sala da mansao
Sala* criarSala(const char* nome, const char* pista){
    Sala* novo = (Sala*)malloc(sizeof(Sala)); // Alocação dinâmica de memória
    if(novo == NULL){
        printf("Erro ao alocar memoria.\n");
        exit(1); // Encerra o programa em caso de erro de memória
    }
    strcpy(novo->nome, nome); // Copia o valor passado como parâmetro (string) para o campo 'valor' do nó
    strcpy(novo->pista, pista);
    novo->esquerda = NULL; // Inicializa o filho esquerdo com NULL
    novo->direita = NULL; // Incializa o filho direito com NULL
    return novo;
}

// Estrutura da árvore binária de busca
typedef struct NoPista{
    char Pista[50];
    struct NoPista* esquerda;
    struct NoPista* direita;
} NoPista;

// Cria um novo nó para a árvore de pistas
NoPista* criarNoPista(const char* Pista) {
    struct NoPista* novo = (struct NoPista*) malloc(sizeof(struct NoPista));
    strcpy(novo->Pista, Pista);
    novo->esquerda = NULL;
    novo->direita = NULL;
    return novo;
}

// Insere uma nova pista na árvore binária de busca de forma ordenada
NoPista* inserirPista(NoPista* raiz, const char* pista) {
    if (raiz == NULL)
        return criarNoPista(pista);

    if (strcmp(pista, raiz->Pista) < 0)
        raiz->esquerda = inserirPista(raiz->esquerda, pista);
    else if (strcmp(pista, raiz->Pista) > 0)
        raiz->direita = inserirPista(raiz->direita, pista);

    return raiz;
}

// Pistas em ordem
void exibirPistas(NoPista* raiz) {
    if (raiz != NULL) {
        exibirPistas(raiz->esquerda);
        printf("%s\n", raiz->Pista);
        exibirPistas(raiz->direita);
    }
}

// Função de navegação 
void explorarSalaComPista(Sala* atual, NoPista** arvorePistas){
   char escolha;

   while(1){
    printf("------- DETECTIVE QUEST --------\n");
    printf("Voce esta no %s\n", atual->nome);
    printf("Pista encontrada: %s\n", atual->pista);

    // Inserindo as pistas na árvore
    *arvorePistas = inserirPista(*arvorePistas, atual->pista);

    // Verificando se os nós não estão vázios
    if (atual->esquerda != NULL)
    printf("e - Ir para esquerda %s\n", atual->esquerda->nome);

    if (atual->direita != NULL)
    printf("d - Ir para a direita %s\n", atual->direita->nome);

    printf("s - Sair da exploracao\n");
    printf("Escolha: ");
    scanf(" %c", &escolha);

 // Verificando os caminhos possíveis
   if(escolha == 'e' && atual->esquerda != NULL){
     atual = atual->esquerda;

   } else if (escolha == 'd' && atual->direita != NULL){
    atual = atual->direita;

   } else if (escolha == 's')
   {
    printf("\nSaindo da mansão...\n");
    break;

   } else{
    printf("\nCaminho invalido.\n");
   }
   
   }  
}

    
int main(){

    // Implementando os cômodos da mansão com as pistas
    Sala* hall = criarSala("Hall de Entrada", "Ha marcas de lama no tapete\n");

    hall->esquerda = criarSala("Sala de Estar", "O relogio esta quebrado\n");
    hall->direita = criarSala("Biblioteca", "Um livro esta faltando na prateleira\n");
    hall->esquerda->esquerda = criarSala("Quarto", "A janela esta quebrada\n");
    hall->esquerda->esquerda->esquerda = criarSala("Banheiro", "Ha sangue na banheira\n");
    hall->esquerda->direita = criarSala("Cozinha", "Ha um copo quebrado no chao\n");
    hall -> direita->direita = criarSala("Jardim", "Pegadas levam ate o portao\n");

    NoPista* pistas = NULL; //árvore de pistas começa vazia

    // Inicia a exploração
    explorarSalaComPista(hall, &pistas);

    printf("\n===== PISTAS COLETADAS =====\n");
    exibirPistas(pistas);

    return 0;
}
    
