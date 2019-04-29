#include "arvore-binaria.h"

TNoAVL *inicializa() {
    return NULL;
}

void imprime(TNoAVL *no, int tab) {
    for (int i = 0; i < tab; i++) {
        printf("-");
    }
    if (no != NULL) {
        printf("%d (fb = %d)\n", no->chave, no->fb);
        imprime(no->esq, tab + 2);
        printf("\n");
        imprime(no->dir, tab + 2);
    } else printf("vazio");
}

TNoAVL *rotacao_direita(TNoAVL *p) {
    //Faz rotação de p para direita e retorna ponteiro para a nova raiz da subárvore afetada
    TNoAVL * aux = NULL ;
    aux = p-> esq ;
    p-> esq = aux-> dir ;
    aux-> dir = p;
    if((aux->esq && aux->dir )||(!aux->esq && !aux->dir)) aux->fb=0;
    else if(!aux->esq && aux->dir) aux->fb = 1;
    else if(aux->esq && !aux->dir) aux->fb = -1;

    if((p->esq && p->dir )||(!p->esq && !p->dir)) p->fb=0;
    else if(!p->esq && p->dir) p->fb = 1;
    else if(p->esq && !p->dir) p->fb = -1;
    return aux;
}

TNoAVL *rotacao_esquerda(TNoAVL *p) {
    //Faz rotação de p para esquerda e retorna ponteiro para a nova raiz da subárvore afetada
    TNoAVL * aux = NULL ;
    aux = p-> dir ;
    p-> dir = aux-> esq ;
    aux->esq = p;

    if((aux->esq && aux->dir )||(!aux->esq && !aux->dir)) aux->fb=0;
    else if(!aux->esq && aux->dir) aux->fb = 1;
    else if(aux->esq && !aux->dir) aux->fb = -1;

    if((p->esq && p->dir )||(!p->esq && !p->dir)) p->fb=0;
    else if(!p->esq && p->dir) p->fb = 1;
    else if(p->esq && !p->dir) p->fb = -1;

    return aux;
}

TNoAVL *rotacao_dupla_direita(TNoAVL *p) {
    //rotação esquerda-direta
    //Faz rotação de p->esq para esquerda, e de p para direita, e retorna ponteiro para nova raiz da subárvore afetada
    p->esq = rotacao_esquerda(p->esq);
    p = rotacao_direita(p);
    return p;

}

TNoAVL *rotacao_dupla_esquerda(TNoAVL *p) {
    //rotação direita-esquerda
    //Faz rotação de p->dir para direita, e de p para esquerda, e retorna ponteiro para nova raiz da subárvore afetada
    p->dir = rotacao_direita(p->dir);
    p = rotacao_esquerda(p);

    return p;
}

TNoAVL *insere(TNoAVL *p, int chave, int *flag) {
    /* Insere no em uma árvore AVL, onde p representa a raiz da árvore,
    chave, a chave a ser inserida e flag é um booleano que indica se é necessário propagar operação de cálculo de fb */
    if (p == NULL) {
        p = (TNoAVL *) malloc(sizeof(TNoAVL));
        p->chave = chave;
        p->esq = NULL;
        p->dir = NULL;
        p->fb = 0;
        *flag = 1;
        printf("\nInseriu %d", p->chave);
        return p;

    } else{

        TNoAVL *aux = p;

        if(chave > p->chave){

            aux->dir = insere(aux->dir, chave, flag);
            if(flag){
                switch (aux->fb) {
                    case -1:
                        aux->fb = 0;
                        *flag = 0;
                        break;
                    case 0:
                        aux->fb = 1;
                        break;
                    case 1:

                        if (aux->dir->fb == -1) aux = rotacao_dupla_esquerda(aux);
                        else if(aux->dir->fb == 1) aux = rotacao_esquerda(aux);

                        *flag = 0;
                        break;
                }
            }
            return aux;
        }
        else{
            aux->esq = insere(aux->esq, chave, flag);
            if(flag){
                switch (aux->fb) {
                    case -1:
                        if (aux->esq->fb == -1) aux = rotacao_direita(aux);
                        else if(aux->esq->fb == 1) aux = rotacao_dupla_direita(aux);
                        *flag = 0;
                        break;
                    case 0:
                        aux->fb = -1;
                        break;
                    case 1:
                        aux->fb = 0;
                        *flag = 0;
                        break;
                }
            }
            return aux;
        }
    }
}

int contaNiveis(TNoAVL *raiz){
    if(!raiz) return 0;
    int esq = 1;
    int dir = 1;
    if(raiz->esq) esq+=contaNiveis(raiz->esq);
    if(raiz->dir) dir+=contaNiveis(raiz->dir);

    if (esq>=dir) return esq;
    else return dir;
}

int contaNos(TNoAVL *raiz){
    if(!raiz) return 0;
    int cont=1;
    if (raiz->esq) cont+=contaNos(raiz->esq);
    if (raiz->dir) cont+=contaNos(raiz->dir);

    return cont;
}

int nivel(TNoAVL *raiz, int x) {

    if (!raiz) return 0;
    int cont = 1;
    if (x < raiz->info) {
        if(nivel(raiz->esq, x) != 0) cont += nivel(raiz->esq, x);
        else cont = 0;
        return cont;
    } else if (x > raiz->info) {
        if(nivel(raiz->dir, x) != 0) cont += nivel(raiz->dir, x);
        else cont = 0;
        return cont;
    } else if (x == raiz->info){
        return 1;
    }
}

TP *cria_p(){
    TP *p=(TP*)malloc(sizeof(TP));
    p->prox=NULL;
    return p;
}

void push(TP *p, TNoAVL *a){
    TP *novo=(TP*) malloc(sizeof(TP));
    novo->info=a;
    novo->prox=p->prox;
    p->prox=novo;
}

void pop(TP *p){
    TP *tmp = p->prox;
    p->prox = p->prox->prox;
    tmp->prox = NULL;
    free(tmp);
}

TNoAVL *peek(TP *p){
    return p->prox->info;
}

int p_vazia(TP *p){

    if(!p->prox) return 1;
    else return 0;

}

void esvazia(TP *p) {
    TP *aux;
    while (p->prox != NULL) {
        aux = p->prox;
        p->prox = p->prox->prox;
        aux->prox = NULL;
        free(aux);
    }
}

int compara_valor(TNoAVL *a, TP *p){
    TP *aux=p->prox;

    while(aux){
        if(aux->info==a) return 1;
        aux=aux->prox;
    }
    return 0;

}

//Imprime em pos ordem usando pilha.
void pos_ordem(TNoAVL *arv){

    TNoAVL *aux=arv;
    TNoAVL *aux2;
    TP *p=cria_p();

    if(arv->esq || arv->dir) {
        do {

            while (aux->esq != NULL && !compara_valor(aux->esq, p)) {
                aux2 = aux;
                aux = aux->esq;
            }

            if (aux->dir != NULL && !compara_valor(aux->dir, p)) aux = aux->dir;
            else {
                push(p, aux);
                aux = arv;
                if (p->prox->info != arv) printf("%d ", p->prox->info->info);
                else pop(p);
            }

        } while (!compara_valor(arv->dir, p));

        esvazia(p);
    }

    printf("%d", arv->info);
}

//Imprime em ordem simetrica usando pilha.
void ordem_simetrica(TNoAVL *arv) {
    TP *p=cria_p();

    push(p, arv);

    TNoAVL *aux;
    while(!p_vazia(p)){
        aux=peek(p);

        pop(p);

        if(aux!=NULL){
            push(p, aux);
            push(p, aux->esq);
        }
        else{
            if(!p_vazia(p)) {
                aux = peek(p);
                pop(p);
                printf("%d ", aux->info);
                push(p, aux->dir);
            }
        }
    }
    esvazia(p);
}


//As duas proximas funções sao usadas para arvores não AVL
void busca_maior(TNoAVL *raiz, int *m){
    if(!raiz)return;
    if(raiz->info > (*m))
        (*m) = raiz->info;
    busca_maior(raiz->dir, m);
    busca_maior(raiz->esq, m);
}
int maior_valor(TNoAVL *raiz){
    if(raiz){
        int m=raiz->info;
        busca_maior(raiz, &m);
        return m;
    }
}
//-----------------------------------//