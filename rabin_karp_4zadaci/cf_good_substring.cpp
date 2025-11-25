#include <bits/stdc++.h>
using namespace std;

int main() {
    string s;
    cin >> s;
    int n = s.size();

    string goodStr;
    cin >> goodStr;

    vector<int> good(26);
    for (int i = 0; i < 26; i++)
        good[i] = goodStr[i] - '0';

    int k;
    cin >> k;

    const long long p1 = 31, p2 = 53;
    const long long m1 = 1000000007, m2 = 1000000009;

    vector<long long> pow1(n+1), pow2(n+1);
    pow1[0] = pow2[0] = 1;

    for (int i = 1; i <= n; i++) {
        pow1[i] = (pow1[i-1] * p1) % m1;
        pow2[i] = (pow2[i-1] * p2) % m2;
    }

    unordered_set<uint64_t> hashes;  

    for (int i = 0; i < n; i++) {
        long long h1 = 0, h2 = 0;
        int bad = 0;

        for (int j = i; j < n; j++) {
            if (!good[s[j] - 'a']) bad++;
            if (bad > k) break;

            h1 = (h1 + (s[j] - 'a' + 1) * pow1[j - i]) % m1;
            h2 = (h2 + (s[j] - 'a' + 1) * pow2[j - i]) % m2;

            uint64_t h64 = (uint64_t(h1) << 32) ^ uint64_t(h2);
            hashes.insert(h64);
        }
    }

    cout << hashes.size() << endl;
    return 0;
}
