#include "../header/AhoCorasik2.h"

int main() {
  Bohr_v v(0, 0);
  bohr.push_back(v);

  std::string text, keyword;
  char j;
  std::cin >> text;
  std::cin >> keyword;
  std::cin >> j;
  std::vector<int> cnt(text.size(), 0);
  std::vector<int> part_len = patterns(keyword, j);
  find(text, cnt, part_len);

  std::vector<std::string> result = out_2(cnt);
  for (auto i : result) {
    std::cout << i << std::endl;
  }
}