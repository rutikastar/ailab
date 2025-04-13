#include<stdio.h>
#include <stdbool.h>
#define N 4
#include<limits.h>

void printsol(int color[]){//printing assigned color of all vertices
    printf("solution is - ");
    for(int i =0;i<N;i++){
        printf("%d ", color[i]);
    }
    printf("\n");
}
bool canColor(int graph[N][N], int m, int color[], int vertex, int vertex_color){
    for(int i = 0;i<N;i++){
        if(graph[vertex][i] && color[i]==vertex_color){
            return false;
        }
    }
    return true;
}

bool graphColoringBT(int graph[N][N], int m, int color[], int vertex){
    if(vertex == N){
        printsol(color);
        return true;
    }
    for(int i= 1;i<=m;i++){
        if(canColor(graph,m,color, vertex, i)){
            color[vertex] = i;
            if(graphColoringBT(graph,m,color, vertex+1)){
                return true;
            }
            color[vertex] = 0;
        }
    }
    return false;
}
void graphcoloring(int graph[N][N], int m){
    int color[N] = {0};
    if(!graphColoringBT(graph,m,color,0)){
        printf("no solutions\n");
    }
}

int main(){
    int graph[N][N] = {
        {0, 1, 1, 1},
        {1, 0, 1, 0},
        {1, 1, 0, 1},
        {1, 0, 1, 0}
    };
    printf("1- green, 2-blue, 3-red, 4-yellow, 5-pink\n");

    int m = 5; //5 colors
    printf("total colors given - %d\n", m);
    graphcoloring(graph, m);
    return 0;

}
