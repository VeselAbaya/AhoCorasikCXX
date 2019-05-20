#include <iostream>
#include "../header/AhoCorasik.h"

int main () {
  Bohr_v v(0, 0);
  bohr.push_back(v);

  int n;
  std::string text, keyword;
  std::cin >> text;
  std::cin >> n;
  for (int i = 0; i < n; i++) {
    std::cin >> keyword;
    add_to_bohr(keyword);
  }

  std::vector<std::string> result = find(text);

  for (auto str: result) {
    std::cout << str << std::endl;
  }
}