#include<stdio.h>
#define n 9
int queue[n];
int graph[n][n]={{0, 1, 0, 0, 0, 0, 0, 0, 0},
{1, 0, 0, 1, 1, 0, 0, 0, 0},
{0, 0, 0, 1, 0, 0, 0, 0, 0},
{0, 1, 1, 0, 0, 1, 0 , 0, 0},
{0, 1, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 1, 0, 0, 1, 0, 1},
{0, 0, 0, 0, 0, 1, 0, 1, 0},
{0, 0, 0, 1, 0, 0, 1, 0, 1},
{0, 0, 0, 0, 0, 1, 0, 1, 0}};
int front = 0, rear = 0;
int visited[n];
void bfs(int startvertex){
    queue[rear++] = startvertex; //enque
    visited[startvertex] = 1;
    while(front<rear){
        int node = queue[front++];
        printf("%d ", node);
        for(int i = 0;i<n;i++){
            if(graph[node][i]==1 && visited[i]!=1){
                queue[rear++] = i;
                visited[i] = 1;
            }
        }
    }
}
int main(){
    bfs(0);
}
