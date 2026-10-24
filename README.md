# Lista de exercícios: Lista dinâmica encadeada circular

Resolução da lista de exercícios da **Aula 07** da disciplina **Estrutura de Dados**
(Departamento de Informática, UFPB), sobre a lista dinâmica encadeada circular, em C.

## Sobre a atividade

Uma atividade da disciplina é uma **lista de exercícios** construída sobre uma biblioteca
que o professor apresenta em aula. Em vez de escrever um programa do zero, o trabalho é
**estender a biblioteca**: cada questão pede uma nova função, e todas seguem as mesmas regras.

1. A função é escrita dentro do arquivo `.c` da biblioteca.
2. O protótipo é acrescentado ao arquivo `.h`.
3. A função é testada a partir do `main.c`.
4. Nenhuma função pode usar a comparação de `prox` com `NULL` como critério de parada,
   porque em uma lista circular o último elemento aponta de volta para o primeiro.

As funções precisam ficar dentro do `.c` porque o tipo da lista é **opaco**: a `struct elemento`
só existe no `.c`, e por isso nenhuma função que percorre os nós (usando `dados` e `prox`)
compila fora dele.

### Questões

| Questão | Função | O que faz |
|---|---|---|
| 1 | `imprime_lista` | Percorre a lista exatamente uma volta e imprime a matrícula de cada aluno, sem repetir nenhum |
| 2 | `maior_matricula` | Escreve em `*mat` a maior matrícula da lista, em uma única volta e sem vetor auxiliar |
| 3 | `conta_aprovados` | Análise de uma função com defeito e a versão corrigida, que conta alunos com média maior ou igual a 7,0 (resposta escrita em comentário no `.c`) |
| 4 | `busca_ciclica` | Copia o k-ésimo elemento percorrendo a lista ciclicamente, com k possivelmente maior que o tamanho e custo que não cresce com k |
| 5 | `remove_lista_pos` | Remove o elemento de uma posição, tratando início, final e elemento único |
| 6 | `rotaciona_lista` | Avança o início da lista em k posições, sem alocar, liberar nem religar nenhum nó |
| 7 | `concatena_listas` | Anexa a segunda lista ao final da primeira apenas religando ponteiros, deixando a segunda vazia e válida |
| 8 | `josephus` | Resolve o problema de Josephus removendo e liberando de fato cada nó eliminado |

As respostas escritas pedidas no enunciado (por exemplo, o custo da rotação e da
concatenação) estão em comentários no `ListaDinEncadCirc.c`, junto de cada questão.

## Biblioteca base

A biblioteca de partida (`ListaDinEncadCirc.h` e `ListaDinEncadCirc.c`) é do
**Prof. Daniel Faustino Lacerda de Souza** e foi copiada, sem alterações, da pasta
`03-lista-dinamica-encadeada-circular` do repositório da disciplina:
[github.com/Ensino-UFPB/exemplosed1](https://github.com/Ensino-UFPB/exemplosed1).

Ela traz criação e destruição da lista, inserção (início, final e ordenada), remoção
(início, final e por matrícula) e busca (por posição e por matrícula). O que foi
acrescentado por mim está marcado nos arquivos:

- no `.h`, pela seção `ATIVIDADE`;
- no `.c`, pelos comentários `QUESTÃO N`, no final do arquivo.

## Organização do repositório

```
.
├── ListaDinEncadCirc.h     interface: tipo opaco e protótipos (base do professor + atividade)
├── ListaDinEncadCirc.c     implementação: base do professor + funções das questões
├── main.c                  programa de testes das questões
├── Makefile                compilação separada dos módulos
└── README.md
```

## Como compilar e executar

```bash
make        # gera o executável ./teste
./teste     # executa os testes
make clean  # remove os .o e o executável
```

Sem o `make`, a compilação manual é:

```bash
gcc -Wall -Wextra -std=c11 -o teste ListaDinEncadCirc.c main.c
```

O único requisito é um compilador C com suporte a C11 (`gcc` ou `clang`). Para procurar
vazamentos de memória nas funções que alocam ou liberam nós:

```bash
valgrind --leak-check=full ./teste
```

## Como os testes funcionam

O `main.c` tem um bloco por questão. Cada bloco monta uma lista, imprime o estado dela
antes e depois da operação, no formato `inicio -> [12] -> [16] -> volta ao inicio`, e
confere casos de borda (lista vazia, `NULL`, elemento único, primeiro e último). Ao lado
de cada resultado aparece o valor esperado, para a conferência ser imediata.

O `main.c` usa apenas o que está declarado no `.h`: em nenhum ponto ele acessa os campos
`dados` ou `prox`.

## Convenções

- **Tipo opaco:** a `struct` interna é definida apenas no `.c`.
- **Compilação limpa:** o código compila com `gcc -Wall -Wextra -std=c11` sem avisos.
- **Retorno:** inserção e remoção devolvem `1` em caso de sucesso e `0` caso contrário.
- **Comentários sem acentuação** nos arquivos `.c` e `.h`, para evitar problemas de
  codificação em editores com outra página de código. Os arquivos `README.md` usam
  acentuação normal.
- **Nomes em português**, iguais aos dos slides e das listas de exercícios.

## Referências

- BACKES, A. R. *Algoritmos e estruturas de dados em linguagem C*. Rio de Janeiro: LTC, 2023.
- TENENBAUM, A. M.; LANGSAM, Y.; AUGENSTEIN, M. J. *Estruturas de dados usando C*. São Paulo: Makron Books, 1995.
- CORMEN, T. H. et al. *Algoritmos: teoria e prática*. 3. ed. Rio de Janeiro: Elsevier, 2012.

## Autoria

Atividade resolvida por Helena Couto, estudante de Ciência de Dados e Inteligência
Artificial na UFPB. A biblioteca base e o enunciado da lista são do Prof. Daniel Faustino
Lacerda de Souza.