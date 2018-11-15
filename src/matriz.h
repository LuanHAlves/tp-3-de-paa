
#ifndef matriz_h
#define matriz_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int menu_opcoes(void);
int gerar_arquivo(int tamanho_linha, int tamanho_coluna, int N, int acrecimo);
int le_tamanho_matriz(char url[], int *num_linha, int *num_coluna);
int le_arquivo(char url[], int num_linha, int num_coluna, char matriz[num_linha][num_coluna],int *linha_inicio, 
                int *coluna_inicio, int *linha_chegada, int *coluna_chegada);
void inicializa_matriz_count(int num_linha, int num_coluna, unsigned int matriz[num_linha][num_coluna]);
void calcula_rotas(int num_linha, int num_coluna, char matriz_obras[num_linha][num_coluna], unsigned int matriz_count[num_linha][num_coluna]);
void imprime_matriz_char(int num_linha, int num_coluna, char matriz[num_linha][num_coluna]);
void imprime_matriz_int(int num_linha, int num_coluna, unsigned int matriz[num_linha][num_coluna]);

#endif // matriz_h
