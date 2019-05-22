#include <iostream>
#include "../header/AhoCorasik.h"

int main () {
  int n;
  std::wstring text, keyword;

  std::wcin >> text;
  std::wcin >> n;
  std::vector<std::wstring> patterns(n);
  for (int i = 0; i < n; i++) {
    std::wcin >> patterns[i];
  }

  std::vector<std::pair<int, int>> result = Aho_Corasik::find(text, patterns);

  for (auto p: result) {
    std::cout << p.first << ' ' << p.second << std::endl;
  }
}