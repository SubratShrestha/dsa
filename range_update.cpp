/*
    Segment tree/range tree that handles range updates and point queries in
    O(logn) time.
    ex. given array a[N] with 0s, support Q operations of form:
    Update U l r v. Perform A[l, ..., r) += v
    Query Q x. Output A[x]
*/

#include<iostream>
#include<algorithm>
#include <vector>

using namespace std;
const int MAX = 100000;
int tree[266666];
int A[MAX];
long long lazyadd[266666];

void build_tree(int node, int start, int end) {
    if (start == end) {
        tree[node] = A[start];
        return;
    }

    int mid = (start + end) / 2;

    build_tree(node * 2 + 1, start, mid);
    build_tree(node * 2 + 2, mid + 1, end);

    tree[node] = tree[node * 2 + 1] + tree[node * 2 + 2];                   // change operation here.
                                                                                // max for max, tree[n*2+1] + tree[n*2+2] for sum
    return;
}

void update(int uL, int uR, int v, int i = 1, int cLeft = 0, int cRight = MAX) {
    // if the current range is exactly the same as the update range.
    if (uL == cLeft && uR == cRight) {
        lazyadd[i] += v;
        return;
    }
    int mid = (cLeft + cRight) / 2;
    
    if (uL < mid) 
        update(uL, min(uR, mid), v, i * 2, cLeft, mid);
    
    if (uR > mid) 
        update(max(uL, mid), uR, v, i * 2 + 1, mid, cRight);
}

long long query(int p, int i = 1, int cLeft = 0, int cRight = MAX) {
    // single node => [i, i+1), difference = 1.
    if (cRight - cLeft == 1) {
        return lazyadd[i];
    }

    int mid = (cLeft + cRight) / 2;
    
    long long ans = lazyadd[i];
    if (p < mid)
        ans += query(p, i * 2, cLeft, mid);
    else ans += query(p, i * 2 + 1, mid, cRight);
    
    return ans;
}

int main() {
    vector<long long> res;
    int n, q; cin >> n >> q;
    for (int i = 0; i < n; i++) cin >> A[i];
    build_tree(0, 0, n-1);
    for (int i = 0 ; i < q; i++) {
       char ch; cin >> ch;
       if (ch == 'U') {
            int l, r, v; cin >> l >> r >> v;
            update(l, r, v);
       } else {
           int q; cin >> q;
           res.push_back(query(q));
       }
    }

    for (auto i : res) {
        cout << i << '\n';
    }
    
    return 0;
}
