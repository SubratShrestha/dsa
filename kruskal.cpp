#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

typedef struct edge {
    int u;
    int v;
    long long w;
    edge(int _u, int _v, long long _w) {u = _u; v = _v; w = _w;}
} edge;

vector<edge> edges;
const int N = 100000;
int parent[N];
int subtree_size[N];
long long res;

void init(int n) {
    for (int i = 0; i < n; i++) {
        parent[i] = i; subtree_size[i] = 1;
    }
}

int root(int x) {
  // only roots are their own parents
  // otherwise apply path compression
  return parent[x] == x ? x : parent[x] = root(parent[x]);
}

void join(int x, int y) {
    // size heuristic
    // hang smaller subtree under root of larger subtree
    x = root(x); y = root(y);
    if (x == y) return;
    if (subtree_size[x] < subtree_size[y]) {
        parent[x] = y;
        subtree_size[y] += subtree_size[x];
    } else {
        parent[y] = x;
        subtree_size[x] += subtree_size[y];
    }
}

bool sort_by_weights(edge e1, edge e2) {
    return e1.w < e2.w;
}

void kruskal() {
    // sort the edges in ascending order of weights
    // if both vertices are not in any group, make new group
    // if both are in different groups, union
    // if both are in the same group, ignore.
    sort(edges.begin(), edges.end(), sort_by_weights);
    for (int i = 0; i < (int)edges.size(); i++) {
        int u = root(edges[i].u);
        int v = root(edges[i].v);
        
        if (u == v) continue;
        else {
            join(u, v);
            res = max(res, edges[i].w);
        }
    }
}

int main() {
    int n, m; cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u; int v; long long w;
        cin >> u >> v >> w;
        edge e = edge(u, v, w);
        edges.push_back(e);
    }

    init(n);
    kruskal();
    cout << res << '\n'; 
    return 0;
}
