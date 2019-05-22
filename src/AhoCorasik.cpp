#include "../header/AhoCorasik.h"

int stepikCharCode(wchar_t ch) {
  int code;
  switch(ch) {
    case L'A':
    case L'Ф':
      code = 0;
    break;
    case L'C':
    case L'Ы':
      code = 1;
    break;
    case L'G':
    case L'В':
      code = 2;
    break;
    case L'T':
    case L'А':
      code = 3;
    break;
    case L'N':
    case L'П':
      code = 4;
    break;
    default:
      code = 5;
    break;
  }

  return code;
}

Aho_Corasik::Bohr::Bohr_node::Bohr_node(int parent, char symbol) {
  for (int i = 0; i < MAXSIZE; i++) {
    next_node[i] = -1;
  }

  this->patternNum = 0;
  flag = false;
  suffLink = -1;

  for (int i = 0; i < MAXSIZE; i++) {
    autoMove[i] = -1;
  }

  this->parent = parent;
  this->symbol = symbol;
}

Aho_Corasik::Bohr::Bohr(std::vector<std::wstring> const& patterns) {
  Bohr_node v(0, 0);
  this->nodes.push_back(v);

  for(std::wstring const& pattern : patterns) {
    this->add(pattern);
  }
}

// Добавление образца в бор
void Aho_Corasik::Bohr::add(const std::wstring &str) {
  int parent_number = 0;
  for (int i = 0; i < str.length(); i++) {
    int ch = stepikCharCode(str[i]);

    // нет ребра
    if (this->nodes[parent_number].next_node[ch] == -1)	{
      Bohr_node node(parent_number, ch);
      this->nodes.push_back(node);
      this->nodes[parent_number].next_node[ch] = this->nodes.size() - 1;
    }

    parent_number = this->nodes[parent_number].next_node[ch];
  }

  this->nodes[parent_number].flag = true;
  this->patterns.push_back(str);
  this->nodes[parent_number].patternNum = this->patterns.size() - 1;
}

// Получаем суффиксную ссылку
int Aho_Corasik::Bohr::getSuff(int node_number) {
  if (nodes[node_number].suffLink == -1) {
    if (node_number == 0 || nodes[node_number].parent == 0) {
      nodes[node_number].suffLink = 0;
    }
    else {
      nodes[node_number].suffLink = getAutoMove(getSuff(nodes[node_number].parent), nodes[node_number].symbol);
    }
  }

  return nodes[node_number].suffLink;
}

int Aho_Corasik::Bohr::getAutoMove(int node_number, int ch) {
  if (nodes[node_number].autoMove[ch] == -1) {
    if (nodes[node_number].next_node[ch] != -1) {
      nodes[node_number].autoMove[ch] = nodes[node_number].next_node[ch];
    }
    else {
      if (node_number == 0) { // if root there no sufflink
        nodes[node_number].autoMove[ch] = 0;
      }
      else {
        nodes[node_number].autoMove[ch] = getAutoMove(getSuff(node_number), ch);
      }
    }
  }

  return nodes[node_number].autoMove[ch];
}

Aho_Corasik::Aho_Corasik(std::wstring const& str, std::vector<std::wstring> const &patterns): str(str) {
  bohr = Bohr(patterns);
}

std::vector<std::pair<int, int>> Aho_Corasik::_find() {
  int node_number = 0;
  std::vector<std::pair<int, int>> result;
  for(int i = 0; i < str.length(); i++) {
    int ch = stepikCharCode(str[i]);

    node_number = bohr.getAutoMove(node_number, ch);

    for(int u = node_number; u != 0; u = bohr.getSuff(u)) {
      if (bohr.nodes[u].flag) {
        result.emplace_back(
          std::make_pair(i+1 - bohr.patterns[bohr.nodes[u].patternNum].length() + 1, bohr.nodes[u].patternNum + 1)
        );
      }
    }
  }

  return result;
}

std::vector<std::pair<int, int>> Aho_Corasik::find(std::wstring const& str, std::vector<std::wstring> const& patterns) {
  return Aho_Corasik(str, patterns)._find();
}
