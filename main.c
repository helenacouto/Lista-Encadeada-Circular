#include <stdio.h>
#include "ListaDinEncadCirc.h"

static struct aluno mk(int mat, float n1, float n2, float n3) {
    struct aluno a;
    a.matricula = mat;
    snprintf(a.nome, sizeof(a.nome), "Aluno %d", mat);
    a.n1 = n1; a.n2 = n2; a.n3 = n3;
    return a;
}

int main(void) {
    Lista *li = cria_lista();
    insere_lista_final(li, mk(12, 8, 8, 8));
    insere_lista_final(li, mk(16, 5, 6, 4));
    insere_lista_final(li, mk(23, 7, 7, 7));
    insere_lista_final(li, mk(40, 9, 4, 7));

    printf("Lista inicial: ");
    imprime_lista(li);
    
    int x;
    maior_matricula(li, &x);
    printf("maior_matricula(li, &x) -> %d\n", x);

    printf("conta_aprovados(li) -> %d\n", conta_aprovados(li));

    struct aluno a;
    busca_ciclica(li, 7, &a);
    printf("k=7: %d\n", a.matricula);

    remove_lista_pos(li, 2);
    printf("remove_lista_pos(li, 2) -> ");
    imprime_lista(li);

    rotaciona_lista(li, 1);
    imprime_lista(li);

    Lista *li2 = cria_lista();
    insere_lista_final(li2, mk(50, 0, 0, 0));
    insere_lista_final(li2, mk(60, 0, 0, 0));
    concatena_listas(li, li2);
    printf("concatena_listas(li, li2) -> ");
    imprime_lista(li); 

    josephus(li, 3, &x);
    printf("sobrevivente: %d\n", x);

    libera_lista(li);
    libera_lista(li2);
    return 0;
}