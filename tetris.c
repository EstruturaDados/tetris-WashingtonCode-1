// Desafio Tetris Stack - Nível Aventureiro
// Objetivo: Implementar um programa em C que simula o gerenciamento de peças no jogo Tetris Stack, utilizando uma fila circular de peças futuras e uma pilha de reserva. Cada peça tem um tipo (como 'I', 'O', 'T', 'L') e um identificador numérico único (id). O jogador poderá visualizar a fila e a pilha, jogar peças, reservar peças para uso posterior e remover peças da reserva.

// Inclusão de bibliotecas necessárias
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Definição de constantes
#define MAX_FILA 5
#define MAX_PILHA 3