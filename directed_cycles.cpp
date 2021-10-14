#include <iostream>
#include <vector>

const int N = 1e6 + 5;          // number of vertices in graph
std::vector<int> edges[N];      // each vertex has a list of connected vertices
bool seen[N];
bool active[N];

// the vertices that are still marked active when this returns are the ones in the cycle we detected
bool has_cycle(int u) {
    if (seen[u]) return false;
    seen[u] = true;
    active[u] = true;
    for (int v : edges[u]) {
    if (active[v] || has_cycle(v)) return true;
    }
    active[u] = false;
    return false;
}