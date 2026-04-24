#include <bits/stdc++.h>
using namespace std;

// Problem 2056 - Falling Balls
// Computes the final position of the last ball in a depth-D perfect binary tree
// and the final states (open=1, closed=0) of all leaf switches from left to right.

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long D, n;
    if (!(cin >> D >> n)) return 0;

    // 1) Last ball position using known iterative rule
    //    Start at index 1; for D-1 levels, if n is odd go left and n=(n+1)/2, else go right and n/=2.
    long long last_pos = 1;
    long long m = n;
    for (long long level = 1; level <= D - 1; ++level) {
        if (m % 2 == 1) {
            last_pos = last_pos * 2;      // go left
            m = (m + 1) / 2;
        } else {
            last_pos = last_pos * 2 + 1;  // go right
            m /= 2;
        }
    }

    // 2) Leaf states after all n balls: distribute counts down the tree
    // For a node with m balls: left gets ceil(m/2) = (m+1)/2, right gets floor(m/2) = m/2.
    // Leaf's final state is (number of visits) % 2, since each visit toggles the (initially closed) switch.
    int depth = static_cast<int>(D);
    int total_nodes_at_depth = 1 << depth; // indices [1, 2^D - 1] exist; leaves are [2^{D-1}, 2^D - 1]
    vector<long long> cnt(total_nodes_at_depth, 0);
    cnt[1] = n;
    for (int i = 1; i < (1 << (depth - 1)); ++i) { // internal nodes only
        long long c = cnt[i];
        cnt[i * 2]     = (c + 1) / 2; // left
        cnt[i * 2 + 1] = c / 2;       // right
    }

    // Output
    cout << last_pos << '\n';
    int L = 1 << (depth - 1);
    for (int i = L; i < (1 << depth); ++i) {
        cout << (cnt[i] % 2);
        if (i + 1 < (1 << depth)) cout << ' ';
    }
    cout << '\n';
    return 0;
}

