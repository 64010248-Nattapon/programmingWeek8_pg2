#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#define R 6 // Rows
#define C 7 //coloumns

void printBoard(char board[R][C]);
void initializeBoard(char board[R][C]);
int checkMove(char board[R][C], int col, char player, int steps[42], int count);
int inRange(int col);
void scanMove(int col);
void printTurn(char player);
int emptyPlace(char board[R][C], int col);
void startGame(char board[R][C], int col, char player, int count);
int lastMove(char board[R][C], int steps[42], int count);
void Undo(char board[R][C], int steps[42], int i);

int main()
{
    int col = 0, i = 0;
    char board[R][C], player = 'O';
    int steps[42] = { 0 };
    initializeBoard(board);
    printBoard(board);
    while (1) {
        if (player == 'X')
        {
            player = 'O';
        }
        else
        {
            player = 'X';
        }
        checkMove(board, col, player, steps, i);
        printf("\nsteps %d\n", steps[i]);
        i++;
    }
    return 0;
}
void undo(char board[R][C], int steps[42], int i)
{
    if (i > 0)
    {
        board[lastMove(board, steps, i)][steps[i]] = ' ';
    }
}

void allTogether(char board[R][C], int col, char player, int count, int steps[42])
{
    count = -1;
    int valid = checkMove(board, col, player, steps, count);
    while (valid != 1)
    {
        scanf("%d", &col);
        checkMove(board, col, player, steps, count);
    }
    count++;
}
int lastMove(char board[R][C], int steps[42], int count)
{
    int laststep = 0, i;
    for (i = 0; i < R; i++)
    {
        if (board[i][steps[count]] != ' ')
        {
            laststep = i;
            return laststep;
        }
    }
    return laststep;
}
int emptyPlace(char board[R][C], int col)
{
    int row = -1;
    int i;
    for (i = 0; i < R; i++)
    {
        if (board[i][col - 1] == ' ') row++;
    }
    return row;
}
int inRange(int col)
{
    if (col >= 1 && col <= 7) return 1;
    return 0;
}
int checkMove(char board[R][C], int col, char player, int steps[42], int i)
{
    int range = 0;
    printTurn(player);
    scanf("%d", &col);
    int row = emptyPlace(board, col);
    range = inRange(col);
    if (col == 0)
    {
        undo(board, steps, i);
        printBoard(board);
        return 1;
    }
    if (row == -1)
    {
        printf("Invalid move. Column 3 is full.\nPlease try again:");
        return -2; // invalid
    }
    if (range == 0)
    {
        printf("Invalid move. Input move is out of range.\nPlease try again:");
        return 0;  //invalid
    }
    int cell = emptyPlace(board, col);
    board[cell][col - 1] = player;
    printf("%d\n", col);
    if (col != 0) {
        steps[i] = col;
        i++;
    }
    printBoard(board);
    return 1;     // valid move
}
void scanMove(int col)
{
    scanf("%d", &col);
}
void initializeBoard(char board[R][C])
{
    for (int i = 0; i < R; i++)
    {
        for (int j = 0; j < C; j++)
        {
            board[i][j] = ' ';
        }
    }
}
void printTurn(char player)
{
    printf("\nPlayer %c, in which column would you like to place your token? (enter 0 to undo)\n", player);
    return;
}
void printBoard(char board[R][C])
{
    for (int i = 0; i < R; i++)
    {
        for (int j = 0; j < C; j++)
        {
            printf("|%c", board[i][j]);
        }
        printf("|\n");
    }
    printf("---------------\n");
    for (int i = 1; i < C + 1; i++)
        printf(" %d", i);
}