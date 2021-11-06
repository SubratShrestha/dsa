#include <iostream>
#include <queue>
#include <vector>

using namespace std;

const int MAX = 999;
typedef pair<int, int> edge;          // (distance, vertex)
priority_queue<edge, vector<edge>, greater<edge>> pq;

vector<edge> edges[MAX];
int dist[MAX];
bool seen[MAX];

void dijkstra() {
    // push source to queue 
    int s = 0;
    pq.push(edge(0, s));

    while (!pq.empty()) {
        edge cur = pq.top(); pq.pop();
        int v = cur.second;
        int d = cur.first;

        if (seen[v]) continue;

        dist[v] = d;
        seen[v] = true;

        // relax all outgoing edges from v
        for (int i = 0; i < edges[v].size(); i++) {
            edge next = edges[v][i];
            int u = next.second;
            int weight = next.first;

            if (!seen[u])
                pq.push(edge(d + weight, u));
        }
    }
}
