#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

//(modulo 2^64)
typedef unsigned long long ull;

const int MAXN = 5005;
ull h[MAXN], rh[MAXN], P[MAXN]; // Hash, Reverse Hash, Powers
int dp[MAXN][MAXN];             // dp[i][len] stores degree
int ans[MAXN];                  // Final counts

// Helper to get substring hash in O(1)
// l and r are 1-based indices
ull get_hash(ull* hash_arr, int l, int r) {
    return hash_arr[r] - hash_arr[l - 1] * P[r - l + 1];
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);

    string s;
    cin >> s;
    int n = s.size();

    // 1. Precompute Powers and Hashes
    P[0] = 1;
    for (int i = 0; i < n; i++) {
        P[i + 1] = P[i] * 131; // 131 is a good prime base
        h[i + 1]  = h[i] * 131 + s[i]; // Forward hash
    }

    // Reverse hash logic: computed from the back of the string
    // But to keep it simple, let's just reverse the string and hash that.
    string rs = s;
    reverse(rs.begin(), rs.end());
    for (int i = 0; i < n; i++) {
        rh[i + 1] = rh[i] * 131 + rs[i];
    }

    // 2. Main Logic Loop
    for (int len = 1; len <= n; len++) {
        for (int i = 1; i <= n - len + 1; i++) {
            int j = i + len - 1; // End index (1-based)

            // Check if palindrome: Forward Hash == Reverse Hash
            // The reverse hash segment corresponding to s[i..j] is in rs[n-j+1 ... n-i+1]
            if (get_hash(h, i, j) == get_hash(rh, n - j + 1, n - i + 1)) {
                
                // If len=1, it's degree 1. 
                // If len>1, look at the pre-calculated degree of the HALF length
                // The left half starts at i and has length len/2.
                dp[i][len] = dp[i][len / 2] + 1;
                
                ans[dp[i][len]]++; 
            }
        }
    }
    //3palindromi sa i 2-palindr i 1 palindr, soberi...
    for (int i = n; i >= 1; i--) {
        ans[i] += ans[i + 1];
    }

    for (int i = 1; i <= n; i++) cout << ans[i] << " ";
    
    return 0;
}