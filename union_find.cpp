#include<iostream>
using namespace std;

const int N = 100000;
int parent[N];
int subtree_size[N];  

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
