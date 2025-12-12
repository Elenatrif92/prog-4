#include <iostream>
#include <string>
#include <algorithm> 
#include <fstream>   

using namespace std;

class RadixNode {
public:
  
  string label; 
  bool is_terminal; 
  RadixNode* children[26]; 

  RadixNode(string l = "", bool terminal = false) : label(l), is_terminal(terminal) {
    for (int i = 0; i < 26; i++) {
      children[i] = nullptr;
    }
  }

    ~RadixNode() {
        for (int i = 0; i < 26; i++) {
            delete children[i];
        }
    }
};

class RadixTrie {
private:
  RadixNode* root;

  int find_common_prefix(const string& str1, const string& str2) {
    int min_len = min(str1.length(), str2.length());
    for (int i = 0; i < min_len; ++i) {
      if (str1[i] != str2[i]) {
        return i;
      }
    }
    return min_len;
  }
    
    int get_index(char c) {
        int index = c - 'a';
        if (index >= 0 && index < 26) {
            return index;
        }
        return -1;
    }

public:
  RadixTrie() { root = new RadixNode(); }
    ~RadixTrie() { delete root; }

 
  void insert(string key) {
    RadixNode* curr = root;
    
    while (!key.empty()) {
      char first_char = key[0];
            int index = get_index(first_char);
            
            if (index == -1) return; 

      if (curr->children[index] == nullptr) {
        curr->children[index] = new RadixNode(key, true);
        key = ""; 
      } else {
        RadixNode* next_node = curr->children[index];
        int common_len = find_common_prefix(key, next_node->label);

        if (common_len == next_node->label.length()) {
          key = key.substr(common_len);
          curr = next_node;
        } else {
          string shared_prefix = next_node->label.substr(0, common_len);
          string old_suffix = next_node->label.substr(common_len);
          string new_suffix = key.substr(common_len);
          RadixNode* internal_node = new RadixNode(shared_prefix);
          
          next_node->label = old_suffix;
          internal_node->children[get_index(old_suffix[0])] = next_node;
          
          RadixNode* new_leaf = new RadixNode(new_suffix, true);
          internal_node->children[get_index(new_suffix[0])] = new_leaf;
          
          curr->children[index] = internal_node;
          key = ""; 
        }
      }
    }
    
    if (key.empty()) {
            curr->is_terminal = true;
        }
  }

  bool search(string key) {
    RadixNode* curr = root;
        
    while (!key.empty()) {
      char first_char = key[0];
            int index = get_index(first_char);
            
            if (index == -1 || curr->children[index] == nullptr) {
        return false; 
      }
            
      RadixNode* next_node = curr->children[index];
      int common_len = find_common_prefix(key, next_node->label);

      if (common_len == next_node->label.length()) {
        key = key.substr(common_len);
        curr = next_node;
      } else {
        return false;
      }
    }
    
    return curr->is_terminal;
  }

    bool startsWith(string prefix) {
        RadixNode* curr = root;
        
    while (!prefix.empty()) {
      char first_char = prefix[0];
            int index = get_index(first_char);
            
            if (index == -1 || curr->children[index] == nullptr) {
        return false; 
      }
            
      RadixNode* next_node = curr->children[index];
      int common_len = find_common_prefix(prefix, next_node->label);
            if (common_len < prefix.length() && common_len < next_node->label.length()) {
                return false; 
            }

      prefix = prefix.substr(common_len);
      curr = next_node;
    }
    
    return true;
    }
};


int main()
{
  RadixTrie trie;
  string line;
    int word_count = 0;
    const string filename = "wiki-100k.txt";
  ifstream file(filename);

    if (file.is_open()) {
        while (getline(file, line)) {
            if (!line.empty()) {
                trie.insert(line);
                word_count++;
            }
        }
        file.close();    
    } 
    else {
        cerr << "ERROR: Unable to open file " << filename << ". Make sure it is in the same directory." << endl;
        return 1;
    }
    
    cout << "Search for 'the': " << (trie.search("the") ? "Found" : "Not Found") << endl; 
    cout << "Search for 'university': " << (trie.search("university") ? "Found" : "Not Found") << endl; 
    cout << "Search for 'orje': " << (trie.search("orje") ? "Found" : "Not Found") << endl;
    
    cout << "Starts with 'uni': " << (trie.startsWith("uni") ? "Found" : "Not Found") << endl;
    cout << "Starts with 'xyzw': " << (trie.startsWith("xyzw") ? "Found" : "Not Found") << endl;
    
  return 0;
}