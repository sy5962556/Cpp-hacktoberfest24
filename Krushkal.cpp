#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Edge {
    int src, dest, weight;
};

struct DisjointSets {
    int *parent, *rank;
    int n;

    DisjointSets(int n) {
        this->n = n;
        parent = new int[n];
        rank = new int[n];

        for (int i = 0; i < n; i++) {
            parent[i] = -1;
            rank[i] = 1;
        }
    }

    int find(int i) {
        if (parent[i] == -1)
            return i;

        return parent[i] = find(parent[i]);
    }

    void unionSets(int x, int y) {
        int s1 = find(x);
        int s2 = find(y);

        if (s1 != s2) {
            if (rank[s1] < rank[s2]) {
                parent[s1] = s2;
            } else if (rank[s1] > rank[s2]) {
                parent[s2] = s1;
            } else {
                parent[s2] = s1;
                rank[s1] += 1;
            }
        }
    }
};

bool compareEdges(Edge e1, Edge e2) {
    return e1.weight < e2.weight;
}

void kruskals(vector<Edge> &edges, int V) {
    sort(edges.begin(), edges.end(), compareEdges);

    DisjointSets ds(V);

    vector<Edge> mst;

    for (Edge edge : edges) {
        int x = ds.find(edge.src);
        int y = ds.find(edge.dest);

        if (x != y) {
            mst.push_back(edge);
            ds.unionSets(x, y);
        }
    }

    cout << "Minimum Spanning Tree: " << endl;
    for (Edge edge : mst) {
        cout << edge.src << " -- " << edge.dest << " : " << edge.weight << endl;
    }
}

int main() {
    int V = 4;  // Number of vertices
    int E = 5;  // Number of edges

    vector<Edge> edges;

    edges.push_back({0, 1, 10});
    edges.push_back({0, 2, 6});
    edges.push_back({0, 3, 5});
    edges.push_back({1, 3, 15});
    edges.push_back({2, 3, 4});

    kruskals(edges, V);

    return 0;
}
