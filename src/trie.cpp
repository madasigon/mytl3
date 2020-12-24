
#include "base.cpp"

#ifndef TRIE_CPP
#define TRIE_CPP

//STARTCOPY
namespace mytl{

template<typename T, typename C = map<T, void*>, typename Data = tuple<>>
struct TrieNode {

    TrieNode* parent = nullptr;
    T label;
    C next = C();


    Data data = Data();

    TrieNode() {}
    TrieNode(TrieNode* parent, T label) : parent{ parent }, label{ label } {}


    TrieNode* jump(T c) {
        if (next[c] == nullptr) {
            next[c] = new TrieNode(this, c);
        }
        return (TrieNode*)next[c];
    }

    
    TrieNode* traverse(const vector<T>& s, function<void(Data&)> operation = [](Data &data) {}) {
        TrieNode* curr = this;

        operation(curr->data);
        for (T c : s) {
            curr = curr->jump(c);
            operation(curr->data);
        }
        return curr;
    }

    TrieNode* traverse(const string& s, function<void(Data&)> operation = [](Data& data) {}) {
        return traverse(vector<char>(s.begin(), s.end()), operation);
    }
};

}
//ENDCOPY

#endif