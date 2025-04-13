#include<stdio.h>
char board[3][3];

void initboard(){
    int count = 1;
    for(int i = 0;i<3;i++){
        for(int j = 0;j<3;j++){
            board[i][j] = count+'0';
            count++;
        }
    }
}

void displayboard(){
    printf("\n");
    for(int i = 0;i<3;i++){
        for(int j = 0;j<3;j++){
            printf("%c ", board[i][j]);
        }
        printf("\n");
    }
}

int checkWin(){
    for(int i = 0;i<3;i++){
        if((board[i][0] == board[i][1] && board[i][1] == board[i][2]) || (board[0][i] == board[1][i] && board[1][i] == board[2][i])){
        return 1;
        }
    }
    if((board[0][0] == board[1][1] && board[1][1] == board[2][2]) || (board[0][2] == board[1][1] && board[1][1] == board[2][0])){
        return 1;
    }
    return 0;
}

int isDraw(){
    for(int i = 0;i<3;i++){
        for(int j = 0;j<3;j++){
            if(board[i][j]!='X' && board[i][j] != 'O'){
                return 0; //empty spaces found
            }
        }
    }
    return 1; //no empty spaces draw
}

void playGame(){
    int player = 1, choice, row, col;
    char mark;
    initboard();
    do{
        displayboard();
        player = (player%2)?1:2; //which players chance is it
        mark = (player == 1)?'X':'O'; //if plyer1 - then mark is x, else o

        printf("player %d, pls enter num from 0 to 9: ", player);
        scanf("%d", &choice);
        row = (choice-1)/3;
        col = (choice - 1)%3;

        if(choice < 1 || choice > 9 || board[row][col] == 'X' || board[row][col] == 'O'){
            printf("Invalid move! Try again.\n");
            player--; //same players turn
        }else{
            board[row][col] = mark;
        }

        if(checkWin()){
            displayboard();
            printf("player %d wins!\n", player);
            return;
        }
        player++;

    }while(!isDraw());
    displayboard();
    printf("draw lol\n");
}
int main(){
    playGame();
    return 0;
}
