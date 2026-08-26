#include <bits/stdc++.h>
using namespace std;

bool is_prime(int n) {
    if (n <= 1) {
        return false;
    }
    for (int i = 2; i * i <= n; ++i) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}

void find_and_print_potent_runes(const std::string& s) {
    vector<int> freq(26, 0);
    for (char c : s) {
        freq[c - 'a']++;
    }

    bool first_rune = true;
    for (int i = 0; i < 26; ++i) {
        if (is_prime(freq[i])) {
            if (!first_rune) {
                std::cout << " ";
            }
            std::cout << static_cast<char>('a' + i);
            first_rune = false;
        }
    }
    cout << "\n";
}

void solve() {
    int n;
    cin >> n;
    string s;
    cin >> s;
    find_and_print_potent_runes(s);
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