#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "../header/AhoCorasik.h"

TEST(AhoCorasik, test) {
  bohr.clear();
  pattern.clear();

  Bohr_v v(0, 0);
  bohr.push_back(v);

  add_to_bohr("ATAAC");
  add_to_bohr("AAC");
  add_to_bohr("AC");
  add_to_bohr("NAF");

  std::vector<std::string> result = find("ACGATAACCNAAG");
  std::string str_result = "";
  for (size_t i = 0; i != result.size(); ++i) {
    str_result += result[i];
    if (i != result.size() - 1) {
      str_result += " ";
    }
  }

  ASSERT_EQ(str_result, "1 3 4 1 6 2 7 3");
}

TEST(AhoCorasik, test_prefix) {
  bohr.clear();
  pattern.clear();

  Bohr_v v(0, 0);
  bohr.push_back(v);

  add_to_bohr("ANACTAN");
  add_to_bohr("ANA");
  add_to_bohr("ANACTG");
  add_to_bohr("NA");
  add_to_bohr("TA");
  add_to_bohr("ANNAGA");

  std::vector<std::string> result = find("ANACTANNAGAAACNG");
  std::string str_result = "";
  for (size_t i = 0; i != result.size(); ++i) {
    str_result += result[i];
    if (i != result.size() - 1) {
      str_result += " ";
    }
  }

  ASSERT_EQ(str_result, "1 2 2 4 5 5 1 1 8 4 6 6");
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}


