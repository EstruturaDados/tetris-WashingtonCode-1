// Desafio Tetris Stack - Nível Aventureiro
// Objetivo: Implementar um programa em C que simula o gerenciamento de peças no jogo Tetris Stack, utilizando uma fila circular de peças futuras e uma pilha de reserva. Cada peça tem um tipo (como 'I', 'O', 'T', 'L') e um identificador numérico único (id). O jogador poderá visualizar a fila e a pilha, jogar peças, reservar peças para uso posterior e remover peças da reserva.

// Inclusão de bibliotecas necessárias
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
void reservarPeca(Fila *f, Pilha *p, int *proximoId);
void usarPecaReservada(Pilha *p);
void exibirEstadoAtual(Fila *f, Pilha *p);

// Função principal
int main() {
    Fila fila;
    Pilha reserva;
    int proximoId = 0;
    int opcao;
    
    srand(time(NULL));

    // Inicialização da fila e da pilha
    inicializarFila(&fila);
    inicializarPilha(&reserva);

    // Preenchimento inicial (Fila com 5 elementos)
    for (int i = 0; i < MAX_FILA; i++) {
        adicionarAFila(&fila, &proximoId);
    }

    do {
        exibirEstadoAtual(&fila, &reserva);

        printf("Opções de Ação:\n");
        printf("1. Jogar peça\n");
        printf("2. Reservar peça\n");
        printf("3. Usar peça reservada\n");
        printf("0. Sair\n");
        printf("\nOpção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                jogarPeca(&fila, &proximoId);
                break;
            case 2:
                reservarPeca(&fila, &reserva, &proximoId);
                break;
            case 3:
                usarPecaReservada(&reserva);
                break;
            case 0:
                printf("Saindo do programa...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (opcao != 0);

    return 0;
}

// Função inicializar fila
void inicializarFila(Fila *f) {
    f->inicio = 0;
    f->fim = 0;
    f->total = 0;
}

// Função inicializar pilha
void inicializarPilha(Pilha *p) {
    p->topo = -1;
}