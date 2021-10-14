#include <iostream>
#include <vector>
#include <queue>

const int N = 1e6 + 5;
std::vector<int> edges[N];
// dist from start. -1 if unreachable.
int dist[N];
// previous node on a shortest path to the start
// Useful for reconstructing shortest paths
int prev[N];

void bfs(int start) {
    std::fill(dist, dist+N, -1);
    dist[start] = 0;
    prev[start] = -1;

    std::queue<int> q;
    q.push(start);
    while (!q.empty()) {
        int c = q.front();
        q.pop();
        for (int nxt : edges[c]) {
            // Push if we have not seen it already.
            if (dist[nxt] == -1) {
                dist[nxt] = dist[c] + 1;
                prev[nxt] = c;
                q.push(nxt);
            }
        }
    }
}