/*
    Given two vertices A and B in a tree at certain depths, find the lowest common
    common ancestor of A and B.
*/

#include<iostream>
#include<vector>
using namespace std;

const int N = 10000;
const int LOG = 14;
vector<int> edges[N];
int parent[N][LOG];                         // parent[i][j] = (2^j)th ancestor of i.
int depth[N];

void dfs(int a) {
    for (int b : edges[a]) {
        depth[b] = depth[a] + 1;
        parent[b][0] = a;                   // a is 0th parent of b.
        for (int j = 1; j < LOG; j++) {
            parent[b][j] = parent[parent[b][j-1]][j-1];
        }

        dfs(b);
    }
}

int lca(int a, int b) {
    // // BRUTE FORCE : O(N) per query
    // if (depth[a] < depth[b]) {
    //     swap(a, b);
    // }

    // // get them at the same level.
    // while (depth[a] < depth[b]) {
    //     a = parent[b][0];
    // }

    // // move them up until they are the same.
    // while (a != b) {
    //     a = parent[a][0];
    //     b = parent[b][0];
    // }

    // return a;


    // USE BINARY LIFTING, O(log N) per query
    if (depth[a] < depth[b]) {
        swap(a, b);
    }
    int k = depth[a] - depth[b];
    for (int j = LOG - 1; j >= 0; j--) {            // move them up until they are the same.
        if (k & (1 << j)) {
            a = parent[a][j];
        }
    }

    if (a == b) return a;

    for (int j = LOG - 1; j >= 0; j--) {
        if (parent[a][j] != parent[b][j]) {
            a = parent[a][j];
            b = parent[b][j];
        }
    }

    return parent[a][0];
}

// note: here root is guaranteed to be 0.
int main() {
    int n; cin >> n;                        // number of nodes labelled 0 - (n-1)
	for(int v = 0; v < n; ++v) {
		// read children of v
		int cnt;
		cin >> cnt;
		for(int i = 0; i < cnt; i++) {
			int c;
			cin >> c;
			edges[v].push_back(c);
		}
	}
	dfs(0);
	int q;
	cin >> q;
	for(int i = 0; i < q; i++) {
		int a, b;
		cin >> a >> b;
		cout << lca(a, b) << "\n";
	}
}