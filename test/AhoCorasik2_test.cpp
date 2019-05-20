#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "../header/AhoCorasik2.h"

TEST(AhoCorasik2, test) {
  bohr.clear();
  pattern.clear();

  Bohr_v v(0, 0);
  bohr.push_back(v);

  std::string text = "ACT", keyword = "A$";
  char j = '$';

  std::stringstream str_stream(keyword);
  std::vector<int> cnt(text.size(), 0);
  std::vector<int> part_len = patterns(str_stream, j);

  find(text, cnt, part_len);

  std::vector<std::string> result = out_2(cnt, text.size());
  std::string str_result = "";
  for (size_t i = 0; i != result.size(); ++i) {
    str_result += result[i];
    if (i != result.size() - 1) {
      str_result += " ";
    }
  }

  ASSERT_EQ(str_result, "1");
}

TEST(AhoCorasik2, test_1) {
  bohr.clear();
  pattern.clear();

  Bohr_v v(0, 0);
  bohr.push_back(v);

  std::string text = "AABCTANCG", keyword = "A$C";
  char j = '$';

  std::stringstream str_stream(keyword);
  std::vector<int> cnt(text.size(), 0);
  std::vector<int> part_len = patterns(str_stream, j);

  find(text, cnt, part_len);

  std::vector<std::string> result = out_2(cnt, text.size());
  std::string str_result = "";
  for (size_t i = 0; i != result.size(); ++i) {
    str_result += result[i];
    if (i != result.size() - 1) {
      str_result += " ";
    }
  }

  ASSERT_EQ(str_result, "2 6");
}

TEST(AhoCorasik2, test_2) {
  bohr.clear();
  pattern.clear();

  Bohr_v v(0, 0);
  bohr.push_back(v);

  // 𝑥𝑎𝑏𝑣𝑐𝑐𝑏𝑎𝑏𝑎𝑏𝑐𝑎𝑥
  std::string text = "GATNCCTATATCAG", keyword = "AT$$C$";
  char j = '$';

  std::stringstream str_stream(keyword);
  std::vector<int> cnt(text.size(), 0);
  std::vector<int> part_len = patterns(str_stream, j);

  find(text, cnt, part_len);

  std::vector<std::string> result = out_2(cnt, text.size());
  std::string str_result = "";
  for (size_t i = 0; i != result.size(); ++i) {
    str_result += result[i];
    if (i != result.size() - 1) {
      str_result += " ";
    }
  }

  ASSERT_EQ(str_result, "2 8");
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}


