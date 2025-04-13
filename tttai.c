#include<stdio.h>
#include<limits.h>
#define AI 'X'
#define PLAYER 'O'
char board[3][3];

void initboard(){
    for(int i = 0;i<3;i++){
        for(int j = 0;j<3;j++){
            board[i][j] = ' ';
        }
    }
}
void displayboard(){
    for(int i = 0;i<3;i++){
        for(int j =0;j<3;j++){
            printf("%c ", board[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}
char checkwinner(){
    for(int i = 0;i<3;i++){
        if(board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0]!=' '){
            return board[i][0];
        }
        if(board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] != ' '){
            return board[0][i];
        }
        if(board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != ' '){
            return board[0][0];
        }
        if(board[0][2] == board[1][1] && board[1][1]==board[2][0] && board[0][2]!= ' '){
            return board[0][2];
        }
    }
    return ' ';
}
int isMovesLeft(){
    for(int i = 0;i<3;i++){
        for(int j = 0;j<3;j++){
            if(board[i][j]==' '){
                return 1;
            }
        }
    }
    return 0;
}
int evaluate(){
    char winner = checkwinner();
    if(winner == AI){
        return 10;
    }else if(winner == PLAYER){
        return -10;
    }
    return 0;

}
int minimax(int depth, int isMaximizing){
    int score = evaluate();
    if(score == 10){
        return score;
    }
    if(score==-10){
        return score;

    }
    if(!isMovesLeft()){
        return 0;
    }
    if(isMaximizing){
        int max_eval = INT_MIN;
        for(int i = 0;i<3;i++){
            for(int j = 0;j<3;j++){
                if(board[i][j] == ' '){
                    board[i][j] = AI;
                    int eval = minimax(depth+1, 0);
                    board[i][j] = ' ';
                    if(eval>max_eval){
                        max_eval = eval;
                    }
                }
            }
        }
        return max_eval;
    }
    else{
        int min_eval = INT_MAX;
        for(int i = 0;i<3;i++){
            for(int j = 0;j<3;j++){
                if(board[i][j] == ' '){
                    board[i][j] = PLAYER;
                    int eval = minimax(depth+1, 1);
                    board[i][j] = ' ';
                    if(eval<min_eval){
                        min_eval = eval;
                    }
                }
            }
        }
        return min_eval;
    }
}
int AImoves(){
    int bestmove=INT_MIN, row = -1, col = -1;
    for(int i = 0;i<3;i++){
        for(int j = 0;j<3;j++){
            if(board[i][j] == ' '){
                board[i][j] = AI;
                int eval = minimax(0, 0);
                board[i][j] = ' ';
                if(eval>bestmove){
                    bestmove = eval;
                    row = i;
                    col = j;
                }
            }
        }
    }
    if(row!=-1 && col!=-1){
    board[row][col] = AI;

    printf("AI has played its move \n");
    }
}
int PlayerMoves(){
    int row, col;
    do{
        printf("Enter choice (row, col): \n");
        scanf("%d %d", &row, &col);
        row--;
        col--;
    }while(row<0||row>2||col<0||col>2||board[row][col]!= ' ');
    board[row][col] = PLAYER;
}
int main(){
    initboard();
    displayboard();
    while(1){
        PlayerMoves();
        displayboard();
        if(checkwinner() == PLAYER){
            printf("PLAYER WINS\n");
            break;
        }
        if(!isMovesLeft()){
            printf("DRAW!!");
            break;
        }
        AImoves();
        displayboard();
        if(checkwinner() == AI){
            printf("AI WINS\n");
            break;
        }
        if(!isMovesLeft()){
            printf("DRAW!!");
            break;
        }
    }
}
