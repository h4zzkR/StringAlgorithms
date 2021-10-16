#ifndef AHO_CORASICK_AHO_H
#define AHO_CORASICK_AHO_H

#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include "trie.h"

struct AhoCorasick {
    std::vector<int> order_of_traversal; // закодированные терминальными вершинами словарные слова
    Trie trie;

    AhoCorasick(int alphabet_size, int alphabet_shift = 'a'): trie(Trie(alphabet_size, alphabet_shift)) {}

    void add_word(std::string& word) {
        int v = trie.add(word);
        order_of_traversal.push_back(v);
    }

    void aho_linking() {
        std::queue<int> Q;

        for (char i = trie.alphabet_shift; i < trie.alphabet_shift + trie.alphabet_size; ++i) {
            if (trie.can_walk(0, i)) {
                trie.set_transition(0, i, trie.get_transition(0, i));
            } else {
                trie.set_transition(0, i, 0);
            }
        }

        trie.at(0)->term_link = 0;

        Q.push(0);
        while (!Q.empty()) {
            int parent = Q.front(); Q.pop();
            for (char ch = trie.alphabet_shift; ch < trie.alphabet_shift + trie.alphabet_size; ++ch) {
                int son = trie.get_transition(parent, ch);
                if (son == -1 || trie.get_suff_link(son) != -1) continue;

                // SUFF_LINKS CREATION
                if (parent == 0) {
                    trie.set_suff_link(son, 0);
                    trie.set_term_link(son, 0);
                } else {
                    trie.set_suff_link(son, trie.get_transition(trie.get_suff_link(parent), ch));

                    int son_link = trie.get_suff_link(son);
                    if (trie.is_term(son_link)) {
                        trie.set_term_link(son, son_link);
                    } else {
                        trie.set_term_link(son, trie.get_term_link(son_link));
                    } // nearest terminal node
                }

                // предподсчет переходов
                for (char ch2 = trie.alphabet_shift; ch2 < trie.alphabet_shift + trie.alphabet_size; ++ch2) {
                    if (trie.get_transition(son, ch2) == -1) { // из вершины нет перехода по d, перескакиваем
                        trie.set_transition(son, ch2, trie.get_transition(trie.get_suff_link(son), ch2));
                    }
                }
                Q.push(son);
            }
        }
    }

    void lookup(int v, int pos_in_text, std::unordered_map<int, std::vector<int>>& entries) {
        int node = v;
        while (node != -1 && node != 0) {
            if (trie.at(node)->is_term) { // if for the first iteration
                int entry_pos = pos_in_text - trie.at(node)->height + 2; // here height is length of dict word
                entries[node].push_back(entry_pos);
            }
            node = trie.at(node)->term_link;
        }
    }

    void search(std::string& text) {
        std::unordered_map<int, std::vector<int>> entries;
        int curv = 0;
        for (int i = 0; i < text.size(); ++i) {
            char c = text[i];
            curv = trie.get_transition(curv, c);
            lookup(curv, i, entries);
        }
        for (int v : order_of_traversal) {
            auto found = entries.find(v);
            if (found == entries.end()) {
                std::cout << 0 << '\n';
                continue;
            }
            std::cout << found->second.size() << ' ';
            for (auto& indexes : found->second) {
                std::cout << indexes << ' ';
            }
            std::cout << std::endl;
        }
    }

};

#endif //AHO_CORASICK_AHO_H
