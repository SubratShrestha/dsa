#include <iostream>
#include <vector>

using namespace std;

const int N = 10000;          // number of vertices in graph
const int V = 13;
const int E = 18;
vector<int> edges[V];            // each vertex has a list of connected vertices
int ordering[V];

void add(int u, int v) {
    edges[u].push_back(v);
}

int dfs(int i, int v, bool visited[V]) {
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
       bool visited[V]; 
       int i = V - 1;

       for (int v = 0; v < V; v++) {
               if(!visited[v]) {
                        i = dfs(i, v, visited);
               }
       }
}

int main() {
        int u, v;
        for (int i= 0; i < E; i++) {
                cin >> u >> v;
                add(u, v);
        }

        topsort();
        for (auto i : ordering) {
                cout << i << ' ';
        }
        return 0;
}
