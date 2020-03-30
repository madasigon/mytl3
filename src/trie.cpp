
#include "base.cpp"

#ifndef TRIE_CPP
#define TRIE_CPP

//STARTCOPY
namespace mytl{

template<typename Op_>
struct Trie {
	struct Node;
	using Op = Op_;
	using T = typename Op::T;
	using Info = typename Op::template Info<Node>;
	using Next_Container = typename Op::template Next<Node*>;

	struct Node : Info {
		Node *parent;
		T last;
		Next_Container next;
		need_int leaf = 0;
		Node *jump(T c) {
			if (next.contains(c)) {
				return next[c];
			}
			else return nullptr;
		}

		Node(Node *parent, T last) : parent{ parent }, last{ last } {}
	};

	Node *root = new Node(nullptr, T());

	template<typename C>
	Node *insert_word(C word, need_int leaf_flag = 1) {
		Node *curr = root;
		for (T c : word) {
			if (!curr->next.contains(c)) {
				curr->next[c] = new Node(curr, c);
			}
			curr = curr->next[c];
		}
		curr->leaf = leaf_flag;
		return curr;
	}

	template<typename C>
	Node* jump_path(Node* node, C path) {
		for (T c : path) {
			if (node == nullptr) return node;
			node = node->jump(c);
		}
		return node;
	}

	template<typename C>
	bool contains_word(C word) {
		Node *res = jump_path(root, word);
		return res && res->leaf;
	}


};


template<need_int ALPHABETSIZE>
struct Basic_Char_Trie_Op {
	using T = char;

	template<typename Node>
	struct Info {
	};

	template<typename N>
	struct Next {
		N next[ALPHABETSIZE] = {};

		N& operator[](char i) {
			return next[i - 'a'];
		}

		bool contains(char i) {
			return operator[](i) != nullptr;
		}

	};

};


template<need_int ALPHABET_SIZE>
using CharTrie = Trie<Basic_Char_Trie_Op<ALPHABET_SIZE> >;


}
//ENDCOPY

#endif