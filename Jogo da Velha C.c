#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

/* variavel global */
// matriz do Jogo.
char game[3][3]; 

// l = Linha | c = Coluna.
int l, c; 

/* tabuleiro */
void startMatriz() {
    for (l = 0; l < 3; l++) {
        for (c = 0; c < 3; c++)
            game[l][c] = ' ';
    }
}

/* função para imprimir tabuleiro */
void printTable() {
    printf("\n\n\t 0   1   2\n\n");
    for(l = 0; l < 3; l++) {
        for(c = 0; c < 3; c++) {
            if(c == 0)
                printf("\t");
            printf(" %c ", game[l][c]);
            if(c < 2)
                printf("|");
            if(c == 2)
                printf("   %d", l);
        }
        printf("\n");
        if(l < 2)
            printf("\t-----------\n");
    }
}

/* função para validar uma coordenada */
int makeValue(int l, int c) {
    if (l >= 0 && l < 3 && c >= 0 && c < 3 && game[l][c] == ' ')
        return 1;
    else
        return 0;
}

/* função para definir vitoria */

/* jogador 'c' na Linha 'l'  */
int winLine(int l, char c) {
    if (game[l][0] == c && game[l][1] == c && game[l][2] == c)
        return 1;
    else
        return 0;
}

/* jogador 'c' nas linhas */
int winLines(char c) {
    int win = 0;
    for (l = 0; l < 3; l++)
    {
        win += winLine(l, c);
    }
    return win;
}

/* jogador 'j' Na coluna 'c' */
int winColumn(int c, char j) {
    if (game[0][c] == j && game[1][c] == j && game[2][c] == j)
        return 1;
    else
        return 0;
}

/* jogador 'j' nas nolunas */
int winColumns(char j) {
    int win = 0;
    for (c = 0; c < 3; c++)
    {
        win += winColumn(c, j);
    }
    return win;
}

/* jogador 'c' na diagonal principal*/
int winDiagPrin(char c) {
    if (game[0][0] == c && game[1][1] == c && game[2][2] == c)
        return 1;
    else
        return 0;
}

/* jogador 'c' na diagonal secundaria */
int winDiagSec(char c) {
    if (game[0][2] == c && game[1][1] == c && game[2][0] == c)
        return 1;
    else
        return 0;
}

/* funcao para pedir as coordenadas */
void getPlace(char j) {
    int line, column;

    printf("\nJogador %c digite a linha: ", j);
    scanf("%d", &line);
    printf("\nJogador %c digite a coluna: ", j);
    scanf("%d",&column);

    while (makeValue(line, column) == 0) {
        printf("\nCoordenadas invalidas!\n\nJogador %c digite outra linha: ", j);
        scanf("%d", &line);
        printf("\nCoordenadas invalidas!\n\nJogador %c digite outra coluna: ", j);
        scanf("%d",&column);
    }
    game[line][column] = j;
}

/* funcao que retorna posicoes vazias */
int emptySpaces() {
    int space = 0;

    for (l = 0; l < 3; l++) {
        for (c = 0; c < 3; c++)
            if (game[l][c] == ' ')
                space++;
    }
    return space;
}

/* funcao para iniciar jogo */
void play(int *plays_player1, int *plays_player2) {
    int player = 1, winX = 0, winO = 0;
    char player1 = 'X', player2 = '0';

    FILE *pont_arq;

    do {
        printTable();
        if (player == 1) {
            getPlace(player1);
            player++;
            winX += winLines(player1);
            winX += winColumns(player1);
            winX += winDiagPrin(player1);
            winX += winDiagSec(player1);
        } else {
            getPlace(player2);
            player = 1;
            winO += winLines(player2);
            winO += winColumns(player2);
            winO += winDiagPrin(player2);
            winO += winDiagSec(player2);
        }
        system("CLS");
    } while (winX == 0 && winO == 0 && emptySpaces() > 0);

    printTable();

    if (winO == 1) {
        printf("\nParabens Jogador 2. Voce venceu!!!\n");
        *plays_player2 += 1;
    } else if (winX == 1) {
        printf("\nParabens Jogador 1. Voce venceu!!!\n");
        *plays_player1 += 1;
    } else {
        printf("\nDeu velha!!!\n");
    }

    /* arquivos com os ranking | contendo o jogador 1 e 2 mais a quantidade de vitorias deles  */
    pont_arq = fopen("arquivo1.txt", "w");

    fprintf(pont_arq, "O Jogador 1 ganhou %d vezes\n", *plays_player1);
    fprintf(pont_arq, "O jogador 2 ganhou %d vezes", *plays_player2);

    fclose(pont_arq);
}

/* menu */
int header() {
    int selectedOne;

    printf("--- JOGO DA VELHA ---");
    printf("\n1- Jogar");
    printf("\n2- Ranking");
    printf("\n3- Créditos");
    printf("\n4- Sair\n\n");
    scanf("%d", &selectedOne);
    return selectedOne;
}

/* main */
int main() {
    
    setlocale(LC_ALL, "Portuguese");
    
	int option;
    int plays_player1 = 0, plays_player2 = 0;
    
	FILE *pont_arq;

    do {
        system("CLS");
        switch (header()) {
        case 1:
            do {
                system("CLS");
                startMatriz();
                play(&plays_player1, &plays_player2);
                printf("\nDigite 1 para jogar novamente ou outro número para sair: ");
                scanf("%d", &option);
            } while (option == 1);
            break;
        case 2:
            system("CLS");
            printf("--- RANKING ---\n\n");
            printf("O jogador 1 ganhou %d\n", plays_player1);
            printf("O jogador 2 ganhou %d\n\n", plays_player2);
            break;
        case 3:
            system("CLS");
            printf("--- CREDITOS ---\n\n");
            printf("Ana Beatriz Cavalcanti Pereira - RMG:30218039\n");
            printf("Gustavo Targino - RMG:30283647\n");
            printf("Hilton Medeiros Amorim - RMG:29264197\n");
            printf("Lucas Bezerra dos Santos - RMG:29469970\n");
            break;
        case 4:
            exit(0);
            break;
        default:
        	printf("Digite uma opção valida!");
        }
        printf("\nDigite 1 para retornar: ");
        scanf("%d", &option);
    } while (option == 1);

    return 0;
}

