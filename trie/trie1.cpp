#include <iostream>
#include <string>
#include <fstream> 

using namespace std;

class TrieNode {
public:
  bool endofWord;
  TrieNode* children[26];

  TrieNode()
  {
    endofWord = false;
    for (int i = 0; i < 26; i++) {
      children[i] = nullptr;
    }
  }
    ~TrieNode() {
        for (int i = 0; i < 26; i++) {
            delete children[i];
        }
    }
};


class Trie {
private:
  TrieNode* root;

public:
  Trie() { root = new TrieNode(); }
    
    ~Trie() {
        delete root;
    }

  void insert(string word)
  {
    TrieNode* node = root;
    for (char c : word) {
      int index = c - 'a';
      if (index < 0 || index >= 26) {
        continue;
      }
            
      if (!node->children[index]) {
        node->children[index] = new TrieNode();
      }
      node = node->children[index];
    }
    node->endofWord = true;
  }

  bool search(string word)
  {
    TrieNode* node = root;
    for (char c : word) {
      int index = c - 'a';
            if (index < 0 || index >= 26) return false;
            
      if (!node->children[index]) {
        return false;
      }
      node = node->children[index];
    }
    return node->endofWord;
  }

  bool startsWith(string prefix)
  {
    TrieNode* node = root;
    for (char c : prefix) {
      int index = c - 'a';
            if (index < 0 || index >= 26) return false;

      if (!node->children[index]) {
        return false;
      }
      node = node->children[index];
    }
    return true;
  }
  
  void deleteWord(string word)
  {
    TrieNode* node = root;
    for (char c : word) {
      int index = c - 'a';
            if (index < 0 || index >= 26) return;
            
      if (!node->children[index]) {
        return; // Word not found
      }
      node = node->children[index];
    }
    if (node && node->endofWord) {
      node->endofWord = false;
    }
  }

  void print(TrieNode* node, string prefix) const
  {
    if (node->endofWord) {
      cout << prefix << endl;
    }
    for (int i = 0; i < 26; i++) {
      if (node->children[i]) {
        print(node->children[i],
           prefix + char('a' + i));
      }
    }
  }

  void print() const { print(root, ""); }
};


int main()
{
  
    Trie trie;
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
        //cout << "Successfully inserted " << word_count << " words into the Trie." << endl;
    } 
    else {
        cerr << "ERROR: Unable to open file " << filename << ". Make sure it is in the same directory." << endl;
        return 1;
    }

    cout << "Search for 'the': " << (trie.search("the") ? "Found" : "Not Found") << endl; 
    cout << "Search for 'asdfghjkl': " << (trie.search("asdfghjkl") ? "Found" : "Not Found") << endl;
    cout << "Starts with 'dog': " << (trie.startsWith("dog") ? "Found" : "Not Found") << endl; 
    cout << "Starts with 'xyz': " << (trie.startsWith("xyz") ? "Found" : "Not Found") << endl;

    return 0;
}