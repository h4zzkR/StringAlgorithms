#include <vector>

struct Trie {
    struct Node {
        std::vector<int> node_edges;

        int suff_link = -1; // собств. суффикс
        int term_link = 0;
        int height    = 0;
        bool is_term = false;

        Node() = default;
        Node(int alphabet_size) {
            node_edges = std::vector<int>(alphabet_size, -1);
        }
    };

    int alphabet_size;
    int alphabet_shift;

    std::vector<Node> trie;

    Trie(int alphabet_size, int alphabet_shift): alphabet_size(alphabet_size), alphabet_shift(alphabet_shift) {
        trie.emplace_back(this->alphabet_size);
    }

    int add(const std::string &s) {
        int v = 0;
        trie[v].term_link = 0;
        for (auto c: s) {
            if (!can_walk(v, c)) { // no way
                trie.emplace_back(alphabet_size);
                int son = int(trie.size() - 1);
                trie[v].node_edges[c - alphabet_shift] = son;
                trie[son].height = trie[v].height + 1;
            }
            v = trie[v].node_edges[c - alphabet_shift];
        }
        trie[v].is_term = true;
        return v;
    }

    Node* at(int idx) {
        return &trie[idx];
    }

    bool is_term(int idx) {
        return trie[idx].is_term;
    }

    int get_transition(int from, char c) {
        return trie[from].node_edges[c - alphabet_shift];
    }

    bool can_walk(int vertex, char character) {
        return trie[vertex].node_edges[character - alphabet_shift] != -1;
    }

    void set_transition(int from, char c, int to) {
        if (c != 0) c -= alphabet_shift;
        trie[from].node_edges[c] = to;
    }

    void set_term_link(int from, int to) {
        trie[from].term_link = to;
    }

    int get_term_link(int from) {
        return trie[from].term_link;
    }

    void set_suff_link(int from, int to) {
        trie[from].suff_link = to;
    }

    int get_suff_link(int vertex) {
        return trie[vertex].suff_link;
    }
};
