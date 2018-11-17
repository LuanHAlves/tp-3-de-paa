
#ifndef matriz_h
#define matriz_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Funcao para exibir o menu de opcoes.
 */
int menu_opcoes(void);

/**
 * Funcao para gerar arquivos automaticamente
 * utilizando numeros aleatorio.
 */
int gerar_arquivo(int tamanho_linha, int tamanho_coluna, int N, int acrecimo);

/**
 * Funcao para ler do arquivo o tamanho da matriz.
 */
int le_tamanho_matriz(char url[], int *num_linha, int *num_coluna);

/**
 * Esta funcao le o restante do arquivo e 
 * e insere os valores na matriz de obras.
 * Nesta matriz sao inseridos as barreiras 
 * e os pontos de inicio e de chegado.
 */
int le_arquivo(char url[], int num_linha, int num_coluna, char matriz[num_linha][num_coluna],int *linha_inicio, int *coluna_inicio, int *linha_chegada, int *coluna_chegada);

/**
 * Funcao que inicializa a matriz count 
 * com o valor zero.
 */
void inicializa_matriz_count(int num_linha, int num_coluna, unsigned int matriz[num_linha][num_coluna]);

/**
 * Funcao que realiza os calculos 
 * do numero de rotas possivei em
 * cada posicao da matriz count.
 */
void calcula_rotas(int num_linha, int num_coluna, char matriz_obras[num_linha][num_coluna], unsigned int matriz_count[num_linha][num_coluna]);

/**
 * Funcao que imprime a matriz de char 
 * onde constam as barreira e o ponto 
 * de inicio e de chegada. 
 */
void imprime_matriz_char(int num_linha, int num_coluna, char matriz[num_linha][num_coluna]);

/**
 * Funcao que imprime a matriz de int  count 
 * onde estao o numero de rotas possiveis 
 * em cada posicao.
 */
void imprime_matriz_int(int num_linha, int num_coluna, unsigned int matriz[num_linha][num_coluna]);

#endif // matriz_h
