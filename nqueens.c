#include <stdio.h>
#include <stdbool.h>

#define N 8  // Change this for a different board size

int solutions = 0; // Counter for the number of solutions

// Function to print the board
void printSolution(int board[N][N]) {
    printf("\nSolution %d:\n", ++solutions);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf(board[i][j] ? " Q " : " . ");
        }
        printf("\n");
    }
}
bool isSafe(int board[N][N], int row, int col) {
    for (int i = 0; i < row; i++)
        if (board[i][col]) return false;
    for (int i = row, j = col; i >= 0 && j >= 0; i--, j--)
        if (board[i][j]) return false;
    for (int i = row, j = col; i >= 0 && j < N; i--, j++)
        if (board[i][j]) return false;

    return true;
}
void solveNQueens(int board[N][N], int row) {
    if (row == N) {  
        printSolution(board);
        return;
    }

    for (int col = 0; col < N; col++) {
        if (isSafe(board, row, col)) {
            board[row][col] = 1; // Place queen
            solveNQueens(board, row + 1); // Recur for next row
            board[row][col] = 0; // Backtrack and remove queen
        }
    }
}

// Driver function
int main() {
    int board[N][N] = {0}; // Initialize empty board
    solveNQueens(board, 0);

    printf("\nTotal solutions found: %d\n", solutions);
    return 0;
}
