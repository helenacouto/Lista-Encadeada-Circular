#include <stdio.h>
#include <stdlib.h>
#include "ListaDinEncadCirc.h"

/* Definicao do tipo lista: oculta de quem usa a biblioteca. */
struct elemento {
    struct aluno dados;
    struct elemento *prox;
};
typedef struct elemento Elem;

/* --- criacao e destruicao ---------------------------------- */

Lista* cria_lista(void) {
    Lista* li = (Lista*) malloc(sizeof(Lista));
    if (li != NULL)
        *li = NULL;
    return li;
}

void libera_lista(Lista* li) {
    if (li == NULL)
        return;
    if ((*li) != NULL) {
        Elem *aux, *no = *li;
        /* para quando o seguinte ao atual e o inicio: uma volta completa */
        while ((*li) != no->prox) {
            aux = no;
            no = no->prox;   /* avanca antes de liberar */
            free(aux);
        }
        free(no);
    }
    free(li);               /* libera o bloco do inicio */
}

/* --- informacoes de estado --------------------------------- */

int tamanho_lista(Lista* li) {
    if (li == NULL || (*li) == NULL)
        return 0;
    int cont = 0;
    Elem* no = *li;
    do {                    /* do-while: o primeiro elemento tem de ser contado */
        cont++;
        no = no->prox;
    } while (no != (*li));
    return cont;
}

int lista_cheia(Lista* li) {
    (void) li;              /* parametro mantido por simetria com as demais */
    return 0;
}

int lista_vazia(Lista* li) {
    if (li == NULL)
        return 1;           /* lista invalida */
    if (*li == NULL)
        return 1;           /* nenhum elemento alocado */
    return 0;
}

/* --- insercao ---------------------------------------------- */

int insere_lista_inicio(Lista* li, struct aluno al) {
    if (li == NULL)
        return 0;
    Elem *no = (Elem*) malloc(sizeof(Elem));
    if (no == NULL)
        return 0;           /* sem memoria: a lista esta cheia */
    no->dados = al;
    if ((*li) == NULL) {    /* lista vazia: o no aponta para si mesmo */
        *li = no;
        no->prox = no;
    } else {
        Elem *aux = *li;
        while (aux->prox != (*li)) {   /* procura o ultimo */
            aux = aux->prox;
        }
        aux->prox = no;
        no->prox = *li;
        *li = no;           /* unica linha que difere da insercao no final */
    }
    return 1;
}

int insere_lista_final(Lista* li, struct aluno al) {
    if (li == NULL)
        return 0;
    Elem *no = (Elem*) malloc(sizeof(Elem));
    if (no == NULL)
        return 0;
    no->dados = al;
    if ((*li) == NULL) {    /* lista vazia: o no aponta para si mesmo */
        *li = no;
        no->prox = no;
    } else {
        Elem *aux = *li;
        while (aux->prox != (*li)) {   /* procura o ultimo */
            aux = aux->prox;
        }
        aux->prox = no;
        no->prox = *li;     /* o inicio nao muda */
    }
    return 1;
}

int insere_lista_ordenada(Lista* li, struct aluno al) {
    if (li == NULL)
        return 0;
    Elem *no = (Elem*) malloc(sizeof(Elem));
    if (no == NULL)
        return 0;
    no->dados = al;
    if ((*li) == NULL) {    /* lista vazia */
        *li = no;
        no->prox = no;
        return 1;
    }
    if ((*li)->dados.matricula > al.matricula) {   /* insercao no inicio */
        Elem *atual = *li;
        while (atual->prox != (*li))               /* procura o ultimo */
            atual = atual->prox;
        no->prox = *li;
        atual->prox = no;
        *li = no;
        return 1;
    }
    /* insercao no meio ou no final: ant acompanha atual uma posicao atras */
    Elem *ant = *li, *atual = (*li)->prox;
    while (atual != (*li) && atual->dados.matricula < al.matricula) {
        ant = atual;
        atual = atual->prox;
    }
    ant->prox = no;
    no->prox = atual;
    return 1;
}

/* --- remocao ----------------------------------------------- */

int remove_lista_inicio(Lista* li) {
    if (li == NULL)
        return 0;
    if ((*li) == NULL)
        return 0;           /* lista vazia */
    if ((*li) == (*li)->prox) {   /* elemento unico: a lista fica vazia */
        free(*li);
        *li = NULL;
        return 1;
    }
    Elem *atual = *li;
    while (atual->prox != (*li))  /* procura o ultimo */
        atual = atual->prox;
    Elem *no = *li;
    atual->prox = no->prox;       /* o ultimo passa a apontar para o segundo */
    *li = no->prox;               /* o segundo passa a ser o inicio */
    free(no);
    return 1;
}

int remove_lista_final(Lista* li) {
    if (li == NULL)
        return 0;
    if ((*li) == NULL)
        return 0;           /* lista vazia */
    if ((*li) == (*li)->prox) {   /* elemento unico: a lista fica vazia */
        free(*li);
        *li = NULL;
        return 1;
    }
    Elem *ant = NULL, *no = *li;
    while (no->prox != (*li)) {   /* procura o ultimo, guardando o anterior */
        ant = no;
        no = no->prox;
    }
    ant->prox = no->prox;         /* o penultimo passa a apontar para o inicio */
    free(no);
    return 1;
}

int remove_lista(Lista* li, int mat) {
    if (li == NULL)
        return 0;
    if ((*li) == NULL)
        return 0;           /* lista vazia */
    Elem *no = *li;
    if (no->dados.matricula == mat) {      /* remocao do inicio */
        if (no == no->prox) {              /* a lista fica vazia */
            free(no);
            *li = NULL;
            return 1;
        } else {
            Elem *ult = *li;
            while (ult->prox != (*li))     /* procura o ultimo */
                ult = ult->prox;
            ult->prox = (*li)->prox;
            *li = (*li)->prox;
            free(no);
            return 1;
        }
    }
    Elem *ant = no;
    no = no->prox;
    /* para ao encontrar a matricula ou ao completar uma volta */
    while (no != (*li) && no->dados.matricula != mat) {
        ant = no;
        no = no->prox;
    }
    if (no == (*li))
        return 0;           /* chave ausente */
    ant->prox = no->prox;
    free(no);
    return 1;
}

/* --- busca ------------------------------------------------- */

int busca_lista_pos(Lista* li, int pos, struct aluno *al) {
    if (li == NULL || (*li) == NULL || pos <= 0)
        return 0;
    Elem *no = *li;
    int i = 1;
    /* para no ultimo elemento ou ao alcancar a posicao desejada */
    while (no->prox != (*li) && i < pos) {
        no = no->prox;
        i++;
    }
    if (i != pos)
        return 0;           /* posicao inexistente */
    else {
        *al = no->dados;
        return 1;
    }
}

int busca_lista_mat(Lista* li, int mat, struct aluno *al) {
    if (li == NULL || (*li) == NULL)
        return 0;
    Elem *no = *li;
    /* para no ultimo elemento ou ao encontrar a matricula */
    while (no->prox != (*li) && no->dados.matricula != mat)
        no = no->prox;
    if (no->dados.matricula != mat)
        return 0;           /* chave ausente */
    else {
        *al = no->dados;
        return 1;
    }
}

/* QUESTÃO 1 */
void imprime_lista(Lista *li) {
    if (li == NULL || (*li) == NULL) return;
    Elem *no = *li;

    do {
        printf("%d ", no->dados.matricula);
        no = no->prox;
    } while (no != *li);
    printf("\n");
}

/* QUESTÃO 2 */
int maior_matricula(Lista *li, int *mat) {
    if (li == NULL || (*li) == NULL) return 0;

    *mat = (*li)->dados.matricula;
    Elem *no = (*li)->prox;

    while(no != (*li)) {
        if (no->dados.matricula > *mat) {
            *mat = no->dados.matricula;
        }
        no = no->prox;
    }

    return 1;
}

/* QUESTÃO 3
O código com defeito apresentado possui dois problemas.
O primeiro é que a função não tem uma seção que verifica
se a lista é válida. O segundo é que como estamos abordando
uma lista circular, nunca teremos um no apontando que o
o próximo é NULL, então rodaria inifinito.

Código corrigido:
*/
int conta_aprovados(Lista *li) {
    if (li == NULL || *li == NULL) return 0;
    Elem* no = *li;

    int cont = 0;
    do {
        float media = (no->dados.n1 + no->dados.n2 + no->dados.n3) / 3;
        if (media >= 7.0) cont++;
        no = no->prox;
    } while (no != *li);
    
    return cont;
}

/* QUESTÃO 4 */
int busca_ciclica(Lista* li, int k, struct aluno *al) {
    if (li == NULL || *li == NULL || k <= 0) return 0;

    int avancos = (k - 1) % tamanho_lista(li);
    Elem *no = *li;
    for (int i = 0; i < avancos; i++)
        no = no->prox;

    *al = no->dados;
    return 1;
}

/* QUESTÃO 5 */
int remove_lista_pos(Lista* li, int pos) {
    if (li == NULL || *li == NULL) return 0;
    if (pos < 1 || pos > tamanho_lista(li)) return 0;

    if (pos == 1) return remove_lista_inicio(li);

    Elem *ant = *li;
    for (int i = 1; i < pos - 1; i++)
        ant = ant->prox;

    Elem *no = ant->prox;
    ant->prox = no->prox;
    free(no);
    return 1;
}

/* QUESTÃO 6
Resposta 1: O custo é O(k). A função só avança *li k vezes, sem procurar o
último elemento e sem alterar nenhum prox, porque o fim já está ligado ao
início. Por isso, para k pequeno ela custa bem menos que percorrer a lista
inteira.

Resposta 2: Na lista não circular, o último aponta para NULL, então seria
preciso religar a estrutura. Teria de percorrer até o k-ésimo elemento,
ligar o último ao primeiro e fazer o k-ésimo apontar para NULL. Como achar
o último exige percorrer a lista toda, o custo é O(N) mesmo com k pequeno.
*/
int rotaciona_lista(Lista* li, int k) {
    if (li == NULL || *li == NULL || k < 0) return 0;

    for (int i = 0; i < k; i++) {
        *li = (*li)->prox;
    }
    return 1;
}

/* QUESTÃO 7
Resposta: O custo seria O(1). Com (*li) guardando o último elemento de cada
lista, os dois últimos são acessados direto e os primeiros são os prox
deles. Basta trocar dois ponteiros (o último de li1 passa a apontar para o
primeiro de li2, e o último de li2 para o primeiro de li1) e atualizar *li
para o último de li2, sem nenhum percurso.
*/
int concatena_listas(Lista* li, Lista* li2) {
    if (li == NULL || li2 == NULL) return 0;
    
    if (*li2 == NULL) return 1;
    if (*li == NULL) {
        *li = *li2;
        *li2 = NULL;
        return 1;
    }

    Elem* no = *li2;
    while(no->prox != *li2) {
        no = no->prox;
    }
    no->prox = *li;

    no = no->prox;
    while(no->prox != *li) {
        no = no->prox;
    }
    no->prox = *li2;
    *li2 = NULL;

    return 1;
}

/* QUESTÃO 8 */
int josephus(Lista* li, int k, int *sobrevivente) {
    if (li == NULL || *li == NULL || k <= 0) return 0;

    Elem *no = *li, *ant = *li;
    while (ant->prox != *li)
        ant = ant->prox;

    while (no->prox != no) {
        for (int i = 1; i < k; i++) {
            ant = no;
            no = no->prox;
        }
        ant->prox = no->prox;
        free(no);
        no = ant->prox;
    }
    *sobrevivente = no->dados.matricula;
    free(no);
    *li = NULL;
    return 1;
}