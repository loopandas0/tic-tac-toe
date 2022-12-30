#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <windows.h>

typedef enum _BoardType {
    EMPTY,
    O,
    X
} BoardType;

bool game_finish = false;
int board_size;
BoardType** board;

void generateBoard(unsigned int _board_size) {
    int i, j;

    board_size = _board_size;

    board = (BoardType**)malloc(sizeof(BoardType*) * board_size);
    for(i = 0; i < board_size; i++) {
        board[i] = (BoardType*)malloc(sizeof(BoardType) * board_size);
        for(j = 0; j < board_size; j++) {
            board[i][j] = EMPTY;
        }
    }
}

void printBoard() {
    int i, j;

    for(i = 0; i < board_size; i++) {
        for(j = 0; j < board_size; j++) {
            switch(board[i][j]) {
            case EMPTY:
                printf("▦");
                break;

            case O:
                printf("○");
                break;

            case X:
                printf("※");
                break;
            }
        }
        puts("");
    }
}

bool setBoard(unsigned int x, unsigned int y, BoardType n) {
    if (x < 0 || y < 0 || x >= board_size || y >= board_size) return false;

    if (board[y][x] == EMPTY) {
        board[y][x] = n;
        return true;
    } else {
        return false;
    }
}

void checkBoard(BoardType sign) {
    int i, j;

    for(i = 0; i < board_size; i++) {
        for(j = 0; j < board_size; j++) {
            if (board[i][j] != sign) break;
        }
        if (j >= board_size) {
            finishGame(sign);
            return;
        }
    }

    for(i = 0; i < board_size; i++) {
        for(j = 0; j < board_size; j++) {
            if (board[j][i] != sign) break;
        }
        if (j >= board_size) {
            finishGame(sign);
            return;
        }
    }

    if (board_size > 3) {
        for(i = 0; i < board_size; i++) {
            if (board[i][i] != sign) break;
        }
        if (i >= board_size) {
            finishGame(sign);
            return;
        }

        for(i = 0; i < board_size; i++) {
            if (board[board_size - 1 - i][i] != sign) break;
        }
        if (i >= board_size) {
            finishGame(sign);
            return;
        }
    } else {
        for(i = 0; i < board_size; i++) {
            if (board[i][i] != sign) break;
        }
        if (i >= board_size) {
            finishGame(sign);
            return;
        }

        for(i = 0; i < board_size; i++) {
            if (board[board_size - 1 - i][i] != sign) break;
        }
        if (i >= board_size) {
            finishGame(sign);
            return;
        }
    }
}

void finishGame(BoardType winner) {
    if (winner == O) {
        printf("O ");
    } else {
        printf("X ");
    }

    printf("is winner!\n");

    game_finish = true;
}

int main(void) {
    BoardType turn = O;
    int input, input2;

    printf("Set board size : ");
    scanf("%d", &input);
    generateBoard(input);

    while(!game_finish) {
        system("cls");

        printBoard();

        if (turn == O) {
            printf("O ");
        } else {
            printf("X ");
        }
        printf("turn\n");

        scanf("%d %d", &input, &input2);
        if (!setBoard(input, input2, turn)) continue;

        if (turn == O) {
            turn = X;
        } else {
            turn = O;
        }

        checkBoard(O);
        checkBoard(X);
    }

    free(board);
    return 0;
}
