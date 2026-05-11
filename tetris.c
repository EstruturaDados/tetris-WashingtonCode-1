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