#include <iostream>
#include <vector>

using namespace std;

const int MAX = 500;
const int INF = 1e9;
vector<int> edges[MAX];
vector<vector<int>> dist(MAX, vector<int>(MAX));
int n;

void floyd() {
    // the distance between everything is infinity
    for (int u = 0; u < n; ++u)
        for (int v = 0; v < n; ++v) {
            dist[u][v] = INF;
        }

    // update the distances for every directed edge
    for (/* each edge u -> v with weight w */) dist[u][v] = w;

    // every vertex can reach itself
    for (int u = 0; u < n; ++u) dist[u][u] = 0;

    for (int i = 0; i < n; i++) {
      for (int u = 0; u < n; u++) {
        for (int v = 0; v < n; v++) {
          // dist[u][v] is the length of the shortest path from u to v using only 0 to i-1 as intermediate vertices
          // now that we're allowed to also use i, the only new path that could be shorter is u -> i -> v
          dist[u][v] = min(dist[u][v], dist[u][i] + dist[i][v]);
        }
      }
    }
}
