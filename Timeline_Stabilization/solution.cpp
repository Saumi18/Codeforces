#include <bits/stdc++.h>
using namespace std;

const int INF = 2e9 + 7;

template <typename T>
struct FenwickTree {
    int n;
    vector<T> tree;

    FenwickTree(int size) : n(size), tree(size + 1, 0) {}

    void update(int idx, T val) {
        idx++;
        while (idx <= n) {
            tree[idx] = max(tree[idx], val);
            idx += idx & -idx;
        }
    }

    T query(int idx) {
        if (idx < 0) return 0;
        idx++;
        T res = 0;
        while (idx > 0) {
            res = max(res, tree[idx]);
            idx -= idx & -idx;
        }
        return res;
    }
};

void calculate_lis_lengths(int n, const vector<int>& a, vector<int>& lis, const map<long long, int>& val_map) {
    int map_size = val_map.size();
    FenwickTree<int> ft(map_size);
    for (int i = 0; i < n; ++i) {
        int val_idx = val_map.at(a[i]);
        int prev_max = ft.query(val_idx - 1);
        lis[i] = prev_max + 1;
        ft.update(val_idx, lis[i]);
    }
}


void solve() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    vector<int> a(n);
    map<long long, int> val_map;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        val_map[a[i]] = 0;
        val_map[(long long)a[i] - 2] = 0;
    }

    int rank = 0;
    for (auto& pair : val_map) {
        pair.second = rank++;
    }

    vector<int> lis_forward(n);
    calculate_lis_lengths(n, a, lis_forward, val_map);

    vector<int> a_rev = a;
    reverse(a_rev.begin(), a_rev.end());
    vector<int> neg_a_rev(n);
    map<long long, int> neg_val_map;

    for (int i = 0; i < n; ++i) {
        neg_a_rev[i] = INF - a_rev[i];
        neg_val_map[neg_a_rev[i]] = 0;
    }
    
    rank = 0;
    for (auto& pair : neg_val_map) {
        pair.second = rank++;
    }

    vector<int> lis_backward_rev(n);
    calculate_lis_lengths(n, neg_a_rev, lis_backward_rev, neg_val_map);
    vector<int> lis_backward(n);
    for(int i = 0; i < n; ++i) {
        lis_backward[i] = lis_backward_rev[n - 1 - i];
    }

    int max_lis = 0;
    for (int len : lis_forward) {
        max_lis = max(max_lis, len);
    }

    FenwickTree<int> ft(val_map.size());
    if (n > 1) {
       ft.update(val_map[a[0]], lis_forward[0]);
    }

    for (int k = 2; k < n; ++k) {
        long long target_val = (long long)a[k] - 2;
        if (val_map.count(target_val)) {
            int target_idx = val_map.at(target_val);
            int max_prefix_lis = ft.query(target_idx);
            if (max_prefix_lis > 0) {
                max_lis = max(max_lis, max_prefix_lis + 1 + lis_backward[k]);
            }
        }
        ft.update(val_map[a[k - 1]], lis_forward[k - 1]);
    }

    cout << max_lis << "\n";
}

int main() {
    solve();
    return 0;
}
