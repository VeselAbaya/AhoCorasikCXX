#ifndef AHOCORASIK_AHOCORASIK2_H
#define AHOCORASIK_AHOCORASIK2_H

#include <iostream>
#include <vector>
#include <cstring>
#include <map>
#include <algorithm>
#include <sstream>

#define MAXSIZE 6

struct Bohr_v {
  int next_node[MAXSIZE];      // массив, где next_node[i] - номер вершины, в которую мы переходим по символу с номером i в алфавите
  std::vector<int> patternNums; // номер строки-образца, обозначающего вершиной next_node[i]
  bool flag;                   // бит, указывающий, явл-я ли вершина конечной
  int suffLink;                // суффиксная ссылка
  int autoMove[MAXSIZE];       // запоминание перехода автомата
  int parent;                  // вершина - родитель
  char symbol;                 // символ на ребре от parent к этой вершине

  Bohr_v() {}

  Bohr_v(int parent, char symbol);
};

extern std::vector<Bohr_v> bohr;
extern std::vector<std::string> pattern;

void add_to_bohr(const std::string &str);
std::vector<std::string> out_2(const std::vector<int>& cnt);

std::vector<int> patterns(std::string& pattern, char joker);

std::vector<std::string> find(const std::string &str, std::vector<int>& cnt, const std::vector<int>& part_len);

#endif //AHOCORASIK_AHOCORASIK2_H
