#include<stdio.h>
#include<stdbool.h>
#define N 4

void printsol(int board[N][N]){
    for(int i = 0;i<N;i++){
        for(int j = 0;j<N;j++){
            printf("%c ", board[i][j]?'Q':'.');
        }
        printf("\n");
    }
    printf("\n");
}
bool issafe(int board[N][N], int row, int col){
    //check row of the col for queen
    for(int i = 0;i<N;i++){
        if(board[i][col])
            return false;
    }
    //check left diag
    for(int i = row,j = col;i>=0 && j>=0;i--,j--){
        if(board[i][j]){
            return false;
        }
    }
    //check right diag
    for(int i = row,j = col;i>=0 && j<N;i--,j++){
        if(board[i][j]){
            return false;
        }
    }
    return true;
}
void solvenqueens(int board[N][N], int row){
    if(row==N){//all queens placed
        printsol(board);
        return;
    }
    for(int col = 0;col<N;col++){
        if(issafe(board, row, col)){
            board[row][col] = 1;
            solvenqueens(board, row+1);
            board[row][col] = 0;
        }
    }
}
int main(){
    int board[N][N] = {0};
    solvenqueens(board, 0);
    return 0;

}
