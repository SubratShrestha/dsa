/*
    Segment tree to perform range updates and range queries in O(logN) time.
    Ex.
    Given an array a[N], initially all zeros, support Q operations, each being
    one of the following forms:
    Update: U l r v. Perform a[l,..,r) += v.
    Query: Q l r. Output a[l] + ... + a[r-1].
*/

#define ll long long
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAX = 100000;
int N, Q = 0;
ll tree[4*MAX];
ll lazy[4*MAX];
ll A[MAX];

void build(int i = 1, int l = 1, int r = N) {
    // base case: leaf node
    if (l == r) {
        tree[i] = A[l];
        return;
    }

    // recurse into children
    int mid = (l + r) / 2;
    build(2*i, l, mid);
    build(2*i + 1, mid+1, r);
    
    // update current node
    tree[i] = tree[2*i] + tree[2*i + 1];
    return;
}

// if there are pending updates, update node and pass updates to children 
void propagate(int i, int l, int r) {
    if (lazy[i] != 0) {
        tree[i] += lazy[i] * (r - l + 1);

        if (l != r) {
            tree[2*i] += lazy[i];
            tree[2*i + 1] += lazy[i];
        }

        // reset pending update
        lazy[i] = 0;
    }
}


ll query(int ql, int qr, int i = 1, int l = 1, int r = N)  {
    // if there are pending updates, update node and pass updates to children 
    propagate(i, l, r);

    // return if query not in node range
    if (l > qr || r < ql) return 0;

    // return value in tree if query is within node range
    if (l >= ql && r <= qr) return tree[i];

    // otherwise recurse to children, and return
    int mid = (l + r) / 2;
    return query(ql, qr, 2*i, l, mid) + query(ql, qr, 2*i + 1, mid+1, r);
}

void update(int ul, int ur, int v, int i = 1, int l = 1, int r = N) {
    // if there are pending updates, update node and pass updates to children 
    propagate(i, l, r);

    // return if update not in node range
    if (l > ur || r < ul) return;

    // update tree value if update in range and pass update to children
    if (l >= ul && r <= ur) {
        tree[i] += (r - l + 1) * v;

        if (l != r) {
            lazy[2*i] += v;
            lazy[2*i + 1] += v;
        }
        
        return;
    }

    // otherwise recurse to children, and then update tree value
    int mid = (r + l ) / 2;
    update(ul, ur, v, 2*i, l, mid);
    update(ul, ur, v, 2*i + 1, mid+1, r);
}

int main() {
    cin >> N >> Q;
    vector<ll> res;
    build();

    for (int i = 0; i < Q; i++) {
        char ch; cin >> ch;
        if (ch == 'U') {
            int l, r, v; cin >> l >> r >> v;
            update(l, r, v);
        } else if (ch == 'Q') {
            int l, r; cin >> l >> r;
            res.push_back(query(l, r));
        }
    }

    for (auto i : res) cout << i << '\n';
    return 0;
}
