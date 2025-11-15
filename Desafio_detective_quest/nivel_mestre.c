#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAMANHO_HASH 10

// =========================
//   ESTRUTURA DA HASH
// =========================

typedef struct Itemhash {
    char pista[100];
    char suspeito[100];
    struct Itemhash* prox;
} Itemhash;

Itemhash* tabela_hash[TAMANHO_HASH];

// Função hash para converter a pista em índice
int funcao_hash(const char* str) {
    int soma = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        soma += str[i];
    }
    return soma % TAMANHO_HASH;
}

// Inserir pista + suspeito
void inserirNaHash(const char* pista, const char* suspeito) {

    int indice = funcao_hash(pista);

    Itemhash* novo = (Itemhash*)malloc(sizeof(Itemhash));
    strcpy(novo->pista, pista);
    strcpy(novo->suspeito, suspeito);

    novo->prox = tabela_hash[indice];
    tabela_hash[indice] = novo;
}

// Procurar suspeito pela pista
char* encontrarSuspeito(const char* pista) {

    int indice = funcao_hash(pista);

    Itemhash* atual = tabela_hash[indice];

    while (atual != NULL) {
        if (strcmp(atual->pista, pista) == 0) {
            return atual->suspeito;
        }
        atual = atual->prox;
    }

    return NULL;
}


// ============================
//     ÁRVORE DE PISTAS
// ============================

typedef struct NoPista {
    char Pista[100];
    struct NoPista* esquerda;
    struct NoPista* direita;
} NoPista;

NoPista* criarNoPista(const char* pista) {
    NoPista* novo = (NoPista*)malloc(sizeof(NoPista));
    strcpy(novo->Pista, pista);
    novo->esquerda = NULL;
    novo->direita = NULL;
    return novo;
}

NoPista* inserirPista(NoPista* raiz, const char* pista) {
    if (raiz == NULL)
        return criarNoPista(pista);

    if (strcmp(pista, raiz->Pista) < 0)
        raiz->esquerda = inserirPista(raiz->esquerda, pista);
    else if (strcmp(pista, raiz->Pista) > 0)
        raiz->direita = inserirPista(raiz->direita, pista);

    return raiz;
}

void exibirPistas(NoPista* raiz) {
    if (raiz != NULL) {
        exibirPistas(raiz->esquerda);
        printf("%s", raiz->Pista);
        exibirPistas(raiz->direita);
    }
}

// Exibe pistas + suspeitos
void verificarSuspeitoFinal(NoPista* raiz) {
    if (raiz == NULL) return;

    verificarSuspeitoFinal(raiz->esquerda);

    char* suspeito = encontrarSuspeito(raiz->Pista);

    printf("Pista: %s", raiz->Pista);
    if (suspeito != NULL) {
        printf(" → Suspeito: %s\n", suspeito);
    } else {
        printf(" → Suspeito: NÃO ENCONTRADO\n");
    }

    verificarSuspeitoFinal(raiz->direita);
}



// ============================
//       SALAS DA MANSÃO
// ============================

typedef struct Sala {
    char nome[50];
    char pista[100];
    struct Sala* esquerda;
    struct Sala* direita;
} Sala;

Sala* criarSala(const char* nome, const char* pista) {
    Sala* novo = (Sala*)malloc(sizeof(Sala));
    strcpy(novo->nome, nome);
    strcpy(novo->pista, pista);
    novo->esquerda = NULL;
    novo->direita = NULL;
    return novo;
}


void explorarSalaComPista(Sala* atual, NoPista** arvorePistas) {
    char escolha;

    while (1) {
        printf("\n------- DETECTIVE QUEST --------\n");
        printf("Você está no %s\n", atual->nome);
        printf("Pista encontrada: %s\n", atual->pista);

        // Adicionar na árvore de pistas
        *arvorePistas = inserirPista(*arvorePistas, atual->pista);

        if (atual->esquerda != NULL)
            printf("e - Ir para a esquerda: %s\n", atual->esquerda->nome);

        if (atual->direita != NULL)
            printf("d - Ir para a direita: %s\n", atual->direita->nome);

        printf("s - Sair da exploração\n");
        printf("Escolha: ");
        scanf(" %c", &escolha);

        if (escolha == 'e' && atual->esquerda != NULL) {
            atual = atual->esquerda;

        } else if (escolha == 'd' && atual->direita != NULL) {
            atual = atual->direita;

        } else if (escolha == 's') {
            printf("\nSaindo da mansão...\n");
            break;

        } else {
            printf("\nCaminho inválido.\n");
        }
    }
}



// ============================
//           MAIN
// ============================

int main() {

    // Inicializar tabela hash
    for (int i = 0; i < TAMANHO_HASH; i++)
        tabela_hash[i] = NULL;

    // Inserir pista + suspeito
    inserirNaHash("Ha marcas de lama no tapete\n", "Jardineiro");
    inserirNaHash("O relogio esta quebrado\n", "Mordomo");
    inserirNaHash("Um livro esta faltando na prateleira\n", "Bibliotecária");
    inserirNaHash("A janela esta quebrada\n", "Vizinho");
    inserirNaHash("Ha sangue na banheira\n", "Hóspede Misterioso");
    inserirNaHash("Ha um copo quebrado no chao\n", "Chef de Cozinha");
    inserirNaHash("Pegadas levam ate o portao\n", "Desconhecido");

    // Criar salas
    Sala* hall = criarSala("Hall de Entrada", "Ha marcas de lama no tapete\n");
    hall->esquerda = criarSala("Sala de Estar", "O relogio esta quebrado\n");
    hall->direita = criarSala("Biblioteca", "Um livro esta faltando na prateleira\n");
    hall->esquerda->esquerda = criarSala("Quarto", "A janela esta quebrada\n");
    hall->esquerda->esquerda->esquerda = criarSala("Banheiro", "Ha sangue na banheira\n");
    hall->esquerda->direita = criarSala("Cozinha", "Ha um copo quebrado no chao\n");
    hall->direita->direita = criarSala("Jardim", "Pegadas levam ate o portao\n");

    NoPista* pistas = NULL;

    explorarSalaComPista(hall, &pistas);

    printf("\n===== PISTAS COLETADAS EM ORDEM =====\n");
    exibirPistas(pistas);

    printf("\n===== JULGAMENTO FINAL =====\n");
    verificarSuspeitoFinal(pistas);

    return 0;
}
