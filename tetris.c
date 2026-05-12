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