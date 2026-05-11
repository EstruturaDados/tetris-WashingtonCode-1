// Desafio Tetris Stack - Nível Novato
// Objetivo: Desenvolver uma estrutura de controle de peças do jogo, incluindo a implementação do sistema de fila de peças futuras, verificando se as regras de entrada, saída e troca estão funcionando.
// Descrição: Agora, você implementará um programa em C que simula a fila de peças futuras do Tetris Stack. As peças têm um tipo (como 'I', 'O', 'T', 'L’), que representa suas formas e um identificador numérico (id) exclusivo. O programa oferecerá ao jogador a opção de visualizar a fila, jogar uma peça (remoção da frente) ou adicionar uma nova peça ao final da fila.

// Inclusão de bibliotecas necessárias
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Definição de constantes
#define MAX_PECAS 5

// Estrutura para representar uma peça do Tetris Stack 
typedef struct {
    char tipo; // Tipo da peça (I, O, T, L)
    int id;    // Identificador único da peça
} Peca;

// Estrutura para representar a fila de peças futuras
typedef struct {
    Peca nome[MAX_PECAS]; // Array para armazenar as peças
    int inicio;           // Índice do início da fila
    int fim;              // Índice do final da fila
    int total;          // Tamanho atual da fila
} Fila;

// Protótipos das funções
void inicializarFila(Fila *f);
void gerarPecas(Fila *f, int *proximoId);
void jogarPeca(Fila *f);
void inserirNovaPeca(Fila *f, int *proximoId);
void inserirPecaNaFila(Fila *f, char tipo, int id);
void exibirFila(Fila *f);

// Função principal
int main() {
    Fila f;
    char opcao;
    int proximoId = 1; // Contador para garantir IDs exclusivos

    srand(time(NULL)); // Inicializa o gerador de números aleatórios

    inicializarFila(&f);
    gerarPecas(&f, &proximoId); // Preenche a fila inicialmente

    do {
        printf("\n---------------------------------------------------\n");
        printf("SEJA BEM VINDO AO JOGO TETRIS STACK - NÍVEL NOVATO!\n");
        printf("---------------------------------------------------\n\n");

        exibirFila(&f);

        printf("MENU DE OPÇÕES:\n");
        printf("1. Jogar peça (remover - dequeue)\n");
        printf("2. Inserir nova peça (Adicionar - enqueue)\n");
        printf("3. Sair\n");
        printf("\n");
        printf("Escolha uma opção (1-3): ");
        scanf(" %c", &opcao);
        getchar();
        
        switch (opcao) {
            case '1':
                jogarPeca(&f);
                break;
            case '2':
                inserirNovaPeca(&f, &proximoId);
                break;
            case '3':
                printf("Saindo do programa...\n");
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
        }

    } while (opcao != '3');

    return 0;
}

// Função para inicializar a fila
void inicializarFila(Fila *f) {
    f->inicio = 0;
    f->fim = 0;
    f->total = 0;
}

// Função para gerar as 5 peças iniciais para começar o jogo
void gerarPecas(Fila *f, int *proximoId) {
    char tipos[] = {'I', 'O', 'T', 'L'};
    for (int i = 0; i < MAX_PECAS; i++) {
        inserirPecaNaFila(f, tipos[rand() % 4], (*proximoId)++);
    }
}

// Lógica interna de inserção (Enqueue)
void inserirPecaNaFila(Fila *f, char tipo, int id) {
    if (f->total == MAX_PECAS) {
        printf("\n[AVISO] Fila cheia! Não é possível inserir mais peças.\n");
        return;
    }
    f->nome[f->fim].tipo = tipo;
    f->nome[f->fim].id = id;
    f->fim = (f->fim + 1) % MAX_PECAS; // Função circular
    f->total++;
}

// Função para o jogador adicionar uma peça (gera aleatoriamente)
void inserirNovaPeca(Fila *f, int *proximoId) {
    char tipos[] = {'I', 'O', 'T', 'L'};
    if (f->total < MAX_PECAS) {
        inserirPecaNaFila(f, tipos[rand() % 4], (*proximoId)++);
        printf("\nNova peça adicionada com sucesso!\n");
    } else {
        printf("\n[ERRO] Fila cheia! Remova uma peça antes de inserir outra.\n");
    }
}

// Função para jogar uma peça, remover da frente da fila (dequeue)
void jogarPeca(Fila *f) {
    if (f->total == 0) {
        printf("\n[ERRO] Fila vazia! Nenhuma peça para jogar.\n");
        return;
    }
    Peca p = f->nome[f->inicio];
    printf("\nPeça JOGADA (removida): [%c %d]\n", p.tipo, p.id);
    
    f->inicio = (f->inicio + 1) % MAX_PECAS; // Incremento circular
    f->total--;
}

// Função para exibir a fila atual
void exibirFila(Fila *f) {
    printf("ESTADO DA FILA: ");
    if (f->total == 0) {
        printf("[Vazia]");
    } else {
        int idx = f->inicio;
        for (int i = 0; i < f->total; i++) {
            printf("[%c %d] ", f->nome[idx].tipo, f->nome[idx].id);
            idx = (idx + 1) % MAX_PECAS;
        }
    }
    printf("\n\n");
}