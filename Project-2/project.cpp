#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int *Root;
int *Rank;


class Edge {
public:
    int v1;
    int v2;
    int weight;

    Edge(int a, int b, int w) {
        v1 = a;
        v2 = b;
        weight = w;
    }
};


class Graph {
public:
    int E;
    vector<Edge> edges;

    Graph(int e) {
        E = e;
    }

    void addEdge(int v1, int v2, int w) {
        Edge edge(v1, v2, w);
        edges.push_back(edge);
    }
};


bool sortByWeight(Edge e1, Edge e2) {
    return e1.weight > e2.weight;
}


int FINDSET(int n) {
    if (Root[n] == -1) {
        return n;
    }
    Root[n] = FINDSET(Root[n]);
    return Root[n];
}

void UNION(int a, int b) {
    int v1 = FINDSET(a);
    int v2 = FINDSET(b);

    if (v1 != v2) {
        if (Rank[v1] < Rank[v2]) {
            Root[v1] = v2;
            Rank[v2] += Rank[v1];
        }
        else {
            Root[v2] = v1;
            Rank[v1] += Rank[v2];
        }
    }
}


// Kruskal's algorithm
int calculateMST(Graph &graph, int E) {
    int total = 0;
    sort(&graph.edges[0], &graph.edges[graph.E+1], sortByWeight);
    vector<Edge> sorted_edges = graph.edges;

    for (int i = 0; i < E; i++) {
        int v1 = sorted_edges[i].v1 -1;
        int v2 = sorted_edges[i].v2 - 1;

        if (FINDSET(v1) != FINDSET(v2)) {
            UNION(v1, v2);
            total += sorted_edges[i].weight;
        }
    }
    return total;
}


int main() {
    int V, E;
    if (scanf("%d %d", &V, &E) != 2) return -1;
// Initialize a graph with V vertices and E edges
    Graph graph(E);

    Root = new int[V];
    Rank = new int[V];

    for (int i = 0; i < V; i++) {
        Root[i] = -1;
        Rank[i] = 1;
    }

    for (int i = 0; i < E; i++) {
        int u, v, w;
        if (scanf("%d %d %d", &u, &v, &w) != 3) return -1;

        // Add an edge between u and v with weight w
        graph.addEdge(u, v, w);
    }
    printf("%d\n", calculateMST(graph, E));
    return 0;
}