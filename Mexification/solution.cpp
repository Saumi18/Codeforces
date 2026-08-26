#include<bits/stdc++.h>

using namespace std;

vector<long long> transform_array(long long n, const vector<long long>& a) {
    if (n == 0) {
        return {};
    }
    vector<int> counts(n + 1, 0);
    for (long long val : a) {
        if (val <= n) {
            counts[val]++;
        }
    }
    long long current_mex = 0;
    while (current_mex <= n && counts[current_mex] > 0) {
        current_mex++;
    }

    vector<long long> next_a(n);
    for (size_t i = 0; i < n; ++i) {
        long long v = a[i];
        long long v_count = (v <= n) ? counts[v] : 1;
        if (v_count > 1) {
            next_a[i] = current_mex;
        } else {
            next_a[i] = min(v, current_mex);
        }
    }
    return next_a;
}

long long calculate_sum(const vector<long long>& a) {
    long long sum = 0;
    for(long long x : a) {
        sum += x;
    }
    return sum;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while (t--) {
        long long n, k;
        cin >> n >> k;
        vector<long long> a0(n);
        for (int i = 0; i < n; ++i) {
            cin >> a0[i];
        }

        if (k == 0) {
            cout << calculate_sum(a0) << "\n";
            continue;
        }

        vector<long long> a1 = transform_array(n, a0);
        if (k == 1) {
            cout << calculate_sum(a1) << "\n";
            continue;
        }

        vector<long long> a2 = transform_array(n, a1);
        if (k == 2) {
            cout << calculate_sum(a2) << "\n";
            continue;
        }
        
        vector<long long> a3 = transform_array(n, a2);
        
        if (a2 == a3) {
            cout << calculate_sum(a2) << "\n";
        } else {
            if ((k - 2) % 2 == 1) {
                cout << calculate_sum(a3) << "\n";
            } else {
                cout << calculate_sum(a2) << "\n";
            }
        }
    }
    return 0;
}