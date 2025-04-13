#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#define S 6
#define INF INT_MAX
int hn[S] = {5, 3, 4, 2, 6, 0}; 
int adjmatrix[S][S] = {
    {0, 1, 0, 0 , 0, 10},
    {0, 0, 2, 1, 0, 0},
    {0, 0, 0, 0, 5, 0},
    {0, 0, 0, 0, 3, 4},
    {0, 0, 0, 0, 0, 2},
    {0, 0, 0, 0, 0, 0}
};

void astar(int start, int goal) {
    int gn[S], fn[S], ol[S], cl[S], parent[S];
    int openSize = 0;  

    //Initialize all arrays
    for (int i = 0; i < S; i++) {
        gn[i] = INF;
        fn[i] = INF;
        parent[i] = -1;
        cl[i] = 0;
        ol[i] = 0;
    }

    //Start node initialization
    gn[start] = 0;
    fn[start] = gn[start] + hn[start];
    ol[start] = 1;
    openSize++;

    while (openSize > 0) {
        int minFn = INF, current = -1;

        //Find node with the lowest f(n) in open list
        for (int i = 0; i < S; i++) {
            if (ol[i] == 1 && fn[i] < minFn) {
                minFn = fn[i];
                current = i;
            }
        }

        //No more nodes to process
        if (current == -1) break;
        
        //If we reached the goal, stop
        if (current == goal) break;

        //Remove from open list, add to closed list
        ol[current] = 0;
        openSize--;
        cl[current] = 1;

        //Explore neighbors
        for (int i = 0; i < S; i++) {
            if (adjmatrix[current][i] > 0 && cl[i] == 0) { // Only consider directed edges
                int tempG = gn[current] + adjmatrix[current][i];

                //If new path is better, update
                if (ol[i] == 0 || tempG < gn[i]) {
                    gn[i] = tempG;
                    fn[i] = gn[i] + hn[i];
                    parent[i] = current;
                    ol[i] = 1;
                    openSize++;
                }
            }
        }
    }

    if (gn[goal] == INF) {
        printf("No path found from %d to %d\n", start, goal);
        return;
    }

    printf("Shortest path: ");
    int path[S], index = 0, final = goal;
    while (final != -1) {
        path[index++] = final;
        final = parent[final];
    }
    for (int i = index - 1; i >= 0; i--) {
        printf("%d ", path[i]);
    }
    printf("\nTotal cost: %d\n", gn[goal]);
}

int main() {
    int start = 0, goal = 5;
    printf("Finding shortest path from %d to %d using A* Algorithm\n", start, goal);
    astar(start, goal);
    return 0;
}
