
#include "corasick.cpp"
#include "trie.cpp"
using namespace std;




using Cora = mytl::Corasick<mytl::CharTrie<26> >;

string path(Cora::Node *n) {
	string res = "";
	while (n != nullptr) {
		res.push_back(n->last);
		n = n->parent;
	}
	res.pop_back();
	reverse(res.begin(), res.end());
	return res;
}



void corasick_test() {
	vector<string> dict{ "a", "abcd", "cdef","fgh", "ghia", "never" };
	Cora trie(dict);
	
	
	string bigword = "abcdefghia";

	vector<ll> matches(dict.size());
	auto n = trie.trie.root;
	for (ll i = 0; i < bigword.size(); i++) {
		n = Cora::go(n, bigword[i]);
		for (auto elem : Cora::current_matches(n)) {
			matches[elem-1]++;
		}
	}

	assert((matches == vector<ll>{2, 1, 1, 1, 1, 0}));
	

}