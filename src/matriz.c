/*******************************************************
 *  Universidade Federal de Viçosa - Campus Florestal  *
 *  CCF330: Projeto e Análise de Algoritmos            *
 *  Prof: Daniel Mendes Barbosa                        *
 *  Aluno: Luan Alves(2278), Marcos Assis(1804)        *
 *******************************************************/

#include "matriz.h"


int menu_opcoes(void) {

    int opcao;

    printf(" ____________________________________________ \n");
    printf("\n        Trablho Patico 3 (Tarefa B)         \n");
    printf(" ____________________________________________ \n");
    printf("    Escolha uma das opcoes abaixo:          \n\n");
    printf("      (1) Gerar Arquivo                       \n");
    printf("      (2) Executar arquivo gerado             \n");
    printf("      (3) sair                                \n");
    printf(" ____________________________________________ \n");
    printf(" Digite a opcao desejada: ");
    scanf("%d", &opcao);
    return opcao;
}

int num_aleatorio(int limite_inf, int limite_sup) {
    return (limite_inf + rand() % limite_sup);
}

int gerar_arquivo(int tamanho_linha, int tamanho_coluna, int N, int acrecimo) {
    FILE *arquivo;
    int x1, y1,
        x2, y2,
        c1, c2;
    int c;
    int aux;
    int k = 1;
    char coord[6] = {'L', 'N', 'L', 'N', 'L', 'N'}; // vetor para sorteio.
    char num_string_buff[3];

    while (k <= N) {

        char url[14] = "arquivo";
        sprintf(num_string_buff, "%d", k);
        strcat(url, num_string_buff);
        strcat(url, ".txt");
        printf("\n %s", url);

        if ((arquivo = fopen(url, "w")) == NULL) {
            perror(" Nao foi possivel abrir o arquivo desejado!\n");
            exit(EXIT_FAILURE);
        } else {
            fprintf(arquivo, "%d %d\n", tamanho_linha, tamanho_coluna);
            x1 = num_aleatorio(1, tamanho_linha);
            y1 = num_aleatorio(1, tamanho_coluna);
            fprintf(arquivo, "%d %d\n", x1, y1);

            do {
                x2 = num_aleatorio(1, tamanho_linha);
                y2 = num_aleatorio(1, tamanho_coluna);
            } while (x2 <= x1 || y2 <= y1);

            fprintf(arquivo, "%d %d\n", x2, y2);

            tamanho_linha <= tamanho_coluna ? (aux = tamanho_linha) : (aux = tamanho_coluna);
            for (int i = 0; i < num_aleatorio(2, aux); i++) {
                do {
                    c1 = num_aleatorio(1, tamanho_linha);
                    c2 = num_aleatorio(1, tamanho_coluna);
                } while (((c1 == x1) && (c2 == y1)) || ((c2 == x2) && (c2 == y2)));
                c = num_aleatorio(0, 5);
                fprintf(arquivo, "%d %d %c\n", c1, c2, coord[c]);
            }
            tamanho_linha += acrecimo;
            tamanho_coluna += acrecimo;
        }
        k++;
    }
    fclose(arquivo);
    return 0;
}

int le_tamanho_matriz(char url[], int *num_linha, int *num_coluna) {
    FILE *arquivo;
    if ((arquivo = fopen(url, "r")) == NULL) {
        perror(" Nao foi possivel abrir o arquivo desejado!\n");
        exit(EXIT_FAILURE);
    } else {
        fscanf(arquivo, "%d %d\n", num_linha, num_coluna);
    }
    fclose(arquivo);

    return 0;
}

int le_arquivo(char url[], int num_linha, int num_coluna, char matriz[num_linha][num_coluna], int *linha_inicio,
               int *coluna_inicio, int *linha_chegada, int *coluna_chegada)
{

    FILE *arquivo;
    int i, j;
    int __unused1, __unused2;
    char coord;

    // Inicializa a matriz com '-'.
    for (int i = 0; i < num_linha; i++) {
        for (int j = 0; j < num_coluna; j++) {
            matriz[i][j] = '-';
        }
    }

    if ((arquivo = fopen(url, "r")) == NULL) {
        perror(" Nao foi possivel abrir o arquivo desejado!\n");
        exit(EXIT_FAILURE);
    } else {
        fscanf(arquivo, "%d %d\n", &__unused1, &__unused2); // le a primeria lina do arquivo, mas nao a usa.
        fscanf(arquivo, "%d %d\n", linha_inicio, coluna_inicio);
        fscanf(arquivo, "%d %d\n", linha_chegada, coluna_chegada);

        /* ajustando os valores lidos para inseri-los na matriz com os indices adequados. */
        *linha_inicio = *linha_inicio - 1;
        *coluna_inicio = *coluna_inicio - 1;
        *linha_chegada = *linha_chegada - 1;
        *coluna_chegada = *coluna_chegada - 1;

        matriz[*linha_inicio][*coluna_inicio] = 'i';
        matriz[*linha_chegada][*coluna_chegada] = 'f';
        while (!feof(arquivo)) {
            fscanf(arquivo, "%d %d %c\n", &i, &j, &coord);
            i--;
            j--;
            matriz[i][j] = coord;
        }
        /* reajustando para os valores originais. */
        *linha_inicio = *linha_inicio + 1;
        *coluna_inicio = *coluna_inicio + 1;
        *linha_chegada = *linha_chegada + 1;
        *coluna_chegada = *coluna_chegada + 1;

        printf("\n Tamanho:   [%d x %d]\n", num_linha, num_coluna);
        printf(" Inicio  i: (%d : %d)\n Chegada f: (%d : %d)\n", *linha_inicio, *coluna_inicio, *linha_chegada, *coluna_chegada);
    }
    fclose(arquivo);

    return 0;
}

void inicializa_matriz_count(int num_linha, int num_coluna, unsigned int matriz[num_linha][num_coluna]) {
    for (int i = 0; i < num_linha; i++) {
        for (int j = 0; j < num_coluna; j++) {
            matriz[i][j] = 0;
        }
    }
}

void calcula_rotas(int num_linha, int num_coluna, char matriz_obras[num_linha][num_coluna], 
                    unsigned int matriz_count[num_linha][num_coluna]) {
    num_linha--;
    num_coluna--;

    matriz_count[num_linha][num_coluna] = 1;

    for (int i = num_linha; i >= 0; i--) {
        for (int j = num_coluna; j >= 0; j--) {
            if (i < num_linha && matriz_obras[i][j] != 'N') {
                matriz_count[i][j] += matriz_count[i + 1][j];
            }
            if (j < num_coluna && matriz_obras[i][j] != 'L') {
                matriz_count[i][j] += matriz_count[i][j + 1];
            }
        }
    }
}

void imprime_matriz_char(int num_linha, int num_coluna, char matriz[num_linha][num_coluna]) {

    for (int i = 0; i < num_linha; i++) {
        for (int j = 0; j < num_coluna; j++) {
            printf("\t%c", matriz[i][j]);
        }
        printf("\n\n");
    }
}

void imprime_matriz_int(int num_linha, int num_coluna, unsigned int matriz[num_linha][num_coluna]) {

    for (int i = 0; i < num_linha; i++) {
        for (int j = 0; j < num_coluna; j++) {
            printf("\t%u", matriz[i][j]);
        }
        printf("\n\n");
    }
}