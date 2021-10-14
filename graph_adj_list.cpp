#include <iostream>
#include <vector>

const int N = 1e6 + 5;          // number of vertices in graph
std::vector<int> edges[N];      // each vertex has a list of connected vertices

void add(int u, int v) {
    edges[u].push_back(v);
    // Warning: If the graph has self-loops, you need to check this.
    if (v != u) {
        edges[v].push_back(u);
    }
}

int main() {
    // iterate over edges from u (since C++11)
    int u = 0;
    for (int v : edges[u]) std::cout << v << '\n';
}