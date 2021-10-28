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
const int MAX = 100005;
ll lazyadd[266666];
ll sum[266666];

void update_sum(int id, ll l, ll r) {
    sum[id] = (r - l) * lazyadd[id];

    // if not a leaf, increment by children's sum
    if (r - l > 1) {
        sum[id] += sum[id * 2];
        sum[id] += sum[id * 2 + 1];
    }
}

void propagate(int id, ll l, ll r) {
    ll mid = (l + r) / 2;

    // increment children's lazy counter
    lazyadd[id * 2] += lazyadd[id];
    lazyadd[id * 2 + 1] += lazyadd[id];

    // update children's sum
    update_sum(id * 2, l, mid);
    update_sum(id * 2 + 1, mid, r);
    
    // reset current node's lazy counter
    lazyadd[id] = 0;
}


void update(int uL, int uR, int v, int i = 1, int cLeft = 0, int cRight = MAX) {
    // if the current range is exactly the same as the update range.
    if (uL == cLeft && uR == cRight) {
        lazyadd[i] += v;
        update_sum(i, cLeft, cRight);
        return;
    }
    propagate(i, cLeft, cRight);
    int mid = (cLeft + cRight) / 2;
    
    if (uL < mid) 
        update(uL, min(uR, mid), v, i * 2, cLeft, mid);
    
    if (uR > mid) 
        update(max(uL, mid), uR, v, i * 2 + 1, mid, cRight);
    
    update_sum(i, cLeft, cRight);
}

ll query(int qL, int qR, int i = 1, int cLeft = 0, int cRight = MAX) {
    if (qL == cLeft && qR == cRight) {
        return sum[i];
    }

    propagate(i, cLeft, cRight);
    
    int mid = (cLeft + cRight) / 2;
    ll ans = 0;
    if (qL < mid)
        ans += query(qL, min(qR, mid), i * 2, cLeft, mid);
    if (qR > mid)
        ans += query(max(qL, mid), qR, i * 2 + 1, mid, cRight);
    
    return ans;
}

int main() {
    vector<ll> res;
    int n, q; cin >> n >> q;
    for (int i = 0; i < q; i++) {
        char ch; cin >> ch;
        if (ch == 'U') {
            int l, r, v; cin >> l >> r >> v;
            update(l, r, v);
        } else {
            int l, r; cin >> l >> r;
            res.push_back(query(l, r));
        }
    }
    for (auto i : res) cout << i << '\n';
    return 0;
}
