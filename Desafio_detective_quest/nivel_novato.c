#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura do nó da árvore binária
typedef struct Sala {
    char nome[50];
    struct Sala* esquerda;
    struct Sala* direita;
} Sala;

Sala* criarSala(const char* nome){
    Sala* novo = (Sala*)malloc(sizeof(Sala)); // Alocação dinâmica de memória
    if(novo == NULL){
        printf("Erro ao alocar memoria.\n");
        exit(1); // Encerra o programa em caso de erro de memória
    }
    strcpy(novo->nome, nome); // Copia o valor passado como parâmetro (string) para o campo 'valor' do nó
    novo->esquerda = NULL; // Inicializa o filho esquerdo com NULL
    novo->direita = NULL; // Incializa o filho direito com NULL
    return novo;
}

// Função de navegação 
void explorarSala(Sala* atual){
   char escolha;

   while(1){
    printf("------- DETECTIVE QUEST --------\n");
    printf("Voce esta no %s\n", atual->nome);

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
    printf("Saindo da mansão...");
    break;

   } else{
    printf("Caminho invalido.");
   }
   
   // Verifica se chegou ao fim
   if(atual->esquerda == NULL && atual->direita == NULL){
    printf("Voce chegou ao fim do caminho, na sala %s\n", atual->nome);
    break;
   }
   
   }
    }
    
    
int main(){

    // Imlementando os cômodos da mansão
    Sala* hall = criarSala("Hall de Entrada");

    hall->esquerda = criarSala("Sala de Estar");
    hall->direita = criarSala("Biblioteca");
    hall->esquerda->esquerda = criarSala("Quarto");
    hall->esquerda->esquerda->esquerda = criarSala("Banheiro");
    hall->esquerda->direita = criarSala("Cozinha");
    hall -> direita->direita = criarSala("Jardim");

    explorarSala(hall);


    return 0;
}
    
