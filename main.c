#include <stdio.h>
#include <string.h>

int board[8][8];

int replaceKnights() {
    for (int a = 0; a < 8; a++) {
        for (int c = 0; c < 8; c++) {
            if (board[a][c] == 4) {
                board[a][c] = 1;
                return 0;
            }
        }
    }
    return 1;
}

int movePiece(int o1, int o2, int t1, int t2) {
    int piece = board[o1][o2];
    switch (piece)
    {
    case 1:
        printf("[K]");
        if (board[t1][t2] == 1) {
            if (replaceKnights()) {
                printf("\n\nGAME OVER\n\n");
                exit(1);
            }
        }
        board[t1][t2] = 1;
        break;
    case 2:
        printf("[Q]");
        if (board[t1][t2] == 1) {
            if (replaceKnights()) {
                printf("\n\nGAME OVER\n\n");
                exit(1);
            }
        }
        board[t1][t2] = 2;
        board[o1][o2] = 0;
        break;
    case 3:
        printf("\n[R]\n");
        if (o1 != t1 && t2 != o2) {
            return 1;
        }
        for (int i = o1+1; i < t1; i++) {
            if (board[i][o2] != 0) {
                printf("obstructed. %d %d\n", i);
                return 1;
            }
        }
        for (int i = o2+1; i < t2; i++) {
            if (board[o1][i] != 0) {
                printf("obstructed 2nd. %d %d\n", i);
                return 1;
            }
        }
        board[o1][o2] = 0;
        board[t1][t2] = 3;
        break;
    case 4:
        printf("\n[K]\n");
        break;
    case 5:
        printf("\n[B]\n");
        if (board[t1][t2] == 0) {
            board[t1][t2] = 5;
            board[o1][o2] = 0;
            return 0;
        }
        return 1;
        break;
    case 6:
        printf("\n[P]\n");
        if (t2 != o2) {
            return 1;
        }
        if (t1 - o1 > 2) {
            return 1;
        }
        for (int i = o1+1; i < t1; i++) {
            if (board[i][o2] != 0) {
                printf("obstructed. %d %d\n", i);
                return 1;
            }
        }
        board[o1][o2] = 0;
        board[t1][t2] = 6;
        printf("moved pawn to array spot %d %d.\n", t1, t2);
        sleep(3);
        break;
    default:
        break;
    }
}

void setRank(int rank) {
    board[rank][0] = 3;
    board[rank][1] = 4;
    board[rank][2] = 5;
    board[rank][3] = 2;
    board[rank][4] = 1;
    board[rank][5] = 5;
    board[rank][6] = 4;
    board[rank][7] = 3;
}

void setBoard() {
    setRank(0);
    setRank(7);
    for (int i = 1; i < 7; i++) {
        for (int a = 0; a < 8; a++) {
            if (i == 1 || i == 6) {
                board[i][a] = 6;
                continue;
            }
            board[i][a] = 0;
        }
    }
}

void printBoard() {
    for (int a = 0; a < 8; a++) {
        for (int c = 0; c < 8; c++) {
            int piece = board[a][c];
            if (piece == 0) {
                printf("[%d%d]", a, c);
            } else {
                switch (piece)
                {
                case 1:
                    printf("[K]");
                    break;
                case 2:
                    printf("[Q]");
                    break;
                case 3:
                    printf("[R]");
                    break;
                case 4:
                    printf("[K]");
                    break;
                case 5:
                    printf("[B]");
                    break;
                case 6:
                    printf("[P]");
                    break;
                default:
                    break;
                }
            }
        }
        printf("\n");
    }
}

int main() {
    printf("Hello World!\n");
    printf("Starting Wizard Chess...\n");
    setBoard();
    sleep(1);

    int input1;
    int input2;
    while (1) {
        printBoard();
        scanf("%d", &input1);
        if (input1 % 10 > 7 || input1 > 77 || input1 < 0) {
            printf("invalid input\n"); 
            continue;
        }
        printf("selected %d %d\n", input1 / 10, input1 % 10);

        printf(" select another piece ");

        scanf("%d", &input2);
        if (input2 % 10 > 7 || input2 > 77 || input2 < 0) {
            printf("invalidated input\n");
            continue;
        }
        printf("selected %d %d to move to\n", input2 % 10, input2 / 10);

        int result = movePiece( (input1 / 10), (input1 % 10), (input2 / 10) , (input2 % 10));
        if (result == 1) {
            printf("Move failed\n");
            return 1;
        }
    }
}
