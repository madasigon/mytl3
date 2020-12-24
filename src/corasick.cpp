
#include "base.cpp"
#include "trie.cpp"

#ifndef CORASICK_CPP
#define CORASICK_CPP

//STARTCOPY
namespace mytl{

template<typename T, typename C = map<T, void*>>
struct Corasick {
    struct Data {
        void* next_left = nullptr;
        void* link = nullptr;
        void* exit_link = nullptr;
        C go;
        vector<need_int> hits;
    };

    using State = TrieNode<T, C, Data>;

    State *root = new State;
    


    State* link(State *curr) {
        void*& kulcs = curr->data.link;
        if (kulcs == nullptr) {
            if (curr == root || curr->parent == root) {
                kulcs = root;
            }
            else {
                kulcs = go(link(curr->parent), curr->label);
            }
        }
        return (State*)kulcs;
    }
    State* go(State* curr, T c) {
        void*& kulcs = curr->data.go[c];
        if (kulcs == nullptr) {
            if (curr->next[c] != nullptr) {
                kulcs = curr->next[c];
            }
            else {
                if (curr->parent == nullptr) {
                    kulcs = root;
                }
                else {
                    kulcs = go(link(curr), c);
                }
            }
        }
        return (State*)kulcs;
    }

    State* exit_link(State* curr) {
        State*& kulcs = (State*&)curr->data.exit_link;

        if (kulcs == nullptr) {
            if (curr == root) {
                kulcs = nullptr;
            }
            else {
                if (!link(curr)->data.hits.empty()) kulcs = link(curr);
                else kulcs = exit_link(link(curr));
            }
        }
        return kulcs;
    }


public:

    template<typename Word>
    Corasick(const vector<Word>& words) {
        for (need_int i = 0; i < words.size(); i++) {
            root->traverse(words[i])->data.hits.push_back(i);
        }
    }

    State* step(State* currstate, T c) {
        return go(currstate, c);
    }

    State* initial_state() {
        return root;
    }

    vector<need_int> hits(State* currstate) {
        State* curr = currstate;

        vector<need_int> res;

        while (curr != nullptr) {
            res.insert(res.end(), curr->data.hits.begin(), curr->data.hits.end());
            curr = exit_link(curr);
        }

        return res;
    }

    need_int num_hits(State* currstate) {
        State* curr = currstate;

        need_int ans = 0;

        while (curr != nullptr) {
            ans += curr->data.hits.size();
            curr = exit_link(curr);
        }
        return ans;
    }

};


}
//ENDCOPY

#endif