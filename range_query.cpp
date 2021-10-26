/*
Range queries of min.
Segment tree to have a preprocessing time of O(N),
query time of O(logN)
update time of O(logN)

node = index within the tree.
id = index within the array/data.
*/
#include<iostream>
#include<algorithm>
using namespace std;
const int MAX = 100000;
int tree[266666];
int A[MAX];
int res[MAX];

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

void update(int node, int id, int start, int end, int value) {
    if (start == end) {
        tree[node] = value;
        A[id] = value;
        return;
    }

    int mid = (start + end) / 2;

    if (id <= mid) {
        update(node * 2 + 1, id, start, mid, value);
    } else update(node * 2 + 2, id, mid + 1, end, value);

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
        int l, r; cin >> l >> r;
        res[i] = query(0, 0, n-1, l, r);
    }

    for (int i = 0; i < q; i++) {
        cout << res[i] << '\n';
    }
    
    return 0;
}