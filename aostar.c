#include<stdio.h>
#include<limits.h>
#define n 6
#define inf INT_MAX
int h[n] = {5, 3, 4, 2, 6,0};
int graph[n][n] = {
    {0, 1, 0, 0, 0, 10},  
    {0, 0, 2, 1, 0, 0},   
    {0, 0, 0, 0, 5, 0},   
    {0, 0, 0, 0, 3, 4},  
    {0, 0, 0, 0, 0, 2},   
    {0, 0, 0, 0, 0, 0} 
};
int g[n], parent[n], solved[n];

void aostar(int node){
    if(solved[node]){return;}
    int mincost = inf;
    int bestchild = -1;

    for(int i = 0; i < n; i++){
        if(graph[node][i]>0){
            aostar(i);
            int cost = g[i]+graph[node][i];
            if(cost<mincost){
                mincost = cost;
                bestchild = i;
            }
        }
    }
    if(bestchild !=-1){
        g[node] = mincost;
        h[node] = mincost;
        parent[node] = bestchild;
    }
    solved[node] = 1;
}
void printSolution(int start, int goal) {
    printf("optimal path: ");
    int current = start;
    while (current != goal) {
        printf("%d ", current);
        current = parent[current];
    }
    printf("%d\n", goal);
    printf("total cost: %d\n", g[start]);
}

int main() {
    for (int i = 0; i < n; i++) {
        g[i] = inf;
        parent[i] = -1;
        solved[i] = 0;
    }
    g[n-1] = 0;

    int start = 0, goal = 5;
    aostar(start);
    printSolution(start, goal);
}
