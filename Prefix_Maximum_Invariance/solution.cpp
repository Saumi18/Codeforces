#include<bits/stdc++.h>

using namespace std;

struct SegTree {
    int size;
    vector<int> tree;

    void init(int n) {
        size = 1;
        while (size < n) {
            size *= 2;
        }
        tree.assign(2 * size, -1);
    }

    void update(int i, int v, int x, int lx, int rx) {
        if (rx - lx == 1) {
            tree[x] = max(tree[x], v);
            return;
        }
        int m = (lx + rx) / 2;
        if (i < m) {
            update(i, v, 2 * x + 1, lx, m);
        } else {
            update(i, v, 2 * x + 2, m, rx);
        }
        tree[x] = max(tree[2 * x + 1], tree[2 * x + 2]);
    }

    void update(int i, int v) {
        update(i, v, 0, 0, size);
    }

    int query(int l, int r, int x, int lx, int rx) {
        if (lx >= r || l >= rx) {
            return -1;
        }
        if (lx >= l && rx <= r) {
            return tree[x];
        }
        int m = (lx + rx) / 2;
        int s1 = query(l, r, 2 * x + 1, lx, m);
        int s2 = query(l, r, 2 * x + 2, m, rx);
        return max(s1, s2);
    }
    
    int query(int l, int r) {
        if (l >= r) {
            return -1;
        }
        return query(l, r, 0, 0, size);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> a(n), b(n);
        int max_val = 0;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            max_val = max(max_val, a[i]);
        }
        for (int i = 0; i < n; i++) {
            cin >> b[i];
            max_val = max(max_val, b[i]);
        }

        SegTree st;
        st.init(max_val + 2);

        long long total_sum = 0;

        for (int i = 0; i < n; i++) {
            int v_a = a[i];
            int v_b = b[i];
            int V = max(v_a, v_b);

            int p = st.query(v_a, max_val + 2);
            int p_prime = st.query(V, max_val + 2);

            long long count1 = (long long)i - p;
            long long count2 = (long long)p_prime + 1;
            
            long long C_i = count2;
            if (v_a == v_b) {
                C_i += count1;
            }

            total_sum += (long long)(n - i) * C_i;

            st.update(v_a, i);
        }
        cout << total_sum << "\n";
    }

    return 0;
}