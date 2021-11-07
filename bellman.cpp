#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct edge {
    int u;
    int v;
    int d;
};

int N, M;
vector<edge> edges;
const int INF = 1e9;
vector<int> dist(N, INF);
vector<int> path;

void bellman() {
    int s = 0;
    dist[s] = 0;
    vector<int> prev(N, -1);

    // relax all edges at most N-1 times.
    for (int i = 0; i < N - 1; i++) {
        bool hasChanges = false;

        for (int j = 0; j < M; j++) {
            if (dist[edges[j].u] < INF) {
                dist[edges[j].v] = min(dist[edges[j].v], dist[edges[j].u] + edges[j].d);
                prev[edges[j].v] = edges[j].u;
                hasChanges = true;
            }
        }

        if (!hasChanges) break;
    }

    // getting path.
    int dest = N-1;
    if (dist[dest] == INF)
        cout << "no path from source = " << s << " to destination = " << dest << '\n';
    else {
        int cur = dest;
        while (cur != -1) {
            path.push_back(cur);
            cur = prev[cur];
        }
        reverse(path.begin(), path.end());
    }
}
