#include <stdio.h>
#include <stdlib.h>

// Cada nó guarda um valor e aponta para os filhos esquerdo e direito.
typedef struct No {
    int valor;
    struct No *esquerda;
    struct No *direita;
} No;


// Cria um nó novo, reservando memória e guardando o valor.
No *criarNo(int valor) {
    No *novo = (No *) malloc(sizeof(No));
    novo->valor = valor;
    novo->esquerda = NULL;
    novo->direita = NULL;
    return novo;
}

// Insere um valor na posição correta e devolve a raiz da (sub)árvore.
// Regra: menor vai para a esquerda, maior (ou igual) vai para a direita.
No *inserir(No *raiz, int valor) {
    if (raiz == NULL) {
        return criarNo(valor);   // espaço vazio: cria o nó aqui
    }

    if (valor < raiz->valor) {
        raiz->esquerda = inserir(raiz->esquerda, valor);
    } else {
        raiz->direita = inserir(raiz->direita, valor);
    }

    return raiz;
}

// Visita: esquerda -> nó atual -> direita (imprime em ordem crescente).
void emOrdem(No *raiz) {
    if (raiz == NULL) {
        return;   // subárvore vazia: nada a fazer
    }
    emOrdem(raiz->esquerda);
    printf("%d ", raiz->valor);
    emOrdem(raiz->direita);
}


// Retorna 1 se o valor existe na árvore, 0 caso contrário.
int buscar(No *raiz, int valor) {
    if (raiz == NULL) {
        return 0;                       // não achou
    }
    if (valor == raiz->valor) {
        return 1;                       // achou!
    }
    if (valor < raiz->valor) {
        return buscar(raiz->esquerda, valor);
    } else {
        return buscar(raiz->direita, valor);
    }
}

// Conta quantos nós existem na árvore.
int contarNos(No *raiz) {
    if (raiz == NULL) {
        return 0;
    }
    return 1 + contarNos(raiz->esquerda) + contarNos(raiz->direita);
}

// Calcula a altura: nível do caminho mais longo da raiz até uma folha.
int altura(No *raiz) {
    if (raiz == NULL) {
        return -1;
    }
    int alturaEsq = altura(raiz->esquerda);
    int alturaDir = altura(raiz->direita);
    return 1 + (alturaEsq > alturaDir ? alturaEsq : alturaDir);
}

// Visita: nó atual -> esquerda -> direita.
void preOrdem(No *raiz) {
    if (raiz == NULL) {
        return;
    }
    printf("%d ", raiz->valor);
    preOrdem(raiz->esquerda);
    preOrdem(raiz->direita);
}

// Visita: esquerda -> direita -> nó atual.
void posOrdem(No *raiz) {
    if (raiz == NULL) {
        return;
    }
    posOrdem(raiz->esquerda);
    posOrdem(raiz->direita);
    printf("%d ", raiz->valor);
}

// Retorna o menor valor da árvore (o nó mais à esquerda).
// Obs: só chame se a árvore não estiver vazia.
int menorValor(No *raiz) {
    while (raiz->esquerda != NULL) {
        raiz = raiz->esquerda;
    }
    return raiz->valor;
}

// Libera toda a memória da árvore usando pós-ordem
// (libera os filhos antes do pai).
void liberar(No *raiz) {
    if (raiz == NULL) {
        return;
    }
    liberar(raiz->esquerda);
    liberar(raiz->direita);
    free(raiz);
}

int main() {
    No *raiz = NULL;   // árvore começa vazia

    int valores[] = {50, 30, 70, 20, 40, 60, 80};
    int n = 7;

    for (int i = 0; i < n; i++) {
        raiz = inserir(raiz, valores[i]);
    }

    printf("Percurso em ordem (crescente): ");
    emOrdem(raiz);
    printf("\n");

    //printf("Percurso pre-ordem:            ");
    //preOrdem(raiz);
    //printf("\n");

    //printf("Percurso pos-ordem:            ");
    //posOrdem(raiz);
    //printf("\n\n");

    printf("O 40 esta na arvore? %d\n", buscar(raiz, 40));   // 1
    printf("O 99 esta na arvore? %d\n", buscar(raiz, 99));   // 0
    printf("Quantidade de nos:   %d\n", contarNos(raiz));    // 7
    printf("Altura da arvore:    %d\n", altura(raiz));       // 3
    printf("Menor valor:         %d\n", menorValor(raiz));   // 20

    liberar(raiz);   // devolve a memoria ao final
    return 0;
}
