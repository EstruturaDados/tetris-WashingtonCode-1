// Desafio Tetris Stack - Nível Mestre
// Objetivo: Desenvolver um gerenciador de peças que usa duas estruturas de dados: uma fila circular com capacidade para 5 peças e uma pilha com capacidade para 3 peças. O sistema irá executar ações estratégicas com elas, como jogar, reservar, recuperar e realizar uma troca em bloco entre as peças da fila e as da pilha.

// Inclusão das bibliotecas necessárias
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Definição de constantes
#define MAX_FILA 5
#define MAX_PILHA 3

// Estrutura para representar uma peça
typedef struct {
    char nome; // 'I', 'O', 'T', 'L'
    int id;    // Identificador único
} Peca;

// Estrutura da Fila Circular (Peças Futuras)
typedef struct {
    Peca itens[MAX_FILA];
    int inicio;
    int fim;
    int total;
} Fila;

// Estrutura da Pilha (Reserva)
typedef struct {
    Peca itens[MAX_PILHA];
    int topo;
} Pilha;

// --- Protótipos das Funções ---
void inicializarFila(Fila *f);
void inicializarPilha(Pilha *p);
Peca gerarPeca(int *proximoId);
void adicionarAFila(Fila *f, int *proximoId);
Peca removerDaFila(Fila *f);
void jogarPeca(Fila *f, int *proximoId);
void reservarPeca(Fila *f, Pilha *p, int *proximoId); // Move da fila para pilha
void usarPecaReservada(Pilha *p);                      // Remove do topo da pilha
void trocarPecaAtual(Fila *f, Pilha *p);
void trocaMultipla(Fila *f, Pilha *p);
void exibirEstadoAtual(Fila *f, Pilha *p);

int main() {
    Fila fila;
    Pilha reserva;
    int proximoId = 0;
    int opcao;

    srand(time(NULL));

    // Inicialização da fila e da pilha
    inicializarFila(&fila);
    inicializarPilha(&reserva);

    // Inicialização da fila com 5 peças
    for (int i = 0; i < MAX_FILA; i++) {
        adicionarAFila(&fila, &proximoId);
    }

    do {
        exibirEstadoAtual(&fila, &reserva);

        printf("Opções disponíveis:\n");
        printf("1. Jogar peça da frente da fila\n");
        printf("2. Enviar peça da fila para a pilha de reserva\n");
        printf("3. Usar peça da pilha de reserva\n");
        printf("4. Trocar peça da frente da fila com o topo da pilha\n");
        printf("5. Trocar os 3 primeiros da fila com as 3 peças da pilha\n");
        printf("0. Sair\n");
        printf("\nOpção escolhida: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: jogarPeca(&fila, &proximoId); break;
            case 2: reservarPeca(&fila, &reserva, &proximoId); break;
            case 3: usarPecaReservada(&reserva); break;
            case 4: trocarPecaAtual(&fila, &reserva); break;
            case 5: trocaMultipla(&fila, &reserva); break;
            case 0: printf("Encerrando o programa...\n"); break;
            default: printf("\nOpção inválida!\n");
        }
    } while (opcao != 0);

    return 0;
}

// --- Implementação das funções ---

// Função inicializar fila
void inicializarFila(Fila *f) {
    f->inicio = 0; f->fim = 0; f->total = 0;
}

// Função inicializar pilha
void inicializarPilha(Pilha *p) {
    p->topo = -1;
}

// Função gerar peça
Peca gerarPeca(int *proximoId) {
    char tipos[] = {'I', 'O', 'T', 'L'};
    Peca nova;
    nova.nome = tipos[rand() % 4];
    nova.id = (*proximoId)++;
    return nova;
}

// Função adicionar a fila
void adicionarAFila(Fila *f, int *proximoId) {
    if (f->total < MAX_FILA) {
        f->itens[f->fim] = gerarPeca(proximoId);
        f->fim = (f->fim + 1) % MAX_FILA;
        f->total++;
    }
}