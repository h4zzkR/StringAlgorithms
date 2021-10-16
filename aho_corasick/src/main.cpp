#include <iostream>
#include "aho.h"

int main() {
    AhoCorasick a(26);
    std::string text;
    std::cin >> text;

    int n;
    std::string input;
    std::cin >> n;
    for (int i = 0; i < n; ++i) {
        std::cin >> input;
        a.add_word(input);
    }

    a.aho_linking();
    a.search(text);
    int t = 0;
    return 0;
}