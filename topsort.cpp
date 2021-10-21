#include <iostream>
#include <vector>

using namespace std;

const int N = 5005;          // number of vertices in graph
int v, e;
vector<int> edges[N];            // each vertex has a list of connected vertices
int ordering[N];

void add(int u, int v) {
    edges[u].push_back(v);
}

int dfs(int i, int v, bool visited[N]) {
    visited[v] = true;

    for (int dest : edges[v]) {
        if (!visited[dest]) {
                i = dfs(i, dest, visited);
        }
    }
    ordering[i] = v;
    return i - 1;
}

// returns the topsort ordering.
// note that a topsort ordering may not be unique.
void topsort() {
   bool visited[N]; 
   int i = v - 1;

   for (int j = 0; j < v; j++) {
       if(!visited[j]) {
                i = dfs(i, j, visited);
       }
   }
}

int main() {
    cin >> v >> e;
    for (int i = 0; i < e; i++) {
        int u, v;
        cin >> u >> v;
        add(u, v);
    }

    topsort();
    for (int i = 0; i < v; i++) {
        cout << ordering[i] << ' ';
    }

    return 0;
}
