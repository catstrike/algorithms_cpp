#include <iostream>
#include <unordered_map>

using namespace std;

class TrieNode {
public:
  unordered_map<char, TrieNode *> children;
};

class SuffixTrie {
public:
  TrieNode *root;
  char endSymbol;

  SuffixTrie(string str) {
    this->root = new TrieNode();
    this->endSymbol = '*';
    this->populateSuffixTrieFrom(str);
  }

  void populateSuffixTrieFrom(string str) {
    for (auto it = begin(str); it != end(str); ++it) {
			addSuffix(it, end(str));
		}
  }

  bool contains(string str) {
    auto node = root;
		
		for (auto c : str) {
			auto& children = node->children;
			auto it = children.find(c);
			
			if (it == end(children)) {
				return false;
			}
			
			node = it->second;
		}
		
    return node->children.find(endSymbol) != end(node->children);
  }
	
private:
	template <class It>
	void addSuffix(It itBegin, It itEnd)
	{
		auto node = root;
		
		for (auto c = itBegin; c != itEnd; ++c) {
			auto& children = node->children;
			auto it = children.find(*c);
			
			if (it == end(children)) {
				node = new TrieNode();
				children.insert({*c, node});
			} else {
				node = it->second;
			}
		}
		
		auto& children = node->children;
		auto it = children.find(endSymbol);
		
		if (it == end(children)) {
			children.insert({endSymbol, nullptr});
		}
	}
};


int main()
{
    SuffixTrie trie("helloworld");

    cout << "world: " << (trie.contains("world") ? "true" : "false") << endl;

    return 0;
}