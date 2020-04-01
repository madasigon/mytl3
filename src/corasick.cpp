
#include "base.cpp"

#ifndef CORASICK_CPP
#define CORASICK_CPP

//STARTCOPY
namespace mytl{

template<typename BaseTrie>
struct Corasick {

	struct Corasick_Op : BaseTrie::Op {
		using T = typename BaseTrie::Op::T;

		template<typename N>
		struct Info {
			N* next_leaf_d = nullptr;
			N* link_d = nullptr;
			typename BaseTrie::Op::template Next<N*> go_d;
		};
	};

	using MyTrie = Trie<Corasick_Op>;
	using Node = typename MyTrie::Node;
	using T = typename Corasick_Op::T;

	MyTrie trie;

	static Node* go(Node *node, T c) {
		if (!node->go_d.contains(c)) {
			if (node->next.contains(c)) {
				node->go_d[c] = node->next[c];
			}
			else if (node->parent == nullptr) {
				node->go_d[c] = node;
			}
			else {
				node->go_d[c] = go(link(node), c);
			}
		}
		return node->go_d[c];
	};

	static Node* link(Node *node) {
		if (node->link_d == nullptr) {
			if (node->parent == nullptr) {
				node->link_d = node;
			}
			else if (node->parent->parent == nullptr) {
				node->link_d = node->parent;
			}
			else {
				node->link_d = go(link(node->parent), node->last);
			}
		}
		return node->link_d;
	}

	static Node* next_leaf(Node *node) {
		if (node->next_leaf_d == nullptr) {
			if (node->parent == nullptr) {
				node->next_leaf_d = node;
			}
			else {
				if (link(node)->leaf) {
					node->next_leaf_d = link(node);
				}
				else {
					node->next_leaf_d = next_leaf(link(node));
					if (!node->next_leaf_d->leaf) {
						node->next_leaf_d = node;
					}
				}
			}
		}
		return node->next_leaf_d;
	}

	static vector<need_int> current_matches(Node* node) {
		vector<need_int> res;
		if (node->leaf) res.push_back(node->leaf);
		while (next_leaf(node) != node) {
			node = next_leaf(node);
			res.push_back(node->leaf);
		}
		return res;
	}

	Node *root = trie.root;


	template<typename C>
	Corasick(C dictionary) {
		need_int i = 0;
		for (auto word : dictionary) {
			trie.insert_word(word, ++i);
		}
	}

};


}
//ENDCOPY

#endif