/*******************************************************
 *  Universidade Federal de Viçosa - Campus Florestal  *
 *  CCF330: Projeto e Análise de Algoritmos            *
 *  Prof: Daniel Mendes Barbosa                        *
 *  Aluno: Luan Alves(2278), Marcos Assis(1804)        *
 *******************************************************/

#include <time.h>
#include "matriz.h"

#define NUM_ARQUIVOS_TESTE 5
#define NUM_ACRECIMO_ARQ 10

int main()
{
    srand((unsigned)time(NULL));
    FILE *arq_resultados;
    char urlr[] = "resultados.csv";
    const int num_exec = 10;

    int linha = 0,
        coluna = 0;
    int num_linha, num_coluna, linha_inicio, coluna_inicio, linha_chegada, coluna_chegada;
    int opcao;
    char num_string_buff[2];
    int debug_flag;
    clock_t tempo_exec; //variável para armazenar tempo

    float soma_tempo;

    if ((arq_resultados = fopen(urlr, "w")) == NULL) {
            perror(" Nao foi possivel abrir o arquivo desejado! resultados.txt \n");
            exit(EXIT_FAILURE);
        }
    
    if ((opcao = menu_opcoes()) == 2) {
        printf("\n Ativar Modo Debug? 1-sim ou 0-nao: ");
        scanf("%d", &debug_flag);
    }

    switch (opcao) {

        case 1:
            printf("\n Entre com o tamanho da matriz (numeros separados por espaco):");
            scanf("%d %d", &linha, &coluna);
            gerar_arquivo(linha, coluna, NUM_ARQUIVOS_TESTE, NUM_ACRECIMO_ARQ);
            printf("\n Arquivo Gerado com sucesso :)\n");
            break;
        case 2:
            fprintf(arq_resultados, "Tam. Matriz, Media Tempo\n");

            for (int i = 1; i <= NUM_ARQUIVOS_TESTE; i++) {

                char url1[13] = "arquivo";
                sprintf(num_string_buff, "%d", i);
                strcat(url1, num_string_buff);
                strcat(url1, ".txt");
                printf("\n %s", url1);

                le_tamanho_matriz(url1, &num_linha, &num_coluna);

                char matriz_obras[num_linha][num_coluna];
                unsigned int matriz_count[num_linha][num_coluna];

                inicializa_matriz_count(num_linha, num_coluna, matriz_count);
                le_arquivo(url1, num_linha, num_coluna, matriz_obras, &linha_inicio, &coluna_inicio, &linha_chegada, &coluna_chegada);

                if(debug_flag) {
                    soma_tempo=0.0;
                    for(int i = 0; i < num_exec; i++){
                        tempo_exec = clock(); // #Debug [INICIO]: Tempo de execucao.
                        calcula_rotas(num_linha, num_coluna, matriz_obras, matriz_count);
                        tempo_exec = clock() - tempo_exec; // #Debug [FIM]:
                        
                        soma_tempo += (((double)tempo_exec) / ((CLOCKS_PER_SEC / 1000)));
                    }
                    fprintf(arq_resultados, "%d,%f\n", num_linha, (soma_tempo/num_exec));
                    printf(" Media do tempo de execucao: %f\n", (soma_tempo/num_exec));
                } else {
                    calcula_rotas(num_linha, num_coluna, matriz_obras, matriz_count);
                    // imprime_matriz_int(num_linha, num_coluna, matriz_count);
                }
                printf(" Existem %u caminhos possiveis do ponto i ao f\n", matriz_count[linha_inicio - 1][coluna_inicio - 1]);
                printf(" _______________________________________________\n\n");
            }
            break;
        case 3:
            printf("\n Execucao Encerrada!\n");
            exit(1);
        default:
            printf("\n Opcao invalida, Tente novamente\n");
            break;
    }

    return 0;
}
