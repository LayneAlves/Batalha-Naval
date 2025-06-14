//parte 1 

#include <stdio.h>

#define TAM 10        // Tamanho do tabuleiro (10x10)
#define NAVIO 3       // Valor que representa um pedaço do navio
#define AGUA 0        // Valor que representa água

// Função para inicializar o tabuleiro com 0 (água)
void inicializarTabuleiro(int tabuleiro[TAM][TAM]) {
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            tabuleiro[i][j] = AGUA;
        }
    }
}

// Função para exibir o tabuleiro no console
void exibirTabuleiro(int tabuleiro[TAM][TAM]) {
    printf("   ");
    for (int j = 0; j < TAM; j++) {
        printf("%2d ", j);
    }
    printf("\n");

    for (int i = 0; i < TAM; i++) {
        printf("%2d ", i);
        for (int j = 0; j < TAM; j++) {
            printf(" %d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

// Função para verificar se é possível posicionar um navio
int podePosicionar(int tabuleiro[TAM][TAM], int linha, int coluna, int tamanho, char direcao) {
    if (direcao == 'H') {
        if (coluna + tamanho > TAM) return 0;
        for (int j = coluna; j < coluna + tamanho; j++) {
            if (tabuleiro[linha][j] == NAVIO) return 0; // sobreposição
        }
    } else if (direcao == 'V') {
        if (linha + tamanho > TAM) return 0;
        for (int i = linha; i < linha + tamanho; i++) {
            if (tabuleiro[i][coluna] == NAVIO) return 0;
        }
    }
    return 1;
}

// Função para posicionar o navio na matriz
void posicionarNavio(int tabuleiro[TAM][TAM], int linha, int coluna, int tamanho, char direcao) {
    if (direcao == 'H') {
        for (int j = coluna; j < coluna + tamanho; j++) {
            tabuleiro[linha][j] = NAVIO;
        }
    } else if (direcao == 'V') {
        for (int i = linha; i < linha + tamanho; i++) {
            tabuleiro[i][coluna] = NAVIO;
        }
    }
}

int main() {
    int tabuleiro[TAM][TAM];
    int tamanhoNavio = 3;

    // Inicializa o tabuleiro com água
    inicializarTabuleiro(tabuleiro);

    // Coordenadas iniciais para o navio horizontal
    int linhaH = 2, colunaH = 4;

    // Coordenadas iniciais para o navio vertical
    int linhaV = 5, colunaV = 7;

    // Verifica e posiciona o navio horizontal
    if (podePosicionar(tabuleiro, linhaH, colunaH, tamanhoNavio, 'H')) {
        posicionarNavio(tabuleiro, linhaH, colunaH, tamanhoNavio, 'H');
    } else {
        printf("Erro ao posicionar navio horizontal!\n");
    }

    // Verifica e posiciona o navio vertical
    if (podePosicionar(tabuleiro, linhaV, colunaV, tamanhoNavio, 'V')) {
        posicionarNavio(tabuleiro, linhaV, colunaV, tamanhoNavio, 'V');
    } else {
        printf("Erro ao posicionar navio vertical!\n");
    }

    // Exibe o tabuleiro
    exibirTabuleiro(tabuleiro);

    return 0;
}
