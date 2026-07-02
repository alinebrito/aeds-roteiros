# Roteiro Prático - Árvore Binária

## Instruções

Este é um roteiro prático com o passo a passo para criar uma Árvore Binária em C.

Ao longo da atividade, você irá construir a estrutura da árvore, criar os nós, inserir valores, percorrer a árvore e testar o funcionamento do programa.

O objetivo é compreender, de forma prática e guiada, como uma árvore binária é representada e manipulada em linguagem C.

> Vamos construir essa árvore juntos:
>
> ```
>             50
>            /  \
>          30    70
>         /  \     \
>       20   40    80
> ```

## Pré-requisitos

Você precisa ter instalado o compilador **GCC** (para C) e o **G++** (para C++). Eles quase sempre vêm juntos.

Verifique no terminal:

```bash
gcc --version
g++ --version
```
---

## PASSO 1: Criar a pasta e o arquivo

No terminal, crie e entre na pasta do projeto:

```bash
mkdir arvore-binaria
cd arvore-binaria
```

Crie um arquivo chamado `arvore.c`. A partir de agora, todo o código em C vai
dentro dele.

**COMMIT & PUSH**

---

## PASSO 2: Definir o nó da árvore

No topo do `arvore.c`, escreva:

```c
#include <stdio.h>
#include <stdlib.h>

// Cada nó guarda um valor e aponta para os filhos esquerdo e direito.
typedef struct No {
    int valor;
    struct No *esquerda;
    struct No *direita;
} No;
```

`int valor`: O número guardado neste nó.

`struct No *esquerda`: Ponteiro para o filho da esquerda (valores menores).

`struct No *direita`: Ponteiro para o filho da direita(valores maiores).

Um ponteiro guarda o endereço de outro nó na memória. Quando um filho não existe, o ponteiro vale `NULL` (vazio). A raiz e as folhas são todas do
mesmo tipo `No`. A árvore é feita de nós apontando para nós.

**COMMIT & PUSH**

---

## PASSO 3: Criar um novo nó

Adicione abaixo do `struct`:

```c
// Cria um nó novo, reservando memória e guardando o valor.
No *criarNo(int valor) {
    No *novo = (No *) malloc(sizeof(No));
    novo->valor = valor;
    novo->esquerda = NULL;
    novo->direita = NULL;
    return novo;
}
```

**COMMIT & PUSH**

---

## PASSO 4: Inserir valores na árvore

Agora a operação principal. A regra é simples e se repete:

Se o valor é menor que o nó atual, vá para a esquerda.
Se é maior, vá para a direita. Quando encontrar um espaço vazio,
coloque o nó ali.

Como essa regra se repete descendo a árvore, usamos recursão (a função chama
a si mesma). Adicione:

```c
// Insere um valor na posição correta e devolve a raiz da (sub)árvore.
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
```
**COMMIT & PUSH**

---

## PASSO 5:  Percorrer a árvore

De que adianta guardar valores se não conseguimos vê-los?

Percorrer é visitar todos os nós numa certa ordem. O percurso em ordem (*in-order*) imprime os valores em ordem crescente.

A ideia: primeiro a esquerda inteira, depois o próprio nó, depois a direita.

```c
// Visita: esquerda -> nó atual -> direita (imprime em ordem crescente).
void visitar(No *raiz) {
    if (raiz == NULL) {
        return;   // subárvore vazia: nada a fazer
    }
    visitar(raiz->esquerda);
    printf("%d ", raiz->valor);
    visitar(raiz->direita);
}
```
**COMMIT & PUSH**

---

## PASSO 6: Escrever a main e testar

Por fim, a função `main` que monta uma árvore e a imprime. Adicione ao final do arquivo:

```c
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

    return 0;
}
```
---

## PASSO 7: Compilar e executar

No terminal, dentro da pasta `arvore-binaria`, compile:

```bash
gcc arvore.c -o arvore
```

Em seguida, execute:

```bash
./arvore
```

Saída esperada:

```
Percurso em ordem (crescente): 20 30 40 50 60 70 80
```

Observe que os números saíram ordenados, mesmo tendo sido inseridos fora de ordem. 

## EXTRA

### Buscar um valor

Retorna `1` se o valor existe na árvore, `0` se não existe.

```c
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
```

Teste na `main`:

```c
printf("O 40 esta na arvore? %d\n", buscar(raiz, 40));  // 1
printf("O 99 esta na arvore? %d\n", buscar(raiz, 99));  // 0
```

### Contar os nós

```c
int contarNos(No *raiz) {
    if (raiz == NULL) {
        return 0;
    }
    return 1 + contarNos(raiz->esquerda) + contarNos(raiz->direita);
}
```

###  Calcular a altura da árvore

```c
int altura(No *raiz) {
    if (raiz == NULL) {
        return 0;
    }
    int alturaEsq = altura(raiz->esquerda);
    int alturaDir = altura(raiz->direita);
    return 1 + (alturaEsq > alturaDir ? alturaEsq : alturaDir);
}
```

---

## Curiosidade — a mesma árvore em C++

Em **C++** podemos escrever a árvore usando uma **classe**, as operações ficam "dentro" do objeto árvore, e quem usa nem vê os
ponteiros.

Crie um arquivo `arvore.cpp`:

```cpp
#include <iostream>
using namespace std;

// O nó continua sendo uma struct simples.
struct No {
    int valor;
    No *esquerda = nullptr;
    No *direita = nullptr;
    No(int v) : valor(v) {}
};

// A classe Arvore "esconde" a raiz e expõe apenas as operações (o TAD).
class Arvore {
private:
    No *raiz = nullptr;

    No *inserir(No *no, int valor) {
        if (no == nullptr) return new No(valor);
        if (valor < no->valor)
            no->esquerda = inserir(no->esquerda, valor);
        else
            no->direita = inserir(no->direita, valor);
        return no;
    }

    void emOrdem(No *no) {
        if (no == nullptr) return;
        emOrdem(no->esquerda);
        cout << no->valor << " ";
        emOrdem(no->direita);
    }

public:
    // Versões "públicas": quem usa não precisa passar a raiz.
    void inserir(int valor) { raiz = inserir(raiz, valor); }
    void emOrdem()          { emOrdem(raiz); }
};

int main() {
    Arvore arvore;

    int valores[] = {50, 30, 70, 20, 40, 60, 80};
    for (int v : valores) {
        arvore.inserir(v);
    }

    cout << "Percurso em ordem (crescente): ";
    arvore.emOrdem();
    cout << endl;

    return 0;
}
```

Compile com o **g++** e execute:

```bash
g++ arvore.cpp -o arvore-cpp
./arvore-cpp
```

A saída é exatamente a mesma da versão em C:

```
Percurso em ordem (crescente): 20 30 40 50 60 70 80
```

# Entrega

Versione o projeto em um repositório no GitHub, realizando commits a cada etapa importante da implementação (por exemplo: criação, implementação da inserção, percursos, funcionalidades avançadas etc.).

Submita a tarefa na [issue #1 aberta](https://github.com/alinebrito/aeds-roteiros/issues/1) neste repositório.
