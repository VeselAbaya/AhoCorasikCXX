#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "../header/AhoCorasik.h"

struct Aho_Corasik_test_case {
  Aho_Corasik_test_case(std::wstring&& str, std::vector<std::wstring>&& patterns, std::vector<std::pair<int,int>>&& entries_array = {}):
      str(str), patterns(patterns), entries_array(entries_array) {}

  std::wstring str;
  std::vector<std::wstring> patterns;
  std::vector<std::pair<int, int>> entries_array;
};

class Aho_Corasik_test: public testing::TestWithParam<Aho_Corasik_test_case> {
public:
  void SetUp() override {}

  void TearDown() override {}
};

TEST_P(Aho_Corasik_test, test) {
  Aho_Corasik_test_case param = GetParam();
  ASSERT_THAT(Aho_Corasik::find(param.str, param.patterns), testing::ContainerEq(param.entries_array));
}

INSTANTIATE_TEST_CASE_P(success, Aho_Corasik_test, ::testing::Values(
    Aho_Corasik_test_case( // random
        L"ACGATAACCNAAG",
        {L"ATAAC", L"AAC", L"AC", L"NAF"},
        {{1, 3}, {4, 1}, {6, 2}, {7, 3}}
    ),
    Aho_Corasik_test_case( // random
        L"ANACTANNAGAAACNG",
        {L"ANACTAN", L"ANA", L"ANACTG", L"NA", L"TA", L"ANNAGA"},
        {{1, 2}, {2, 4}, {5, 5}, {1, 1}, {8, 4}, {6, 6}}
    ),
    Aho_Corasik_test_case( // only one "good" pattern
        L"ANCGAD",
        {L"GAD", L"TAC", L"NTGC"},
        {{4, 1}}
    ),
    Aho_Corasik_test_case( // only one "good" pattern
        L"AAAGACA",
        {L"A"},
        {{1, 1}, {2, 1}, {3, 1}, {5, 1}, {7, 1}}
    ),
    Aho_Corasik_test_case( // only one "good" pattern
        L"ФПЫАФЫВВ",
        {L"Ф", L"ФЫВ", L"ВВ"},
        {{1, 1}, {5, 1}, {5, 2}, {7, 3}}
    )
));

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}


