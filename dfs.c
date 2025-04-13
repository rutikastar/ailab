#include<stdio.h>
#define m 9
int stack[m];
int visited[m];
int graph[m][m] = {{0, 1, 0, 0, 0, 0, 0, 0, 0},
{1, 0, 0, 1, 1, 0, 0, 0, 0},
{0, 0, 0, 1, 0, 0, 0, 0, 0},
{0, 1, 1, 0, 0, 1, 0 , 0, 0},
{0, 1, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 1, 0, 0, 1, 0, 1},
{0, 0, 0, 0, 0, 1, 0, 1, 0},
{0, 0, 0, 1, 0, 0, 1, 0, 1},
{0, 0, 0, 0, 0, 1, 0, 1, 0}};
int top = -1;

void dfs(int startvertex){
    stack[++top] = startvertex;
    while(top>-1){
        int node = stack[top--];
        if(!visited[node]){
        printf("%d ", node);
        visited[node] = 1;
        }
        for(int i = 0;i<m;i++){
            if(graph[node][i] == 1 && visited[i]!=1){
                stack[++top] = i;
            }
        }
    }
}
int main(){
    dfs(0);
}
