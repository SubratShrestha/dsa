#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int INF = 1e9;
const int MAX = 1000;
int V, E;
int s, t;
int start[MAX];             // index of first outgoing edge of vertex
int succ[MAX];              // next outgoing edge of of same vertex as edge e 
int cap[MAX];               // capacity of edge
int to[MAX];                // destination vertex of edge
int level[MAX];
int next_child[MAX];        // the next useless child

int edge_counter = 0;

void init() {
    for (auto &i : start) i = -1;
}

void add_edge(int u, int v, int c) {
    cap[edge_counter] = c;
    to[edge_counter] = v;

    // add this edge to start of u's list of outgoing edges.
    succ[edge_counter] = start[u];
    start[u] = edge_counter;
    edge_counter++;
}

// toggle between residual and original.
int inv(int e) {
    return e ^ 1;
}

// construct the level graph using bfs and check if sink is reachable.
bool bfs() {
    for (auto &i : level) i = -1;
    
    queue<int> q;
    level[s] = 0;
    q.push(s);
    
    while (!q.empty()) {
        int u = q.front(); q.pop();
        next_child[u] = start[u];

        // loop through all outgoing edges of u.
        for (int e = start[u]; e != -1; e = succ[e]) {
            if (cap[e] > 0) {
                int v = to[e];
                if (level[v] != -1) continue;   // seen
                level[v] = level[u] + 1;
                q.push(v);
            }
        }
    }

    return level[t] != -1;
}

// Find augmenting path only using nodes in level graph using dfs.
int dfs(int u, int flow = INF) {
    if (u == t) return flow;                // reached sink

    // note the reference here. We need to modify the value here.
    for (int &i = next_child[u]; i >= 0; i = succ[i]) {
        if (cap[i] > 0) {
            int next = to[i];

            // ignore edges that are not in level graph
            if (level[next] != level[u] + 1) continue;
            
            int cur_flow = dfs(next, min(flow, cap[i]));

            // found child we can flow through
            if (cur_flow > 0) { 
                cap[i] -= cur_flow;
                cap[i ^ 1] += cur_flow;
                return cur_flow;
            }
        }
    }

    level[u] = -1;
    return 0;
}

int max_flow() {
    int mf = 0;
    // try to find a path as long as a level graph can be constructed and the sink
    // can be reached.
    while (bfs()) {
        int flow = dfs(s);
        while (flow) {
            mf += flow;
            flow = dfs(s);
        }
    }

    return mf;
}

int main() {
    cin >> V >> E;
    cin >> s >> t;
    init();
    for (int i = 0; i < E; i++) {
        int u, v, c;
        cin >> u >> v >> c;
        add_edge(u, v, c);
        add_edge(v, u, 0);
    }

    cout << "Max flow = " << max_flow() << '\n';
    return 0;
}
