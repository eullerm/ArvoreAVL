#ifndef ARVORE_LIBRARY_H
#define ARVORE_LIBRARY_H

#include <stdio.h>
#include <stdlib.h>

typedef struct sNoAVL {
    int chave;
    int fb;
    struct sNoAVL *esq;
    struct sNoAVL *dir;
} TNoAVL;

typedef struct tp{

    TNoAVL *info;
    struct tp *prox;

}TP;

TNoAVL *inicializa();

void imprime(TNoAVL *no, int tab);

TNoAVL *rotacao_direita(TNoAVL *p);

TNoAVL *rotacao_esquerda(TNoAVL *p);

TNoAVL *rotacao_dupla_direita(TNoAVL *p);

TNoAVL *rotacao_dupla_esquerda(TNoAVL *p);

TNoAVL *insere(TNoAVL *p, int chave, int *flag);

int contaNiveis(TNoAVL *raiz);

int contaNos(TNoAVL *raiz);

int nivel(TNoAVL *raiz, int x);

TP *cria_p();

void push(TP *p, TNoAVL *a);

void pop(TP *p);

TNoAVL *peek(TP *p);

int p_vazia(TP *p);

void esvazia(TP *p);

int compara_valor(TNoAVL *a, TP *p);

//Imprime em pos ordem usando pilha.
void pos_ordem(TNoAVL *arv);

//Imprime em ordem simetrica usando pilha.
void ordem_simetrica(TNoAVL *arv);

//Usado para arvores nao AVL-------------//
void busca_maior(TNoAVL *raiz, int *m); //
int maior_valor(TNoAVL *raiz);         //
//------------------------------------//

#endif