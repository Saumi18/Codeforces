#include<bits/stdc++.h>
using namespace std;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    while (t--) {
        long long k, x;
        cin >> k >> x;

        while (k-- > 0) {
            if (x % 2 != 0) {
                x = x * 2;
            } 
            else {
                if (x > 1 && (x - 1) % 3 == 0) {
                    x = (x - 1) / 3;
                } else {
                    x = x * 2;
                }
            }
        }
        cout << x << "\n";
    }
    return 0;
}