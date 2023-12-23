#include <stdio.h>

// Game Functions
_Bool hasWon(unsigned int field[], const unsigned int turn, const size_t rowSizeSquared);
void nextTurn(unsigned int *turn);
_Bool executeMoveIfValid(unsigned int field[], unsigned int coordinate, unsigned int turn);

// Output Functions
void printField(unsigned int field[]);

// Input Functions
unsigned int inputMoveByUser(unsigned int field[], unsigned int ownTurn);

// Game Constants
constexpr unsigned int ROW_SIZE = 3;
constexpr unsigned int NUMBER_PLAYERS = 2;
constexpr char PLAYING_CHARACTERS[NUMBER_PLAYERS + 1] = {' ', 'X', 'O'};
// input method interface: int functionname(int field[], unsigned int ownTurn) {...return move;}
const unsigned int (*INPUT_METHODS[NUMBER_PLAYERS])(unsigned int field[], unsigned int ownTurn) = {inputMoveByUser, inputMoveByUser};
// output method interface: void functionname(int field[]) {...}
const void (*OUTPUT_METHOD)(unsigned int field[]) = printField;

// TicTacToe Launcher
void playTicTacToe();

_Bool hasWon(unsigned int field[], const unsigned int turn, const size_t rowSizeSquared) {
    _Bool winningConfiguration;
    // horizontal
    for (int i = 0; i < ROW_SIZE; i++) {
        winningConfiguration = 1;
        for (int ii = 0; ii < ROW_SIZE; ii++) {
            if (field[i * ROW_SIZE + ii] != turn) {
                winningConfiguration = 0;
                break;
            }
        }
        if (winningConfiguration) {
            return 1;
        }
    }
    // vertical
    for (int i = 0; i < ROW_SIZE; i++) {
        winningConfiguration = 1;
        for (int ii = 0; ii < ROW_SIZE; ii++) {
            if (field[i + ii * ROW_SIZE] != turn) {
                winningConfiguration = 0;
                break;
            }
        }
        if (winningConfiguration) {
            return 1;
        }
    }
    // diagonal
    winningConfiguration = 1;
    for (int i = 0; i < rowSizeSquared; i += 1 + ROW_SIZE) {
        if (field[i] != turn) {
            winningConfiguration = 0;
            break;
        }
    }
    if (winningConfiguration) {
        return 1;
    }
    winningConfiguration = 1;
    for (int i = rowSizeSquared - ROW_SIZE; i > 0; i += 1 - ROW_SIZE) {
        if (field[i] != turn) {
            winningConfiguration = 0;
            break;
        }
    }
    if (winningConfiguration) {
        return 1;
    }
    return 0;
}

void nextTurn(unsigned int *turn) {
    if (*turn == NUMBER_PLAYERS) {
        *turn = 1;
        return;
    }
    *turn = *turn + 1;
}

_Bool executeMoveIfValid(unsigned int field[], unsigned int coordinate, unsigned int turn) {
    if (field[coordinate] == 0) {
        field[coordinate] = turn;
        return 0;
    }
    return 1;
}

void playTicTacToe() {
    size_t rowSizeSquared = ROW_SIZE * ROW_SIZE;
    unsigned int field[rowSizeSquared];

    for (int i = 0; i < rowSizeSquared; i++) {
        field[i] = 0;
    }

    unsigned int fieldCoordinate;

    unsigned int turn = 0;
    do {
        // next turn
        nextTurn(&turn);
        do {
            // play move
            fieldCoordinate = INPUT_METHODS[turn - 1](field, turn);
        // validate and execute move
        } while (executeMoveIfValid(field, fieldCoordinate, turn));

        // print field
        OUTPUT_METHOD(field);
    } while (!hasWon(field, turn, rowSizeSquared));

    printf("\n\n%c has won the game!", PLAYING_CHARACTERS[turn]);
}

// Concrete Implementations

void printField(unsigned int field[]) {
    printf("\n");
    for (int i = 0; i < ROW_SIZE; i++) {
        printf(" %c", PLAYING_CHARACTERS[field[i * ROW_SIZE]]);
        for (int ii = 1; ii < ROW_SIZE; ii++) {
            printf(" | %c", PLAYING_CHARACTERS[field[i * ROW_SIZE + ii]]);
        }
        printf("\n");
    }
}

unsigned int inputMoveByUser(unsigned int field[], unsigned int ownTurn) {
    printf("Next move: ");
    int move;
    scanf("%d", &move);
    return move;
}

int main() {
    playTicTacToe();
    return 0;
}