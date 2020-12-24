
#include "corasick.cpp"
#include "trie.cpp"
using namespace std;




using Cora = mytl::Corasick<char>;




void corasick_test() {
	vector<string> dict{ "a", "abcd", "cdef","fgh", "ghia", "never" };
	Cora trie(dict);
	
	
	string bigword = "abcdefghia";

	vector<ll> matches(dict.size());
	auto n = trie.root;
	for (ll i = 0; i < bigword.size(); i++) {
		n = trie.go(n, bigword[i]);
		for (auto elem : trie.hits(n)) {
			matches[elem]++;
		}
	}

	debug_assert((matches == vector<ll>{2, 1, 1, 1, 1, 0}));
	

}