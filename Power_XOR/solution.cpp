#include <bits/stdc++.h>
using namespace std;

long long perform_operation(long long val, int index) {
    long long xor_val = 1LL << (index % 25);
    if (val >= 0) {
        return val ^ xor_val;
    } else {
        return -((-val) ^ xor_val);
    }
}

long long find_max_subarray_sum(const vector<long long>& arr) {
    long long max_so_far = 0;
    long long current_max = 0;
    for (long long x : arr) {
        current_max += x;
        if (current_max > max_so_far) {
            max_so_far = current_max;
        }
        if (current_max < 0) {
            current_max = 0;
        }
    }
    return max_so_far;
}

void solve() {
    int n;
    cin >> n;
    vector<long long> processed_arr(n);
    for (int i = 0; i < n; ++i) {
        long long val;
        cin >> val;
        long long operated_val = perform_operation(val, i);
        processed_arr[i] = max(val, operated_val);
    }
    cout << find_max_subarray_sum(processed_arr) << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}