/*
    Perform point updates and range queries in O(logN) time.

    node = index within the tree.
    id = index within the array/data.
*/
#include<iostream>
#include<algorithm>
#include <vector>
using namespace std;
const int MAX = 100000;
int tree[266666];
int A[MAX];
vector<int> res;

void build_tree(int node, int start, int end) {
    if (start == end) {
        tree[node] = A[start];
        return;
    }

    int mid = (start + end) / 2;

    build_tree(node * 2 + 1, start, mid);
    build_tree(node * 2 + 2, mid + 1, end);

    tree[node] = min(tree[node * 2 + 1], tree[node * 2 + 2]);                   // change operation here.
                                                                                // max for max, tree[n*2+1] + tree[n*2+2] for sum
    return;
}

void update(int start, int end, int value, int id, int node = 0) {
    if (start == end) {
        tree[node] = value;
        A[id] = value;
        return;
    }

    int mid = (start + end) / 2;

    if (id <= mid) {
        update(start, mid, value, id, node * 2 + 1);
    } else update(mid + 1, end, value, id, node * 2 + 2);

    tree[node] = min(tree[node * 2 + 1], tree[node * 2 + 2]);                   // change operation here.
    return;
}

int query(int node, int start, int end, int left, int right) {
    // case where a node completely represents interval left - right.
    if (left <= start && end <= right) {
        return tree[node];
    }

    // case where a node is disjoint from query
    if (start > right || end < left) {
        return INT32_MAX;                                                       // change to value that won't affect answer.
                                                                                // INT32_MIN for max, 0 for sum
    }

    // combination of node ranges
    int mid = (start + end) / 2;
    int l = query(node * 2 + 1, start, mid, left, right);
    int r = query(node * 2 + 2, mid + 1, end, left, right);
    return min(l, r);                                                           // change operation here.
}

int main() {
    int n, q; cin >> n >> q;
    for (int i = 0; i < n; i++) cin >> A[i];
    build_tree(0, 0, n-1);
    for (int i = 0 ; i < q; i++) {
        char ch; cin >> ch;
        if (ch == 'Q') {
            int l, r; cin >> l >> r;
            res.push_back(query(0, 0, n-1, l, r));
        } else {
            int k, v; cin >> k >> v;
            update(0, n-1, v, k);
        }
    }

    for (auto i : res) {
        cout << i << '\n';
    }
    return 0;
}
