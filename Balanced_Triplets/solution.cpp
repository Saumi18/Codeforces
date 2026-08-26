#include <bits/stdc++.h>

using namespace std;

vector<long long> get_counts(int n) {
    vector<long long> counts(4, 0);
    for (int i = 0; i < 3 * n; ++i) {
        int num;
        cin >> num;
        counts[num]++;
    }
    return counts;
}

bool can_form_triplets(long long n, const vector<long long>& counts) {
    long long c1 = counts[1];
    long long c2 = counts[2];
    long long c3 = counts[3];

    long long total_sum = c1 + c2 * 2 + c3 * 3;
    if (total_sum % n != 0) {
        return false;
    }

    long long target_sum = total_sum / n;

    switch (target_sum) {
        case 3:
            return c1 == 3 * n;
        case 4:
            return c1 == 2 * n && c2 == n;
        case 5: {
            if (c2 % 2 != 0) return false;
            long long num_122_triplets = c2 / 2;
            long long num_113_triplets = c3;
            return num_113_triplets + num_122_triplets == n && 2 * num_113_triplets + num_122_triplets == c1;
        }
        case 6: {
            if (c1 != c3) return false;
            if (c2 < c1 || (c2 - c1) % 3 != 0) return false;
            long long num_123_triplets = c1;
            long long num_222_triplets = (c2 - c1) / 3;
            return num_123_triplets + num_222_triplets == n;
        }
        case 7: {
            if (c2 % 2 != 0) return false;
            long long num_133_triplets = c1;
            long long num_223_triplets = c2 / 2;
            return num_133_triplets + num_223_triplets == n && 2 * num_133_triplets + num_223_triplets == c3;
        }
        case 8:
            return c2 == n && c3 == 2 * n;
        case 9:
            return c3 == 3 * n;
        default:
            return false;
    }
}

void solve() {
    int n;
    cin >> n;
    vector<long long> counts = get_counts(n);
    if (can_form_triplets(n, counts)) {
        cout << "Yes\n";
    } else {
        cout << "No\n";
    }
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