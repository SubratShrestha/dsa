#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

bool isValid(int mid) {
    return true;
}

int main() {
    cin.tie(nullptr);
    cin.sync_with_stdio(false);

    // replace
    int res = 0;
    int low = 1;
    int high = 10;

    while (low <= high) {
        int mid = (high + low) / 2;
        if (isValid(mid)) {
            res = mid;
            high = mid - 1;
        } else low = mid + 1;
    }

    return 0;
}
