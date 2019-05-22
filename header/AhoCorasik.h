#ifndef AHOCORASIK_AHOCORASIK_H
#define AHOCORASIK_AHOCORASIK_H

#include <iostream>
#include <vector>
#include <cstring>
#include <map>
#include <algorithm>
#include <sstream>

#define MAXSIZE 6

class Aho_Corasik {
public:
  class Bohr {
  public:
    friend Aho_Corasik;

    Bohr() {};
    Bohr(std::vector<std::wstring> const& patterns);

    void add(std::wstring const& str);

    int getAutoMove(int node_number, int ch);
    int getSuff(int node_number);

  private:
    struct Bohr_node {
      int next_node[MAXSIZE]; // массив, где next_node[i] - номер вершины, в которую мы переходим по символу с номером i в алфавите
      int patternNum;         // номер строки-образца, обозначающего вершиной next_node[i]
      bool flag;              // бит, указывающий, явл-я ли вершина конечной
      int suffLink;           // суффиксная ссылка
      int autoMove[MAXSIZE];  // запоминание перехода автомата
      int parent;             // вершина - родитель
      char symbol;            // символ на ребре от parent к этой вершине

      Bohr_node() {};
      Bohr_node(int parent, char symbol);
    };

    std::vector<Bohr_node> nodes;
    std::vector<std::wstring> patterns;
  };

  Aho_Corasik(std::wstring const& str, std::vector<std::wstring> const& patterns);

  static std::vector<std::pair<int, int>> find(std::wstring const& str, std::vector<std::wstring> const& patterns);

private:
  std::vector<std::pair<int, int>> _find();

  Bohr bohr;
  std::wstring str;
};

#endif //AHOCORASIK_AHOCORASIK_H
