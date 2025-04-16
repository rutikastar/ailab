Best first search
#include <stdio.h>
#include <limits.h>

#define S 6
#define INF INT_MAX

// Heuristic values for each node
int h[S] = {5, 3, 4, 2, 6, 0};

// Adjacency matrix (edges between nodes)
int graph[S][S] = {
    {0, 1, 0, 0, 0, 10},
    {0, 0, 2, 1, 0, 0},
    {0, 0, 0, 0, 5, 0},
    {0, 0, 0, 0, 3, 4},
    {0, 0, 0, 0, 0, 2},
    {0, 0, 0, 0, 0, 0}
};

void bestFirstSearch(int start, int goal) {
    int visited[S] = {0};
    int parent[S];
    for (int i = 0; i < S; i++) parent[i] = -1;

    int open[S];
    int openSize = 0;

    open[openSize++] = start;
    visited[start] = 1;

    while (openSize > 0) {
        // Find node with lowest heuristic in open list
        int minIndex = 0;
        for (int i = 1; i < openSize; i++) {
            if (h[open[i]] < h[open[minIndex]]) {
                minIndex = i;
            }
        }

        // Pop the best node
        int current = open[minIndex];
        open[minIndex] = open[--openSize];

        printf("Visited: %d\n", current);

        if (current == goal) break;

        // Explore neighbors
        for (int i = 0; i < S; i++) {
            if (graph[current][i] > 0 && !visited[i]) {
                visited[i] = 1;
                open[openSize++] = i;
                parent[i] = current;
            }
        }
    }

    // Print path
    if (!visited[goal]) {
        printf("No path found\n");
        return;
    }

    int path[S], idx = 0;
    int temp = goal;
    while (temp != -1) {
        path[idx++] = temp;
        temp = parent[temp];
    }

    printf("Path: ");
    for (int i = idx - 1; i >= 0; i--) {
        printf("%d ", path[i]);
    }
    printf("\n");
}

int main() {
    int start = 0, goal = 5;
    printf("Best-First Search from %d to %d:\n", start, goal);
    bestFirstSearch(start, goal);
    return 0;
}

