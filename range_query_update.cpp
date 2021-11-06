/*
    Segment tree to perform range updates and range queries in O(logN) time.
    Ex.
    Given an array a[N], initially all zeros, support Q operations, each being
    one of the following forms:

    (exclusive)
    Update: U l r v. Perform a[l,..,r) += v.
    Query: Q l r. Output a[l, ..., r)

    * l and r may be 0 ... N-1 (0 indexed)
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

void build(int i = 1, int l = 0, int r = N) {
    // base case: leaf node
    if (r - l == 1) {                                         // (r == l) for inclusive
        tree[i] = A[l];
        return;
    }

    // recurse into children
    int mid = (l + r) / 2;
    build(2*i, l, mid);
    build(2*i + 1, mid, r);                                  // build(2*i+1, mid+1, r) for inclusive
    
    // update current node
    tree[i] = tree[2*i] + tree[2*i + 1];
}

// if there are pending updates, update node and pass updates to children 
void propagate(int i, int l, int r) {
    if (lazy[i] != 0) {
        tree[i] += lazy[i] * (r - l);                       // (r - l + 1) for inclusive

        if (r - l != 1) {
            tree[2*i] += lazy[i];
            tree[2*i + 1] += lazy[i];
        }

        // reset pending update
        lazy[i] = 0;
    }
}


ll query(int ql, int qr, int i = 1, int l = 0, int r = N)  {
    // if there are pending updates, update node and pass updates to children 
    propagate(i, l, r);

    // return if query not in node range
    if (l > qr || r < ql) return 0;

    // return value in tree if query is within node range
    if (l >= ql && r <= qr) return tree[i];

    // otherwise recurse to children, and return
    int mid = (l + r) / 2;
    
    ll ans = 0;
    if (ql < mid)
        ans += query(ql, min(qr, mid), 2*i, l, mid);
    if (qr > mid)
        ans += query(max(ql, mid), qr, 2*i + 1, mid, r);
    return ans;

    // For inclusive:
    // return query(ql, qr, 2*i, l, mid) + query(ql, qr, 2*i + 1, mid, r);
}

void update(int ul, int ur, int v, int i = 1, int l = 0, int r = N) {
    // if there are pending updates, update node and pass updates to children 
    propagate(i, l, r);

    // return if update not in node range
    if (l > ur || r < ul) return;

    // update tree value if update in range and pass update to children
    if (l >= ul && r <= ur) {
        tree[i] += (r - l) * v;

        if (r - l != 1) {                               // (r == l) for inclusive
            lazy[2*i] += v;
            lazy[2*i + 1] += v;
        }
        
        return;
    }

    // otherwise recurse to children, and then update tree value
    int mid = (r + l) / 2;
    
    if (ul < mid)                                     
        update(ul, min(ur, mid), v, 2*i, l, mid);
    if (ur > mid)                                    
        update(max(ul, mid), ur, v, 2*i + 1, mid, r);
    
    // For inclusive:
    // update(ul, ur, v, 2*i, l, mid);
    // update(ul, ur, v, 2*i + 1, mid, r);
    tree[i] = tree[2*i] + tree[2*i + 1];
}

void printVals() {
    cout << "values: ";
    for (int i = 0; i < N; i++) cout << query(i, i+1) << ' ';    // query(i, i) for inclusive
    cout << endl;
    return;
}

int main() {
    cin >> N >> Q;
    vector<ll> res;
    build();

    for (int i = 0; i < Q; i++) {
        char ch;
        int l, r;
        cin >> ch >> l >> r;
        if (ch == 'U') {
            int v; cin >> v;
            update(l, r, v);
            printVals();                                        // optional
        } else if (ch == 'Q') {
            res.push_back(query(l, r));
        }
    }

    for (auto i : res) cout << i << '\n';
    return 0;
}
