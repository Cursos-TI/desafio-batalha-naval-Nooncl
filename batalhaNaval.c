#include <stdio.h>

#define TAM_TABULEIRO 10
#define TAM_NAVIO 3
#define TAM_HABILIDADE 5

int main() {
    int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO];
    int habilidadeCone[TAM_HABILIDADE][TAM_HABILIDADE];
    int habilidadeCruz[TAM_HABILIDADE][TAM_HABILIDADE];
    int habilidadeOctaedro[TAM_HABILIDADE][TAM_HABILIDADE];

    int i, j;

    // =========================================================
    // INICIALIZA O TABULEIRO COM ÁGUA (0)
    // =========================================================
    for (i = 0; i < TAM_TABULEIRO; i++) {
        for (j = 0; j < TAM_TABULEIRO; j++) {
            tabuleiro[i][j] = 0;
        }
    }

    // =========================================================
    // POSICIONA 4 NAVIOS (VALOR 3)
    // =========================================================

    // Navio horizontal
    for (i = 0; i < TAM_NAVIO; i++) {
        tabuleiro[1][2 + i] = 3;
    }

    // Navio vertical
    for (i = 0; i < TAM_NAVIO; i++) {
        tabuleiro[5 + i][0] = 3;
    }

    // Navio diagonal principal (↘)
    for (i = 0; i < TAM_NAVIO; i++) {
        tabuleiro[i][7 + i] = 3;
    }

    // Navio diagonal secundária (↙)
    for (i = 0; i < TAM_NAVIO; i++) {
        tabuleiro[7 + i][9 - i] = 3;
    }

    // =========================================================
    // INICIALIZA AS MATRIZES DAS HABILIDADES COM 0
    // =========================================================
    for (i = 0; i < TAM_HABILIDADE; i++) {
        for (j = 0; j < TAM_HABILIDADE; j++) {
            habilidadeCone[i][j] = 0;
            habilidadeCruz[i][j] = 0;
            habilidadeOctaedro[i][j] = 0;
        }
    }

    // =========================================================
    // CONSTRÓI A HABILIDADE CONE
    // Formato:
    // 0 0 1 0 0
    // 0 1 1 1 0
    // 1 1 1 1 1
    // 0 0 0 0 0
    // 0 0 0 0 0
    // =========================================================
    for (i = 0; i < 3; i++) {
        for (j = 0; j < TAM_HABILIDADE; j++) {
            if (j >= 2 - i && j <= 2 + i) {
                habilidadeCone[i][j] = 1;
            }
        }
    }

    // =========================================================
    // CONSTRÓI A HABILIDADE CRUZ
    // =========================================================
    for (i = 0; i < TAM_HABILIDADE; i++) {
        for (j = 0; j < TAM_HABILIDADE; j++) {
            if (i == 2 || j == 2) {
                habilidadeCruz[i][j] = 1;
            }
        }
    }

    // =========================================================
    // CONSTRÓI A HABILIDADE OCTAEDRO (LOSANGO)
    // =========================================================
    for (i = 0; i < TAM_HABILIDADE; i++) {
        for (j = 0; j < TAM_HABILIDADE; j++) {
            // Distância de Manhattan ao centro (2,2)
            int distancia = (i > 2 ? i - 2 : 2 - i) +
                            (j > 2 ? j - 2 : 2 - j);

            if (distancia <= 2) {
                habilidadeOctaedro[i][j] = 1;
            }
        }
    }

    // =========================================================
    // DEFINE AS ORIGENS DAS HABILIDADES NO TABULEIRO
    // =========================================================
    int origemConeLinha = 2;
    int origemConeColuna = 2;

    int origemCruzLinha = 5;
    int origemCruzColuna = 5;

    int origemOctLinha = 7;
    int origemOctColuna = 2;

    // =========================================================
    // SOBREPOSIÇÃO DA HABILIDADE CONE (VALOR 5)
    // =========================================================
    for (i = 0; i < TAM_HABILIDADE; i++) {
        for (j = 0; j < TAM_HABILIDADE; j++) {
            if (habilidadeCone[i][j] == 1) {
                int linhaTab = origemConeLinha + (i - 2);
                int colunaTab = origemConeColuna + (j - 2);

                if (linhaTab >= 0 && linhaTab < TAM_TABULEIRO &&
                    colunaTab >= 0 && colunaTab < TAM_TABULEIRO &&
                    tabuleiro[linhaTab][colunaTab] == 0) {
                    tabuleiro[linhaTab][colunaTab] = 5;
                }
            }
        }
    }

    // =========================================================
    // SOBREPOSIÇÃO DA HABILIDADE CRUZ (VALOR 5)
    // =========================================================
    for (i = 0; i < TAM_HABILIDADE; i++) {
        for (j = 0; j < TAM_HABILIDADE; j++) {
            if (habilidadeCruz[i][j] == 1) {
                int linhaTab = origemCruzLinha + (i - 2);
                int colunaTab = origemCruzColuna + (j - 2);

                if (linhaTab >= 0 && linhaTab < TAM_TABULEIRO &&
                    colunaTab >= 0 && colunaTab < TAM_TABULEIRO &&
                    tabuleiro[linhaTab][colunaTab] == 0) {
                    tabuleiro[linhaTab][colunaTab] = 5;
                }
            }
        }
    }

    // =========================================================
    // SOBREPOSIÇÃO DA HABILIDADE OCTAEDRO (VALOR 5)
    // =========================================================
    for (i = 0; i < TAM_HABILIDADE; i++) {
        for (j = 0; j < TAM_HABILIDADE; j++) {
            if (habilidadeOctaedro[i][j] == 1) {
                int linhaTab = origemOctLinha + (i - 2);
                int colunaTab = origemOctColuna + (j - 2);

                if (linhaTab >= 0 && linhaTab < TAM_TABULEIRO &&
                    colunaTab >= 0 && colunaTab < TAM_TABULEIRO &&
                    tabuleiro[linhaTab][colunaTab] == 0) {
                    tabuleiro[linhaTab][colunaTab] = 5;
                }
            }
        }
    }

    // =========================================================
    // EXIBE O TABULEIRO COM LETRAS E NÚMEROS
    // =========================================================
    printf("TABULEIRO BATALHA NAVAL\n");

    // Letras das colunas (A até J)
    printf("  ");
    for (j = 0; j < TAM_TABULEIRO; j++) {
        printf(" %c", 'A' + j);
    }
    printf("\n");

    // Linhas numeradas
    for (i = 0; i < TAM_TABULEIRO; i++) {
        printf("%d ", i);

        for (j = 0; j < TAM_TABULEIRO; j++) {
            if (tabuleiro[i][j] == 0) {
                printf("0 ");
            } else if (tabuleiro[i][j] == 3) {
                printf("3 ");
            } else if (tabuleiro[i][j] == 5) {
                printf("5 ");
            }
        }

        printf("\n");
    }

    return 0;
}