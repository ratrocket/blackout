#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

#define EX 0x58  // "X"
#define OH 0x4f  // "O"
#define NL 0x0a  // "\n"
#define SP 0x20  // " "

typedef unsigned short Ushort;

int print_board(Ushort);
int win(Ushort);
void closing_message(int);

int main(int argc, char *argv[]) {
    int i = 0;
    char c_move[128] = { 0 };
    int i_move = 0;
    int num_moves = 0;
    Ushort board = 0;
    Ushort masks[9] = {
        0xb,   // 0,1,3
        0x17,  // 0,1,2,4
        0x26,  // 1,2,5
        0x59,  // 0,3,4,6
        0xba,  // 1,3,4,5,7
        0x134, // 2,4,5,8
        0xc8,  // 3,6,7
        0x1d0, // 4,6,7,8
        0x1a0  // 5,7,8
    };

    srandom(time(NULL));
    while (win(board)) {
        if (board) board = 0;  // all 1s causes problem
        for (i = 0; i < 9; i++) board |= ((random() & 01) << i);
    }

    do {
        print_board(board);
        printf("move? (1-9): ");
        scanf("%s", c_move);
        i_move = (int) strtol(c_move, (char **)NULL, 10);
        if (i_move > 0 && i_move < 10) {
            board ^= masks[i_move - 1];
            num_moves++;
        }
    } while (!win(board));

    print_board(board);
    closing_message(num_moves);

    return 0;
}

int print_board(Ushort b) {
    int i = 0;
    int piece = 0;
    for (i = 0; i < 9; i++) {
        piece = b & (1 << i);
        putchar(piece ? OH : EX);
        putchar(i % 3 == 2 ? NL : SP);
    }
    return 0;
}

int win(Ushort b) { return (b == 0 || b == 511); }

void closing_message(int n) {
    printf("\nB L A  =======>\n");
    printf("C K !  ...... You won in %d moves.\n", n);
    printf("O U T  ====>\n");
}
