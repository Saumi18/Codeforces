#include<bits/stdc++.h>

using namespace std;

vector<vector<int>> group_indices(int n, const vector<int>& b) {
    vector<vector<int>> groups(n + 1);
    for (int i = 0; i < n; ++i) {
        groups[b[i]].push_back(i);
    }
    return groups;
}

bool is_solvable(int n, const vector<vector<int>>& groups) {
    for (int c = 1; c <= n; ++c) {
        if (!groups[c].empty() && groups[c].size() % c != 0) {
            return false;
        }
    }
    return true;
}

vector<int> construct_array(int n, const vector<vector<int>>& groups) {
    vector<int> a(n);
    int val_counter = 1;
    for (int c = 1; c <= n; ++c) {
        if (groups[c].empty()) {
            continue;
        }
        
        int num_blocks = groups[c].size() / c;
        for (int block = 0; block < num_blocks; ++block) {
            int current_val = val_counter++;
            for (int item = 0; item < c; ++item) {
                int original_idx = groups[c][block * c + item];
                a[original_idx] = current_val;
            }
        }
    }
    return a;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> b(n);
        for (int i = 0; i < n; ++i) {
            cin >> b[i];
        }

        vector<vector<int>> groups = group_indices(n, b);

        if (!is_solvable(n, groups)) {
            cout << -1 << "\n";
        } else {
            vector<int> a = construct_array(n, groups);
            for (size_t i = 0; i < a.size(); ++i) {
                cout << a[i] << (i == a.size() - 1 ? "" : " ");
            }
            cout << "\n";
        }
    }

    return 0;
}