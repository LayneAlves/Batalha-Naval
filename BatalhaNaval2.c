//parte2 

#include <stdio.h>

#define TAM 10
#define NAVIO 3
#define AGUA 0

// Inicializa o tabuleiro com 0 (água)
void inicializarTabuleiro(int tabuleiro[TAM][TAM]) {
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            tabuleiro[i][j] = AGUA;
        }
    }
}

// Mostra o tabuleiro no console
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

// Verifica se pode posicionar o navio na direção dada
int podePosicionar(int tabuleiro[TAM][TAM], int linha, int coluna, int tamanho, char direcao) {
    for (int i = 0; i < tamanho; i++) {
        int l = linha, c = coluna;

        if (direcao == 'H') c += i;
        else if (direcao == 'V') l += i;
        else if (direcao == 'D') { l += i; c += i; }  // Diagonal principal ↘️
        else if (direcao == 'd') { l += i; c -= i; }  // Diagonal secundária ↙️

        // Verifica limites
        if (l < 0 || l >= TAM || c < 0 || c >= TAM) return 0;

        // Verifica sobreposição
        if (tabuleiro[l][c] == NAVIO) return 0;
    }
    return 1;
}

// Posiciona o navio na direção especificada
void posicionarNavio(int tabuleiro[TAM][TAM], int linha, int coluna, int tamanho, char direcao) {
    for (int i = 0; i < tamanho; i++) {
        int l = linha, c = coluna;

        if (direcao == 'H') c += i;
        else if (direcao == 'V') l += i;
        else if (direcao == 'D') { l += i; c += i; }
        else if (direcao == 'd') { l += i; c -= i; }

        tabuleiro[l][c] = NAVIO;
    }
}

int main() {
    int tabuleiro[TAM][TAM];
    int tamanhoNavio = 3;

    // Inicializa o tabuleiro com água
    inicializarTabuleiro(tabuleiro);

    //NAVIOS HORIZONTAIS/VERTICAIS
    if (podePosicionar(tabuleiro, 1, 1, tamanhoNavio, 'H'))
        posicionarNavio(tabuleiro, 1, 1, tamanhoNavio, 'H');
    else
        printf("Erro ao posicionar navio horizontal.\n");

    if (podePosicionar(tabuleiro, 4, 6, tamanhoNavio, 'V'))
        posicionarNavio(tabuleiro, 4, 6, tamanhoNavio, 'V');
    else
        printf("Erro ao posicionar navio vertical.\n");

    //NAVIOS DIAGONAIS
    if (podePosicionar(tabuleiro, 6, 0, tamanhoNavio, 'D'))  // ↘️
        posicionarNavio(tabuleiro, 6, 0, tamanhoNavio, 'D');
    else
        printf("Erro ao posicionar navio diagonal principal.\n");

    if (podePosicionar(tabuleiro, 2, 8, tamanhoNavio, 'd'))  // ↙️
        posicionarNavio(tabuleiro, 2, 8, tamanhoNavio, 'd');
    else
        printf("Erro ao posicionar navio diagonal secundária.\n");

    // Exibe o tabuleiro com todos os navios
    exibirTabuleiro(tabuleiro);

    return 0;
}
