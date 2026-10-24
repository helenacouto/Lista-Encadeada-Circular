#include <stdio.h>
#include "ListaDinEncadCirc.h"

static struct aluno mk(int matricula, float n1, float n2, float n3) {
    struct aluno a;
    a.matricula = matricula;
    snprintf(a.nome, sizeof(a.nome), "Aluno %d", matricula);
    a.n1 = n1; a.n2 = n2; a.n3 = n3;
    return a;
}

/* Imprime a lista usando apenas a interface publica:
   inicio -> [12] -> [16] -> volta ao inicio */
static void imprime(const char *rotulo, Lista *li) {
    int i, n = tamanho_lista(li);
    struct aluno a;
    printf("  %-22s tam=%d: ", rotulo, n);
    if (n == 0) {
        printf("(vazia)\n");
        return;
    }
    printf("inicio ->");
    for (i = 1; i <= n; i++) {
        busca_lista_pos(li, i, &a);
        printf(" [%d] ->", a.matricula);
    }
    printf(" volta ao inicio\n");
}

/* Monta uma lista com as matriculas dadas, inserindo no final. */
static Lista* monta(const int *mats, int n) {
    Lista *li = cria_lista();
    for (int i = 0; i < n; i++)
        insere_lista_final(li, mk(mats[i], 0, 0, 0));
    return li;
}

static void titulo(const char *t) {
    printf("\n%s\n", t);
}

int main(void) {
    Lista *li, *li2;

    /* ---------- Questao 1 ---------- */
    titulo("Q1 - imprime_lista");
    {
        int m4[] = {12, 16, 23, 40};
        int m1[] = {12};
        li = monta(m4, 4);
        printf("  esperado: 12 16 23 40\n  obtido:   ");
        imprime_lista(li);
        libera_lista(li);

        li = monta(m1, 1);
        printf("  um elemento, esperado: 12\n  obtido:   ");
        imprime_lista(li);
        libera_lista(li);

        li = cria_lista();
        printf("  vazia, esperado nada: <");
        imprime_lista(li);
        printf(">\n");
        libera_lista(li);
        printf("  NULL,  esperado nada: <");
        imprime_lista(NULL);
        printf(">\n");
    }

    /* ---------- Questao 2 ---------- */
    titulo("Q2 - maior_matricula");
    {
        int m[] = {5, 99, 7};
        int x = -1, r;
        li = monta(m, 3);
        imprime("lista", li);
        r = maior_matricula(li, &x);
        printf("  devolve %d, *mat = %d (esperado 1 e 99)\n", r, x);
        libera_lista(li);

        li = cria_lista();
        x = -1;
        r = maior_matricula(li, &x);
        printf("  vazia: devolve %d, *mat = %d (esperado 0 e -1)\n", r, x);
        libera_lista(li);
        printf("  NULL:  devolve %d (esperado 0)\n", maior_matricula(NULL, &x));
    }

    /* ---------- Questao 3 ---------- */
    titulo("Q3 - conta_aprovados (medias 8.00, 5.00, 7.00, 6.67)");
    {
        li = cria_lista();
        insere_lista_final(li, mk(12, 8, 8, 8));
        insere_lista_final(li, mk(16, 5, 6, 4));
        insere_lista_final(li, mk(23, 7, 7, 7));
        insere_lista_final(li, mk(40, 9, 4, 7));
        imprime("lista", li);
        printf("  aprovados: %d (esperado 2)\n", conta_aprovados(li));
        libera_lista(li);

        li = cria_lista();
        printf("  lista vazia: %d (esperado 0)\n", conta_aprovados(li));
        libera_lista(li);
    }

    /* ---------- Questao 4 ---------- */
    titulo("Q4 - busca_ciclica em [12, 16, 23, 40]");
    {
        int m[] = {12, 16, 23, 40};
        int ks[]  = {1,  4,  5,  7,  1000, 0};
        int esp[] = {12, 40, 12, 23, 40,   0};   /* 0 = busca deve falhar */
        struct aluno a;
        li = monta(m, 4);
        imprime("lista", li);
        for (int i = 0; i < 6; i++) {
            int r = busca_ciclica(li, ks[i], &a);
            if (r)
                printf("  k=%-4d -> %d (esperado %d)\n", ks[i], a.matricula, esp[i]);
            else
                printf("  k=%-4d -> invalido (esperado %s)\n", ks[i],
                       esp[i] == 0 ? "invalido" : "um aluno");
        }
        libera_lista(li);
    }

    /* ---------- Questao 5 ---------- */
    titulo("Q5 - remove_lista_pos em [10, 20, 30, 40, 50]");
    {
        int m[] = {10, 20, 30, 40, 50};
        li = monta(m, 5);
        imprime("antes", li);
        remove_lista_pos(li, 3);
        imprime("pos 3 (meio)", li);
        remove_lista_pos(li, 4);
        imprime("pos 4 (ultima)", li);
        remove_lista_pos(li, 1);
        imprime("pos 1 (primeira)", li);
        printf("  pos 9 devolve %d (esperado 0)\n", remove_lista_pos(li, 9));
        remove_lista_pos(li, 2);
        imprime("pos 2 (sobra 1)", li);
        remove_lista_pos(li, 1);
        imprime("pos 1 (unico)", li);
        libera_lista(li);
    }

    /* ---------- Questao 6 ---------- */
    titulo("Q6 - rotaciona_lista em [12, 16, 23, 40]");
    {
        int m[] = {12, 16, 23, 40};
        li = monta(m, 4);
        imprime("antes", li);
        rotaciona_lista(li, 1);
        imprime("k = 1", li);
        rotaciona_lista(li, 4);
        imprime("k = 4 (volta completa)", li);
        printf("  k = -1 devolve %d (esperado 0)\n", rotaciona_lista(li, -1));
        libera_lista(li);
    }

    /* ---------- Questao 7 ---------- */
    titulo("Q7 - concatena_listas");
    {
        int a[] = {1, 2};
        int b[] = {3, 4};
        li = monta(a, 2);
        li2 = monta(b, 2);
        imprime("li1 antes", li);
        imprime("li2 antes", li2);
        printf("  devolve %d (esperado 1)\n", concatena_listas(li, li2));
        imprime("li1 depois", li);
        imprime("li2 depois", li2);
        libera_lista(li);
        libera_lista(li2);

        li = cria_lista();
        li2 = monta(b, 2);
        concatena_listas(li, li2);
        imprime("li1 vazia: li1", li);
        imprime("li1 vazia: li2", li2);
        libera_lista(li);
        libera_lista(li2);

        li = monta(a, 2);
        li2 = cria_lista();
        concatena_listas(li, li2);
        imprime("li2 vazia: li1", li);
        libera_lista(li);
        libera_lista(li2);
    }

    /* ---------- Questao 8 ---------- */
    titulo("Q8 - josephus");
    {
        int m[] = {1, 2, 3, 4, 5, 6, 7};
        int u[] = {8};
        int s = -1, r;
        li = monta(m, 7);
        imprime("antes", li);
        r = josephus(li, 3, &s);
        printf("  k=3 devolve %d, sobrevivente %d (esperado 1 e 4)\n", r, s);
        imprime("depois", li);
        libera_lista(li);

        li = monta(u, 1);
        r = josephus(li, 3, &s);
        printf("  um elemento: devolve %d, sobrevivente %d (esperado 1 e 8)\n", r, s);
        libera_lista(li);

        li = monta(m, 7);
        printf("  k=0 devolve %d (esperado 0)\n", josephus(li, 0, &s));
        imprime("lista intacta", li);
        libera_lista(li);
    }

    printf("\n");
    return 0;
}