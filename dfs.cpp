#include <iostream>
#include <vector>

const int N = 1e6 + 5;          // number of vertices in graph
std::vector<int> edges[N];      // each vertex has a list of connected vertices
bool seen[N];

void dfs(int u) {
    if (seen[u]) return;
    seen[u] = true;
    for (int v : edges[u]) dfs(v);
}