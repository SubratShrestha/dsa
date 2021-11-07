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
    int x;

    // relax all edges at most N-1 times.
    for (int i = 0; i < N - 1; i++) {
        x = -1;
        bool hasChanges = false;

        for (int j = 0; j < M; j++) {
            if (dist[edges[j].u] < INF) {
                if (dist[edges[j].v] < dist[edges[j].u] + edges[j].d) {
                    dist[edges[j].v] = max(-INF, dist[edges[j].u] + edges[j].d);
                    prev[edges[j].v] = edges[j].u;
                    hasChanges = true;
                    x = edges[j].v;
                }
            }
        }

        if (!hasChanges) break;
    }

    if (x == -1) {
        cout << "no negative cycle\n";

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
    } else {
        // get negative cycle path.
        cout << "negative cycle\n";
        int y = x;
        for (int i = 0; i < N; i++) {
            y = prev[y];
        }

        for (int cur = y; ; cur = prev[cur]) {
            path.push_back(cur);
            if (cur == y && path.size() > 1)
                break;
        }
        reverse(path.begin(), path.end());
    }
}
