#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "../header/AhoCorasik.h"

struct Aho_Corasik_test_case {
  Aho_Corasik_test_case(std::string&& str, std::vector<std::string>&& patterns, std::vector<std::string>&& entries_array = {}):
      str(str), patterns(patterns), entries_array(entries_array) {}

  std::string str;
  std::vector<std::string> patterns;
  std::vector<std::string> entries_array;
};

class Aho_Corasik_test: public testing::TestWithParam<Aho_Corasik_test_case> {
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

TEST_P(Aho_Corasik_test, test) {
  Aho_Corasik_test_case param = GetParam();

  for (auto const& pattern : param.patterns) {
    add_to_bohr(pattern);
  }

  std::vector<std::string> result = find(param.str);
  ASSERT_THAT(result, testing::ContainerEq(param.entries_array));
}

INSTANTIATE_TEST_CASE_P(success, Aho_Corasik_test, ::testing::Values(
    Aho_Corasik_test_case( // random
        "ACGATAACCNAAG",
        {"ATAAC", "AAC", "AC", "NAF"},
        {"1 3", "4 1", "6 2", "7 3"}
    ),
    Aho_Corasik_test_case( // random
        "ANACTANNAGAAACNG",
        {"ANACTAN", "ANA", "ANACTG", "NA", "TA", "ANNAGA"},
        {"1 2", "2 4", "5 5", "1 1", "8 4", "6 6"}
    ),
    Aho_Corasik_test_case( // only one "good" pattern
        "ANCGAD",
        {"GAD", "TAC", "NTGC"},
        {"4 1"}
    ),
    Aho_Corasik_test_case( // only one "good" pattern
        "AAAGACA",
        {"A"},
        {"1 1", "2 1", "3 1", "5 1", "7 1"}
    )
));

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}


