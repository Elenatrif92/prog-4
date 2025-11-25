#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <string_view>

using namespace std;

class Solution {
    typedef unsigned long long ull;
    const int P = 131; 
    
public:
    string longestDupSubstring(string s) {
        int n = s.length();
        int left = 1, right = n - 1;
        string_view best_view = ""; 
        
        while (left <= right) {
            int mid = left + (right - left) / 2;
            
            // Check if duplicate of length 'mid' exists
            string_view duplicate = check(s, mid);
            
            if (!duplicate.empty()) {
                // If found, save it and try to find a longer one
                best_view = duplicate;
                left = mid + 1;
            } else {
                // If not found, looking for something smaller
                right = mid - 1;
            }
        }
        
        return string(best_view);
    }
    
    // Returns the duplicate substring if found, otherwise returns empty string_view
    string_view check(const string& s, int len) {
        int n = s.length();
        if (len == 0) return "";
        
        ull current_hash = 0;
        ull power = 1;
        
        // 1. Compute hash of the first 'len' characters (Initial Window)
        for (int i = 0; i < len; i++) {
            current_hash = current_hash * P + s[i];
            if (i < len - 1) power = power * P; // We need P^(len-1) for rolling
        }
        
        // Map: Hash -> List of starting indices that have this hash
        // We use a vector of ints because multiple different strings might collide to same hash
        unordered_map<ull, vector<int>> seen;
        seen[current_hash].push_back(0);
        
        // 2. Slide the window
        for (int i = 1; i <= n - len; i++) {
            // Remove leading char (s[i-1]) and add new trailing char (s[i+len-1])
            // Formula: hash = (hash - s[start] * P^(len-1)) * P + s[end]
            current_hash = current_hash - s[i - 1] * power;
            current_hash = current_hash * P + s[i + len - 1];
            
            // If this hash exists in our map, we might have a duplicate
            if (seen.count(current_hash)) {
                // COLLISION CHECK: Compare actual substrings to be sure
                string_view curr_sub(s.c_str() + i, len);
                for (int start_index : seen[current_hash]) {
                    string_view prev_sub(s.c_str() + start_index, len);
                    if (curr_sub == prev_sub) {
                        return curr_sub; // Found valid duplicate
                    }
                }
            }
            
            // Add this new index to our map
            seen[current_hash].push_back(i);
        }
        
        return "";
    }
};