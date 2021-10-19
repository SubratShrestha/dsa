/*
    Given a tree of size N, a vertex v and integer k,
    find the k-th ancestor of v.

    Reference: https://www.youtube.com/watch?v=oib-XsjFa-M
*/

#include<iostream>
#include<vector>
using namespace std;

const int N = 1000000;
const int LOG = 20;
vector<int> edges[N];
int parent[N][LOG];                         // parent[i][j] = (2^j)th ancestor of i.
int direct_parent[N];
int depth[N];

void preprocess() {
    direct_parent[0] = 0;
    for (int v = 0; v < N; v++) {
        parent[v][0] = direct_parent[v];
        if (v != 0) {
            depth[v] = depth[direct_parent[v]] + 1;
        }
        for (int j = 1; j < LOG; j++) {
            parent[v][j] = parent[ parent[v][j-1] ][j-1];
        }
    }
}

int getKthAncestor(int node, int k) {
    if (depth[node] < k) {
        return -1;
    }
    for (int j = 0; j < LOG; j++) {
        if (k & (1 << j)) {
            node = parent[node][j];
        }
    }

    return node;
}