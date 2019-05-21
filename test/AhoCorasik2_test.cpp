#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "../header/AhoCorasik2.h"

struct Aho_Corasik2_test_case {
  Aho_Corasik2_test_case(std::string&& str, std::string&& pattern, std::vector<std::string>&& entries_array = {}):
      str(str), pattern(pattern), entries_array(entries_array) {}

  std::string str;
  std::string pattern;
  std::vector<std::string> entries_array;
};

class Aho_Corasik2_test: public testing::TestWithParam<Aho_Corasik2_test_case> {
public:
  void SetUp() override {
    Bohr_v v(0, 0);
    bohr.push_back(v);
  }

  void TearDown() override {
    bohr.clear();
    pattern.clear();
  }
};

TEST_P(Aho_Corasik2_test, test) {
  Aho_Corasik2_test_case param = GetParam();

  std::vector<int> cnt(param.str.size(), 0);
  std::vector<int> part_len = patterns(param.pattern, '$');
  find(param.str, cnt, part_len);
  std::vector<std::string> result = out_2(cnt);

  ASSERT_THAT(result, testing::ContainerEq(param.entries_array));
}

INSTANTIATE_TEST_CASE_P(success, Aho_Corasik2_test, ::testing::Values(
    Aho_Corasik2_test_case( // random
        "AABCTANCG",
        "A$C",
        {"2", "6"}
    ),
    Aho_Corasik2_test_case( // empty parts
        "GATNCCTATATCAG",
        "AT$$C$",
        {"2", "8"}
    ),
    Aho_Corasik2_test_case( // without j
        "ACGANGA",
        "GA",
        {"3", "6"}
    ),
    Aho_Corasik2_test_case( // only j
        "AAAAA",
        "$",
        {"1", "2", "3", "4", "5"}
    )
));

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}


