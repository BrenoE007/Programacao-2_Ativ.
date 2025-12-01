#include <stdio.h>
#include <stdlib.h>

// Estrutura do nó da árvore
typedef struct no {
    int chave;
    struct no *esquerda;
    struct no *direita;
} No;

// Protótipos das funções
No* criarNo(int valor);
No* inserir(No* raiz, int valor);
No* buscar(No* raiz, int valor);
No* remover(No* raiz, int valor);
No* encontrarMinimo(No* raiz);
void preOrdem(No* raiz);
void emOrdem(No* raiz);
void posOrdem(No* raiz);
void liberarArvore(No* raiz);
void menuPrincipal();
void menuPercurso();

// Função principal
int main() {
    menuPrincipal();
    return 0;
}

// Função para criar um novo nó
No* criarNo(int valor) {
    No* novoNo = (No*)malloc(sizeof(No));
    if (novoNo == NULL) {
        printf("Erro de alocação de memória!\n");
        exit(1);
    }
    novoNo->chave = valor;
    novoNo->esquerda = NULL;
    novoNo->direita = NULL;
    return novoNo;
}

// Função para inserir um valor na árvore
No* inserir(No* raiz, int valor) {
    // Se a árvore está vazia, cria um novo nó
    if (raiz == NULL) {
        return criarNo(valor);
    }

    // Caso contrário, percorre a árvore recursivamente
    if (valor < raiz->chave) {
        raiz->esquerda = inserir(raiz->esquerda, valor);
    } else if (valor > raiz->chave) {
        raiz->direita = inserir(raiz->direita, valor);
    }

    return raiz;
}

// Função para buscar um valor na árvore
No* buscar(No* raiz, int valor) {
    // Caso base: raiz é NULL ou valor está na raiz
    if (raiz == NULL || raiz->chave == valor) {
        return raiz;
    }

    // Valor é maior que a chave da raiz
    if (raiz->chave < valor) {
        return buscar(raiz->direita, valor);
    }

    // Valor é menor que a chave da raiz
    return buscar(raiz->esquerda, valor);
}

// Função auxiliar para encontrar o nó com menor valor (mais à esquerda)
No* encontrarMinimo(No* raiz) {
    No* atual = raiz;
    while (atual && atual->esquerda != NULL) {
        atual = atual->esquerda;
    }
    return atual;
}

// Função para remover um valor da árvore
No* remover(No* raiz, int valor) {
    // Caso base: árvore vazia
    if (raiz == NULL) {
        return raiz;
    }

    // Procura o nó a ser removido
    if (valor < raiz->chave) {
        raiz->esquerda = remover(raiz->esquerda, valor);
    } else if (valor > raiz->chave) {
        raiz->direita = remover(raiz->direita, valor);
    } else {
        // Nó encontrado - implementação dos três casos

        // Caso 1: Nó folha ou com apenas um filho
        if (raiz->esquerda == NULL) {
            No* temp = raiz->direita;
            free(raiz);
            return temp;
        } else if (raiz->direita == NULL) {
            No* temp = raiz->esquerda;
            free(raiz);
            return temp;
        }

        // Caso 3: Nó com dois filhos - usa o sucessor in-order (menor da subárvore direita)
        No* temp = encontrarMinimo(raiz->direita);

        // Copia o valor do sucessor para este nó
        raiz->chave = temp->chave;

        // Remove o sucessor
        raiz->direita = remover(raiz->direita, temp->chave);
    }
    return raiz;
}

// Função para percurso pré-ordem (raiz, esquerda, direita)
void preOrdem(No* raiz) {
    if (raiz != NULL) {
        printf("%d ", raiz->chave);
        preOrdem(raiz->esquerda);
        preOrdem(raiz->direita);
    }
}

// Função para percurso em ordem (esquerda, raiz, direita)
void emOrdem(No* raiz) {
    if (raiz != NULL) {
        emOrdem(raiz->esquerda);
        printf("%d ", raiz->chave);
        emOrdem(raiz->direita);
    }
}

// Função para percurso pós-ordem (esquerda, direita, raiz)
void posOrdem(No* raiz) {
    if (raiz != NULL) {
        posOrdem(raiz->esquerda);
        posOrdem(raiz->direita);
        printf("%d ", raiz->chave);
    }
}

// Função para liberar toda a memória da árvore
void liberarArvore(No* raiz) {
    if (raiz != NULL) {
        liberarArvore(raiz->esquerda);
        liberarArvore(raiz->direita);
        free(raiz);
    }
}

// Submenu para percursos
void menuPercurso(No* raiz) {
    int opcao;

    do {
        printf("\n=== SUBMENU PERCURSO ===\n");
        printf("1 - Pré-ordem\n");
        printf("2 - Em ordem\n");
        printf("3 - Pós-ordem\n");
        printf("0 - Voltar\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                printf("Pré-ordem: ");
                preOrdem(raiz);
                printf("\n");
                break;
            case 2:
                printf("Em ordem: ");
                emOrdem(raiz);
                printf("\n");
                break;
            case 3:
                printf("Pós-ordem: ");
                posOrdem(raiz);
                printf("\n");
                break;
            case 0:
                printf("Voltando ao Menu Principal...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (opcao != 0);
}

// Menu principal
void menuPrincipal() {
    No* raiz = NULL;
    int opcao, valor;
    No* resultado;

    do {
        printf("\n=== ÁRVORE DE BUSCA BINÁRIA ===\n");
        printf("1 - Inserir valor\n");
        printf("2 - Buscar valor\n");
        printf("3 - Remover valor\n");
        printf("4 - Percorrer árvore\n");
        printf("0 - Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                printf("Digite o valor a ser inserido: ");
                scanf("%d", &valor);
                raiz = inserir(raiz, valor);
                printf("Valor %d inserido com sucesso!\n", valor);
                break;

            case 2:
                printf("Digite o valor a ser pesquisado: ");
                scanf("%d", &valor);
                resultado = buscar(raiz, valor);
                if (resultado != NULL) {
                    printf("Valor %d encontrado na árvore!\n", valor);
                } else {
                    printf("Valor %d não encontrado na árvore!\n", valor);
                }
                break;

            case 3:
                printf("Digite o valor a ser removido: ");
                scanf("%d", &valor);
                resultado = buscar(raiz, valor);
                if (resultado != NULL) {
                    raiz = remover(raiz, valor);
                    printf("Valor %d removido com sucesso!\n", valor);
                } else {
                    printf("Valor %d não encontrado na árvore!\n", valor);
                }
                break;

            case 4:
                menuPercurso(raiz);
                break;

            case 0:
                printf("Liberando memória e saindo...\n");
                liberarArvore(raiz);
                break;

            default:
                printf("Opção inválida!\n");
        }
    } while (opcao != 0);
}
