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

// Função remover da fila
Peca removerDaFila(Fila *f) {
    Peca p = f->itens[f->inicio];
    f->inicio = (f->inicio + 1) % MAX_FILA;
    f->total--;
    return p;
}

// Função jogar peça
void jogarPeca(Fila *f, int *proximoId) {
    if (f->total > 0) {
        Peca p = removerDaFila(f);
        printf("\n[AÇÃO] Você jogou a peça [%c %d]!\n", p.nome, p.id);
        adicionarAFila(f, proximoId);
    }
}

// Função reservar peça
void reservarPeca(Fila *f, Pilha *p, int *proximoId) {
    if (p->topo < MAX_PILHA - 1) {
        Peca p_da_fila = removerDaFila(f);
        p->topo++;
        p->itens[p->topo] = p_da_fila;
        printf("\n[AÇÃO] Peça [%c %d] movida para a reserva.\n", p_da_fila.nome, p_da_fila.id);
        adicionarAFila(f, proximoId);
    } else {
        printf("\n[AVISO] Pilha de reserva cheia!\n");
    }
}

// Função usar peça reservada
void usarPecaReservada(Pilha *p) {
    if (p->topo >= 0) {
        Peca p_reserva = p->itens[p->topo];
        p->topo--;
        printf("\n[AÇÃO] Peça reservada [%c %d] utilizada!\n", p_reserva.nome, p_reserva.id);
    } else {
        printf("\n[AVISO] Não há peças na reserva!\n");
    }
}

// Função trocar peça atual
void trocarPecaAtual(Fila *f, Pilha *p) {
    if (f->total > 0 && p->topo >= 0) {
        Peca temp = f->itens[f->inicio];
        f->itens[f->inicio] = p->itens[p->topo];
        p->itens[p->topo] = temp;
        printf("\n[AÇÃO] Troca realizada entre a frente da fila e o topo da reserva!\n");
    } else {
        printf("\n[ERRO] Operação NÃO REALIZADA: fila ou reserva vazia.\n");
    }
}

// Função troca multipla (alterna as 3 primeiras da fila com as 3 da pilha)
void trocaMultipla(Fila *f, Pilha *p) {
    if (f->total >= 3 && p->topo >= 2) {
        for (int i = 0; i < 3; i++) {
            int idxFila = (f->inicio + i) % MAX_FILA;
            int idxPilha = p->topo - i;

            Peca temp = f->itens[idxFila];
            f->itens[idxFila] = p->itens[idxPilha];
            p->itens[idxPilha] = temp;
        }
        printf("\n[AÇÃO] Troca múltipla de 3 peças concluída!\n");
    } else {
        printf("\n[ERRO] Quantidade insuficiente de peças para troca múltipla (mínimo 3 em cada).\n");
    }
}

// Função exibir estado atual
void exibirEstadoAtual(Fila *f, Pilha *p) {
    printf("\n---------------------------------------------------\n");
    printf("ESTADO ATUAL\n");
    printf("Fila de peças: ");
    int idx = f->inicio;
    for (int i = 0; i < f->total; i++) {
        printf("[%c %d] ", f->itens[idx].nome, f->itens[idx].id);
        idx = (idx + 1) % MAX_FILA;
    }
    printf("\nPilha de reserva (Topo -> Base): ");
    if (p->topo == -1) printf("[Vazia]");
    else {
        for (int i = p->topo; i >= 0; i--) {
            printf("[%c %d] ", p->itens[i].nome, p->itens[i].id);
        }
    }
    printf("\n---------------------------------------------------\n");
}