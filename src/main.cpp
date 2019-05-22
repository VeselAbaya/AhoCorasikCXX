#include <iostream>
#include "../header/AhoCorasik.h"

int main () {
  int n;
  std::string text, keyword;
  std::cin >> text;
  std::cin >> n;
  std::vector<std::string> patterns(n);
  for (int i = 0; i < n; i++) {
    std::cin >> patterns[i];
  }

  std::vector<std::pair<int, int>> result = Aho_Corasik::find(text, patterns);

  for (auto p: result) {
    std::cout << p.first << ' ' << p.second << std::endl;
  }
}