#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 10000001;
vector<bool> is_prime(MAX_N, true);
vector<long long> prime_sum_prefix(MAX_N, 0);

void sieve_and_prefix_sum() {
    is_prime[0] = is_prime[1] = false;
    for (int p = 2; p * p < MAX_N; ++p) {
        if (is_prime[p]) {
            for (int i = p * p; i < MAX_N; i += p)
                is_prime[i] = false;
        }
    }

    prime_sum_prefix[0] = 0;
    for (int i = 1; i < MAX_N; ++i) {
        prime_sum_prefix[i] = prime_sum_prefix[i - 1];
        if (is_prime[i]) {
            prime_sum_prefix[i] += i;
        }
    }
}

void solve() {
    int l, r;
    cin >> l >> r;
    long long result = prime_sum_prefix[r] - prime_sum_prefix[l - 1];
    cout << result << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    sieve_and_prefix_sum();
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}