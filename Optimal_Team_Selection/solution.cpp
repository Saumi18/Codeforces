#include <bits/stdc++.h>

using namespace std;

struct Candidate {
    int proficiency;
    int salary;
};

bool compareCandidates(const Candidate& a, const Candidate& b) {
    return a.proficiency < b.proficiency;
}

void find_optimal_team_cost(int n, int k, vector<Candidate>& candidates) {
    sort(candidates.begin(), candidates.end(), compareCandidates);

    if (k == 0) {
        cout << 0 << "\n";
        return;
    }

    long long min_cost = -1;
    long long sum_k_minus_1_salaries = 0;
    priority_queue<int> pq;

    for (int i = 0; i < k - 1; ++i) {
        pq.push(candidates[i].salary);
        sum_k_minus_1_salaries += candidates[i].salary;
    }

    for (int i = k - 1; i < n; ++i) {
        long long current_total_salary = sum_k_minus_1_salaries + candidates[i].salary;
        long long current_cost = (long long)candidates[i].proficiency * current_total_salary;
        
        if (min_cost == -1 || current_cost < min_cost) {
            min_cost = current_cost;
        }

        if (k > 1) {
            if (candidates[i].salary < pq.top()) {
                sum_k_minus_1_salaries -= pq.top();
                pq.pop();
                sum_k_minus_1_salaries += candidates[i].salary;
                pq.push(candidates[i].salary);
            }
        }
    }
    cout << min_cost << "\n";
}

void solve() {
    int n, k;
    cin >> n >> k;
    vector<Candidate> candidates(n);
    for (int i = 0; i < n; ++i) cin >> candidates[i].proficiency;
    for (int i = 0; i < n; ++i) cin >> candidates[i].salary;
    
    find_optimal_team_cost(n, k, candidates);
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