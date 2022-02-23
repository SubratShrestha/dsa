/*
    Segment tree to perform range updates and range queries in O(logN) time.
    Ex.
    Given an array a[N], initially all zeros, support Q operations, each being
    one of the following:

    Update: U l r v. Perform a[l,..,r] += v.
    Query: Q l r. Sum of a[l] + ... + a[r].

    * l and r may be 0 ... N (1 indexed)
*/

#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAX = 100001;
int A[MAX];
int tree[4 * MAX];
int lazy[4 * MAX];

int N, Q;

void build(int i = 1, int l = 1, int r = N) {
    if (l == r) {
        tree[i] = A[l];
        return;
    }

    int mid = (l + r) / 2;
    build(2*i, l, mid);
    build(2*i + 1, mid + 1, r);
    tree[i] = tree[2*i] + tree[2*i + 1];
}

ll query(int ql, int qr, int i = 1, int l = 1, int r = N) {
    if (lazy[i] != 0) {
        tree[i] += lazy[i] * (r - l + 1);  // update range

        if (l != r) {
            lazy[2*i] += lazy[i];
            lazy[2*i + 1] += lazy[i];
        }
        
        lazy[i] = 0;
    }

    if (l > qr || r < ql) return 0;   // current range outside queried range.

    if (l >= ql && r <= qr) return tree[i];  // current range inside queried range.

    ll mid = (l + r) / 2;
    return query(ql, qr, 2*i, l, mid) + query(ql, qr, 2*i + 1, mid + 1, r);
}

void update(int ql, int qr, ll v, int i = 1, int l = 1, int r = N) {
    if (lazy[i] != 0) {
        tree[i] += lazy[i] * (r - l + 1);  // update range

        if (l != r) {
            lazy[2*i] += lazy[i];
            lazy[2*i + 1] += lazy[i];
        } 
        
        lazy[i] = 0;
    }
    
    if (l > qr || r < ql) return;

    if (l >= ql && r <= qr) {
        tree[i] += (r - l + 1) * v;

        if (l != r) {
            lazy[2*i] += v;
            lazy[2*i + 1] += v;
        }

        return;
    }

    int mid = (l + r) / 2;
    update(ql, qr, v, 2*i, l, mid);
    update(ql, qr, v, 2*i + 1, mid + 1, r);

    tree[i] = tree[2*i] + tree[2*i + 1];
}

void print_vals() {
    for (int i = 1; i <= N; i++) {
        cout << query(i, i) << ' ';
    }
    cout << '\n';
}

void update_array() {
    for (int i = 1; i <= N; i++) {
        A[i - 1] = query(i, i);
    }
}

int main() {
    cin.tie(nullptr);
    cin.sync_with_stdio(false);

    cin >> N >> Q;
    // initialize Array here.
    for (int i = 1; i <= N; i++) A[i] = i;

    build();

    while (Q--) {
        char c; int l, r;
        cin >> c >> l >> r;
        if (c == 'Q') {
            cout << "sum = " << query(l, r) << '\n';
        } else {
            int v; cin >> v;
            update(l, r, v);
            update_array();
            for (int i = 0; i < N; i++) cout << A[i] << ' ';
            cout << '\n';
        }
    }
    return 0;
}
