#include <stdio.h>
#include <limits.h>
#include <string.h>

#define MAX_NODES 10
#define MAX_GROUPS 5
#define MAX_GROUP_SIZE 3

typedef struct {
    char name;
    int heuristic_value;
    int solved;
    int num_groups;
    int group_size[MAX_GROUPS];
    int group_nodes[MAX_GROUPS][MAX_GROUP_SIZE]; // Stores indices of child nodes
    int group_costs[MAX_GROUPS][MAX_GROUP_SIZE]; // Corresponding edge costs
} Node;

Node graph[MAX_NODES];
int total_nodes = 0;

// Map character name to index
int getNodeIndex(char name) {
    for (int i = 0; i < total_nodes; i++) {
        if (graph[i].name == name)
            return i;
    }
    return -1;
}

void addNode(char name, int hval) {
    graph[total_nodes].name = name;
    graph[total_nodes].heuristic_value = hval;
    graph[total_nodes].solved = 0;
    graph[total_nodes].num_groups = 0;
    total_nodes++;
}

void addOrEdge(char from, char to[], int costs[], int size) {
    int fromIndex = getNodeIndex(from);
    int groupIndex = graph[fromIndex].num_groups++;

    for (int i = 0; i < size; i++) {
        graph[fromIndex].group_nodes[groupIndex][i] = getNodeIndex(to[i]);
        graph[fromIndex].group_costs[groupIndex][i] = costs[i];
    }
    graph[fromIndex].group_size[groupIndex] = size;
}

void AOStar(int nodeIndex, int visited[]) {
    if (graph[nodeIndex].solved || visited[nodeIndex]) return;

    visited[nodeIndex] = 1;

    int min_cost = INT_MAX;
    int best_group = -1;

    for (int g = 0; g < graph[nodeIndex].num_groups; g++) {
        int cost = 0;
        for (int j = 0; j < graph[nodeIndex].group_size[g]; j++) {
            int child = graph[nodeIndex].group_nodes[g][j];
            cost += graph[nodeIndex].group_costs[g][j] + graph[child].heuristic_value;
        }
        if (cost < min_cost) {
            min_cost = cost;
            best_group = g;
        }
    }

    if (best_group != -1)
        graph[nodeIndex].heuristic_value = min_cost;

    for (int j = 0; j < graph[nodeIndex].group_size[best_group]; j++) {
        int child = graph[nodeIndex].group_nodes[best_group][j];
        AOStar(child, visited);
    }

    int allSolved = 1;
    for (int j = 0; j < graph[nodeIndex].group_size[best_group]; j++) {
        int child = graph[nodeIndex].group_nodes[best_group][j];
        if (!graph[child].solved) {
            allSolved = 0;
            break;
        }
    }

    if (allSolved) graph[nodeIndex].solved = 1;
}

void printSolution(int nodeIndex) {
    printf("%c", graph[nodeIndex].name);

    if (graph[nodeIndex].num_groups == 0) return;

    int min_cost = INT_MAX;
    int best_group = -1;

    for (int g = 0; g < graph[nodeIndex].num_groups; g++) {
        int cost = 0;
        for (int j = 0; j < graph[nodeIndex].group_size[g]; j++) {
            int child = graph[nodeIndex].group_nodes[g][j];
            cost += graph[nodeIndex].group_costs[g][j] + graph[child].heuristic_value;
        }
        if (cost < min_cost) {
            min_cost = cost;
            best_group = g;
        }
    }

    for (int j = 0; j < graph[nodeIndex].group_size[best_group]; j++) {
        int child = graph[nodeIndex].group_nodes[best_group][j];
        printf(" --%d--> ", graph[nodeIndex].group_costs[best_group][j]);
        printSolution(child);
    }
}

int main() {
    addNode('A', 5);
    addNode('B', 6);
    addNode('C', 4);
    addNode('D', 3);
    addNode('E', 3);
    addNode('F', 1);
    addNode('G', 0);

    // A → B(1) or C(4)
    addOrEdge('A', (char[]){'B'}, (int[]){1}, 1);
    addOrEdge('A', (char[]){'C'}, (int[]){4}, 1);

    // B → C(2) or D(3)
    addOrEdge('B', (char[]){'C'}, (int[]){2}, 1);
    addOrEdge('B', (char[]){'D'}, (int[]){3}, 1);

    // C → E(5)
    addOrEdge('C', (char[]){'E'}, (int[]){5}, 1);

    // D → F(2) and G(4)
    addOrEdge('D', (char[]){'F', 'G'}, (int[]){2, 4}, 2);

    // E → G(3)
    addOrEdge('E', (char[]){'G'}, (int[]){3}, 1);

    // F → G(1)
    addOrEdge('F', (char[]){'G'}, (int[]){1}, 1);

    int visited[MAX_NODES] = {0};
    AOStar(getNodeIndex('A'), visited);

    printf("\nFinal Heuristic Value of A: %d\n", graph[getNodeIndex('A')].heuristic_value);
    printf("Final Solution Subgraph: ");
    printSolution(getNodeIndex('A'));
    printf("\n");

    return 0;
}
