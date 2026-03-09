#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

typedef struct no {
    int valor;
    struct no *esquerda;
    struct no *direita;
} No;

void criarArvore(No **raiz) {
    *raiz = NULL;
}

int arvoreVazia(No *raiz) {
    return raiz == NULL;
}

void inserir(No **raiz, int valor) {
    if(*raiz == NULL) {
        *raiz = (No*)malloc(sizeof(No));
        (*raiz)->esquerda = NULL;
        (*raiz)->direita = NULL;
        (*raiz)->valor = valor;
    } else {
        if(valor < (*raiz)->valor) {
            inserir(&(*raiz)->esquerda, valor);
        } else if(valor > (*raiz)->valor) {
            inserir(&(*raiz)->direita, valor);
        }
    }
}

No* encontrarMaior(No **raiz) {
    if((*raiz)->direita != NULL) {
        return encontrarMaior(&(*raiz)->direita);
    } else {
        No *aux = *raiz;
        if((*raiz)->esquerda != NULL) {
            *raiz = (*raiz)->esquerda;
        } else {
            *raiz = NULL;
        }
        return aux;
    }
}

No* encontrarMenor(No **raiz) {
    if((*raiz)->esquerda != NULL) {
        return encontrarMenor(&(*raiz)->esquerda);
    } else {
        No *aux = *raiz;
        if((*raiz)->direita != NULL) {
            *raiz = (*raiz)->direita;
        } else {
            *raiz = NULL;
        }
        return aux;
    }
}

void remover(No **raiz, int valor) {
    if(*raiz == NULL) {
        printf("\nValor não encontrado na árvore!\n");
        return;
    }
    
    if(valor < (*raiz)->valor) {
        remover(&(*raiz)->esquerda, valor);
    } else if(valor > (*raiz)->valor) {
        remover(&(*raiz)->direita, valor);
    } else {
        No *aux = *raiz;
        
        // Caso 1: Nó folha
        if((*raiz)->esquerda == NULL && (*raiz)->direita == NULL) {
            free(aux);
            *raiz = NULL;
        }
        // Caso 2: Nó com apenas um filho
        else if((*raiz)->esquerda == NULL) {
            *raiz = (*raiz)->direita;
            free(aux);
        } else if((*raiz)->direita == NULL) {
            *raiz = (*raiz)->esquerda;
            free(aux);
        }
        // Caso 3: Nó com dois filhos
        else {
            aux = encontrarMaior(&(*raiz)->esquerda);
            aux->esquerda = (*raiz)->esquerda;
            aux->direita = (*raiz)->direita;
            free(*raiz);
            *raiz = aux;
        }
        printf("\nValor removido com sucesso!\n");
    }
}

void preOrdem(No *raiz) {
    if(raiz != NULL) {
        printf("%d ", raiz->valor);
        preOrdem(raiz->esquerda);
        preOrdem(raiz->direita);
    }
}

void emOrdem(No *raiz) {
    if(raiz != NULL) {
        emOrdem(raiz->esquerda);
        printf("%d ", raiz->valor);
        emOrdem(raiz->direita);
    }
}

void posOrdem(No *raiz) {
    if(raiz != NULL) {
        posOrdem(raiz->esquerda);
        posOrdem(raiz->direita);
        printf("%d ", raiz->valor);
    }
}

void imprimirArvore(No *raiz, int nivel) {
    if(raiz != NULL) {
        imprimirArvore(raiz->direita, nivel + 1);
        
        int i; 
		for(i = 0; i < nivel; i++) {
    	printf("    ");
}
        
        printf("%d\n", raiz->valor);
        
        imprimirArvore(raiz->esquerda, nivel + 1);
    }
}

void liberarArvore(No **raiz) {
    if(*raiz != NULL) {
        liberarArvore(&(*raiz)->esquerda);
        liberarArvore(&(*raiz)->direita);
        free(*raiz);
        *raiz = NULL;
    }
}

int main() {
    No *raiz;
    criarArvore(&raiz);
    setlocale(LC_ALL, "Portuguese");
    
    int opcao, valor;
    
    do {
        system("cls");
        printf("---------------------------------------------------------------\n");
		printf("DISCIPLINA: Estrutura de Dados\n");
		printf("Professor: Marco Aurelio Novaes Esteves\n");
		printf("Aluno: Sergio Martins Filho\n");
		printf("Matricula: 1240206591\n");
        printf("========== MENU ==========\n\n");
        printf("1. Inserir valor\n");
        printf("2. Remover valor\n");
        printf("3. Exibir pré-ordem\n");
        printf("4. Exibir em ordem\n");
        printf("5. Exibir pós-ordem\n");
        printf("6. Imprimir árvore\n");
        printf("0. Sair\n\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        
        switch(opcao) {
            case 1:
                printf("\nDigite um valor para inserir: ");
                scanf("%d", &valor);
                inserir(&raiz, valor);
                break;
                
            case 2:
                printf("\nDigite um valor para remover: ");
                scanf("%d", &valor);
                remover(&raiz, valor);
                break;
                
            case 3:
                printf("\nPré-ordem: ");
                preOrdem(raiz);
                printf("\n");
                break;
                
            case 4:
                printf("\nEm ordem: ");
                emOrdem(raiz);
                printf("\n");
                break;
                
            case 5:
                printf("\nPós-ordem: ");
                posOrdem(raiz);
                printf("\n");
                break;
                
            case 6:
                printf("\nÁrvore:\n");
                imprimirArvore(raiz, 0);
                printf("\n");
                break;
                
            case 0:
                liberarArvore(&raiz);
                printf("\nPrograma encerrado.\n");
                break;
                
            default:
                printf("\nOpção inválida!\n");
        }
        
        if(opcao != 0) {
            system("pause");
        }
    } while(opcao != 0);
    
    return 0;
}
