//parte 3
#include <stdio.h>
#include <stdlib.h>

#define TAM_TAB 10
#define TAM_NAVIO 3
#define TAM_HABILIDADE 5

// Função para inicializar tabuleiro com zeros (água)
void inicializarTabuleiro(char tabuleiro[TAM_TAB][TAM_TAB]) {
    for(int i = 0; i < TAM_TAB; i++) {
        for(int j = 0; j < TAM_TAB; j++) {
            tabuleiro[i][j] = '0'; // água
        }
    }
}

// Função para posicionar navio horizontal ou vertical
// tipo: 'H' horizontal, 'V' vertical
int posicionarNavio(char tabuleiro[TAM_TAB][TAM_TAB], int linha, int coluna, char tipo) {
    if (tipo == 'H') {
        if (coluna + TAM_NAVIO > TAM_TAB) return 0; // não cabe horizontalmente
        for(int i = 0; i < TAM_NAVIO; i++) {
            if (tabuleiro[linha][coluna + i] != '0') return 0; // sobreposição
        }
        for(int i = 0; i < TAM_NAVIO; i++) {
            tabuleiro[linha][coluna + i] = 'N';
        }
    } else if (tipo == 'V') {
        if (linha + TAM_NAVIO > TAM_TAB) return 0; // não cabe verticalmente
        for(int i = 0; i < TAM_NAVIO; i++) {
            if (tabuleiro[linha + i][coluna] != '0') return 0; // sobreposição
        }
        for(int i = 0; i < TAM_NAVIO; i++) {
            tabuleiro[linha + i][coluna] = 'N';
        }
    } else {
        return 0; // tipo inválido
    }
    return 1;
}

// Posicionar navio diagonal (descendo para direita)
int posicionarNavioDiagonal(char tabuleiro[TAM_TAB][TAM_TAB], int linha, int coluna) {
    if (linha + TAM_NAVIO > TAM_TAB || coluna + TAM_NAVIO > TAM_TAB) return 0; 
    for(int i = 0; i < TAM_NAVIO; i++) {
        if (tabuleiro[linha + i][coluna + i] != '0') return 0;
    }
    for(int i = 0; i < TAM_NAVIO; i++) {
        tabuleiro[linha + i][coluna + i] = 'N';
    }
    return 1;
}

// Posicionar navio diagonal (descendo para esquerda)
int posicionarNavioDiagonalEsq(char tabuleiro[TAM_TAB][TAM_TAB], int linha, int coluna) {
    if (linha + TAM_NAVIO > TAM_TAB || coluna - TAM_NAVIO + 1 < 0) return 0; 
    for(int i = 0; i < TAM_NAVIO; i++) {
        if (tabuleiro[linha + i][coluna - i] != '0') return 0;
    }
    for(int i = 0; i < TAM_NAVIO; i++) {
        tabuleiro[linha + i][coluna - i] = 'N';
    }
    return 1;
}

// Criar matriz da habilidade cone (5x5), com topo no meio da linha 0
void criarCone(int cone[TAM_HABILIDADE][TAM_HABILIDADE]) {
    int centro = TAM_HABILIDADE / 2;
    for(int i = 0; i < TAM_HABILIDADE; i++) {
        for(int j = 0; j < TAM_HABILIDADE; j++) {
            // condição para formar o cone apontando para baixo
            if(j >= centro - i && j <= centro + i)
                cone[i][j] = 1;
            else
                cone[i][j] = 0;
        }
    }
}

// Criar matriz da habilidade cruz (5x5)
void criarCruz(int cruz[TAM_HABILIDADE][TAM_HABILIDADE]) {
    int centro = TAM_HABILIDADE / 2;
    for(int i = 0; i < TAM_HABILIDADE; i++) {
        for(int j = 0; j < TAM_HABILIDADE; j++) {
            if(i == centro || j == centro)
                cruz[i][j] = 1;
            else
                cruz[i][j] = 0;
        }
    }
}

// Criar matriz da habilidade octaedro (5x5)
void criarOctaedro(int octaedro[TAM_HABILIDADE][TAM_HABILIDADE]) {
    int centro = TAM_HABILIDADE / 2;
    for(int i = 0; i < TAM_HABILIDADE; i++) {
        for(int j = 0; j < TAM_HABILIDADE; j++) {
            if(abs(i - centro) + abs(j - centro) <= centro)
                octaedro[i][j] = 1;
            else
                octaedro[i][j] = 0;
        }
    }
}

// Sobrepor matriz habilidade ao tabuleiro com valor '3'
void aplicarHabilidade(char tabuleiro[TAM_TAB][TAM_TAB], int habilidade[TAM_HABILIDADE][TAM_HABILIDADE], int origemLinha, int origemColuna) {
    int meio = TAM_HABILIDADE / 2;
    for(int i = 0; i < TAM_HABILIDADE; i++) {
        for(int j = 0; j < TAM_HABILIDADE; j++) {
            if(habilidade[i][j] == 1) {
                int tabLinha = origemLinha - meio + i;
                int tabCol = origemColuna - meio + j;
                if(tabLinha >=0 && tabLinha < TAM_TAB && tabCol >=0 && tabCol < TAM_TAB) {
                    // Só sobrepõe se não for navio
                    if(tabuleiro[tabLinha][tabCol] == '0') {
                        tabuleiro[tabLinha][tabCol] = '3';
                    }
                }
            }
        }
    }
}

// Imprimir tabuleiro formatado
void imprimirTabuleiro(char tabuleiro[TAM_TAB][TAM_TAB]) {
    printf("    ");
    for(int i=0; i<TAM_TAB; i++) {
        printf("%2d ", i);
    }
    printf("\n");

    for(int i=0; i<TAM_TAB; i++) {
        printf("%2d |", i);
        for(int j=0; j<TAM_TAB; j++) {
            printf(" %c ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

int main() {
    char tabuleiro[TAM_TAB][TAM_TAB];
    int cone[TAM_HABILIDADE][TAM_HABILIDADE];
    int cruz[TAM_HABILIDADE][TAM_HABILIDADE];
    int octaedro[TAM_HABILIDADE][TAM_HABILIDADE];

    // Inicializa tabuleiro com água
    inicializarTabuleiro(tabuleiro);

    // Posiciona os navios (2 fixos horizontal e vertical, 2 diagonais)
    // Ajuste coordenadas para não se sobreporem e ficarem visíveis
    posicionarNavio(tabuleiro, 1, 1, 'H');     // horizontal no topo esquerdo
    posicionarNavio(tabuleiro, 5, 7, 'V');     // vertical perto do meio direita
    posicionarNavioDiagonal(tabuleiro, 7, 0);  // diagonal descendo para direita no canto inferior esquerdo
    posicionarNavioDiagonalEsq(tabuleiro, 4, 9);// diagonal descendo para esquerda meio direito

    // Cria matrizes das habilidades
    criarCone(cone);
    criarCruz(cruz);
    criarOctaedro(octaedro);

    // Aplica habilidades no tabuleiro em posições distintas para melhor visualização
    aplicarHabilidade(tabuleiro, cone, 2, 5);      // cone perto do topo centro-direita
    aplicarHabilidade(tabuleiro, cruz, 7, 7);      // cruz perto do meio inferior direita
    aplicarHabilidade(tabuleiro, octaedro, 5, 2);  // octaedro perto do meio esquerdo

    // Imprime o tabuleiro final
    imprimirTabuleiro(tabuleiro);

    return 0;
}
