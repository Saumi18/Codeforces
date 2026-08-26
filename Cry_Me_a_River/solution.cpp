#include<bits/stdc++.h>
using namespace std;

vector<int> get_topological_order(int n, const vector<vector<int>>& adj, vector<int>& in_degree) {
    vector<int> topo_order;
    topo_order.reserve(n);
    queue<int> q;
    for (int i = 1; i <= n; ++i) {
        if (in_degree[i] == 0) {
            q.push(i);
        }
    }
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        topo_order.push_back(u);
        for (int v : adj[u]) {
            in_degree[v]--;
            if (in_degree[v] == 0) {
                q.push(v);
            }
        }
    }
    return topo_order;
}

void initialize_dp_states(
    int n,
    const vector<int>& topo_order,
    const vector<vector<int>>& adj,
    const vector<int>& out_degree,
    vector<bool>& cry_win_1,
    vector<bool>& cry_win_2,
    vector<int>& count_cw1_false,
    vector<int>& count_cw2_true
) {
    for (int i = n - 1; i >= 0; --i) {
        int u = topo_order[i];
        if (out_degree[u] == 0) {
            cry_win_1[u] = true;
            cry_win_2[u] = true;
        } else {
            for (int v : adj[u]) {
                if (!cry_win_1[v]) {
                    count_cw1_false[u]++;
                }
                if (cry_win_2[v]) {
                    count_cw2_true[u]++;
                }
            }
            cry_win_1[u] = (count_cw2_true[u] > 0);
            cry_win_2[u] = (count_cw1_false[u] == 0);
        }
    }
}

void perform_update_and_propagate(
    int u,
    vector<bool>& is_red,
    vector<bool>& cry_win_1,
    vector<bool>& cry_win_2,
    const vector<vector<int>>& rev_adj,
    vector<int>& count_cw1_false,
    vector<int>& count_cw2_true
) {
    if (is_red[u]) {
        return;
    }
    is_red[u] = true;

    bool old_cw1 = cry_win_1[u];
    bool old_cw2 = cry_win_2[u];
    cry_win_1[u] = false;
    cry_win_2[u] = false;

    queue<pair<int, int>> Q;
    vector<bool> in_queue1(is_red.size(), false);
    vector<bool> in_queue2(is_red.size(), false);

    if (old_cw1) {
        Q.push({u, 1});
        in_queue1[u] = true;
    }
    if (old_cw2) {
        Q.push({u, 2});
        in_queue2[u] = true;
    }

    while (!Q.empty()) {
        auto [c, flip_type] = Q.front();
        Q.pop();

        for (int p : rev_adj[c]) {
            if (is_red[p]) {
                continue;
            }

            if (flip_type == 1) {
                bool p_was_win = cry_win_2[p];
                count_cw1_false[p]++;
                if (p_was_win) {
                    cry_win_2[p] = false;
                    if (!in_queue2[p]) {
                        Q.push({p, 2});
                        in_queue2[p] = true;
                    }
                }
            } else {
                bool p_was_win = cry_win_1[p];
                count_cw2_true[p]--;
                if (count_cw2_true[p] == 0) {
                    if (p_was_win) {
                        cry_win_1[p] = false;
                        if (!in_queue1[p]) {
                            Q.push({p, 1});
                            in_queue1[p] = true;
                        }
                    }
                }
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while(t--) {
        int n, m, q;
        cin >> n >> m >> q;

        vector<vector<int>> adj(n + 1);
        vector<vector<int>> rev_adj(n + 1);
        vector<int> out_degree(n + 1, 0);
        vector<int> in_degree_for_topo(n + 1, 0);

        for (int i = 0; i < m; ++i) {
            int u, v;
            cin >> u >> v;
            adj[u].push_back(v);
            rev_adj[v].push_back(u);
            out_degree[u]++;
            in_degree_for_topo[v]++;
        }

        vector<int> topo_order = get_topological_order(n, adj, in_degree_for_topo);

        vector<bool> is_red(n + 1, false);
        vector<bool> cry_win_1(n + 1);
        vector<bool> cry_win_2(n + 1);
        vector<int> count_cw1_false(n + 1, 0);
        vector<int> count_cw2_true(n + 1, 0);

        initialize_dp_states(n, topo_order, adj, out_degree, cry_win_1, cry_win_2, count_cw1_false, count_cw2_true);

        for (int k = 0; k < q; ++k) {
            int type, u;
            cin >> type >> u;
            if (type == 2) {
                if (cry_win_1[u]) {
                    cout << "YES\n";
                } else {
                    cout << "NO\n";
                }
            } else {
                perform_update_and_propagate(u, is_red, cry_win_1, cry_win_2, rev_adj, count_cw1_false, count_cw2_true);
            }
        }
    }
    return 0;
}