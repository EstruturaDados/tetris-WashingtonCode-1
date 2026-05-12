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

// Função remover da fila
Peca removerDaFila(Fila *f) {
    Peca p = f->itens[f->inicio];
    f->inicio = (f->inicio + 1) % MAX_FILA;
    f->total--;
    return p;
}

// Função jogar peça (Dequeue)
void jogarPeca(Fila *f, int *proximoId) {
    if (f->total > 0) {
        Peca p = removerDaFila(f);
        printf("\n[JOGADA] Peça [%c %d] removida da fila e usada no jogo.\n", p.nome, p.id);
        // Mantém a fila cheia
        adicionarAFila(f, proximoId);
    } else {
        printf("\nFila vazia!\n");
    }
}

// Função reservar peça
void reservarPeca(Fila *f, Pilha *p, int *proximoId) {
    if (p->topo < MAX_PILHA - 1) {
        if (f->total > 0) {
            Peca pecaParaReserva = removerDaFila(f);
            p->topo++;
            p->itens[p->topo] = pecaParaReserva;
            printf("\n[RESERVA] Peça [%c %d] movida para a reserva.\n", pecaParaReserva.nome, pecaParaReserva.id);
            // Mantém a fila cheia
            adicionarAFila(f, proximoId);
        }
    } else {
        printf("\n[ERRO] Pilha de reserva cheia (Limite: %d)!\n", MAX_PILHA);
    }
}

// Função usar peça reservada
void usarPecaReservada(Pilha *p) {
    if (p->topo >= 0) {
        Peca p_uso = p->itens[p->topo];
        p->topo--;
        printf("\n[USO] Peça [%c %d] saiu da reserva para o jogo.\n", p_uso.nome, p_uso.id);
    } else {
        printf("\n[ERRO] Pilha de reserva vazia!\n");
    }
}

// Função exibir estado atual
void exibirEstadoAtual(Fila *f, Pilha *p) {
    printf("\n---------------------------------------------------\n");
    printf("Estado atual:\n");
    
    // Fila de peças
    printf("Fila de peças: ");
    int idx = f->inicio;
    for (int i = 0; i < f->total; i++) {
        printf("[%c %d] ", f->itens[idx].nome, f->itens[idx].id);
        idx = (idx + 1) % MAX_FILA;
    }

    // Pilha de reserva
    printf("\nPilha de reserva (Topo -> Base): ");
    if (p->topo == -1) {
        printf("[Vazia]");
    } else {
        for (int i = p->topo; i >= 0; i--) {
            printf("[%c %d] ", p->itens[i].nome, p->itens[i].id);
        }
    }
    printf("\n---------------------------------------------------\n");
}