#include "../header/AhoCorasik.h"

std::vector<Bohr_v> bohr;
std::vector<std::string> pattern;

Bohr_v::Bohr_v(int parent, char symbol) {
  for (int i = 0; i < MAXSIZE; i++) {
    next_node[i] = -1;
  }

  patternNums = 0;
  flag = false;
  suffLink = -1;

  for (int i = 0; i < MAXSIZE; i++) {
    autoMove[i] = -1;
  }

  this->parent = parent;
  this->symbol = symbol;
}

// Добавление образца в бор
void add_to_bohr(const std::string &str) {
  int parent_number = 0;
  for (int i = 0; i < str.length(); i++) {
    int ch;
    switch(str[i]) {
      case 'A':
        ch = 0;
        break;
      case 'C':
        ch = 1;
        break;
      case 'G':
        ch = 2;
        break;
      case 'T':
        ch = 3;
        break;
      case 'N':
        ch = 4;
        break;
      default:
        ch = 5;
        break;
    }

    // нет ребра
    if (bohr[parent_number].next_node[ch] == -1)	{
      Bohr_v node(parent_number, ch);
      bohr.push_back(node);
      bohr[parent_number].next_node[ch] = bohr.size() - 1;
    }

    parent_number = bohr[parent_number].next_node[ch];
  }

  bohr[parent_number].flag = true;
  pattern.push_back(str);
  bohr[parent_number].patternNums = pattern.size() - 1;
}

int getAutoMove(int node_number, int ch);

// Получаем суффиксную ссылку
int getSuff(int node_number) {
  if (bohr[node_number].suffLink == -1) {
    if (node_number == 0 || bohr[node_number].parent == 0) {
      bohr[node_number].suffLink = 0;
    }
    else {
      bohr[node_number].suffLink = getAutoMove(getSuff(bohr[node_number].parent), bohr[node_number].symbol);
    }
  }

  return bohr[node_number].suffLink;
}

int getAutoMove(int node_number, int ch) {
  if (bohr[node_number].autoMove[ch] == -1) {
    if (bohr[node_number].next_node[ch] != -1) {
      bohr[node_number].autoMove[ch] = bohr[node_number].next_node[ch];
    }
    else {
      if (node_number == 0) { // if root there no sufflink
        bohr[node_number].autoMove[ch] = 0;
      }
      else {
        bohr[node_number].autoMove[ch] = getAutoMove(getSuff(node_number), ch);
      }
    }
  }

  return bohr[node_number].autoMove[ch];
}


void out(int node_number, int i, std::vector<std::string>& result) {
  for(int u = node_number; u != 0; u = getSuff(u)) {
    if (bohr[u].flag) {
      std::stringstream stream;
      stream << i - pattern[bohr[u].patternNums].length() + 1 << " "
             << bohr[u].patternNums + 1;

      result.push_back(stream.str());
    }
  }
}

std::vector<std::string> find(const std::string &str) {
  int borh_node_number = 0;
  std::vector<std::string> result;
  for(int i = 0; i < str.length(); i++) {
    int ch;
    switch(str[i]) {
      case 'A':
        ch = 0;
        break;
      case 'C':
        ch = 1;
        break;
      case 'G':
        ch = 2;
        break;
      case 'T':
        ch = 3;
        break;
      case 'N':
        ch = 4;
        break;
      default:
        ch = 5;
        break;
    }

    borh_node_number = getAutoMove(borh_node_number, ch);
    out(borh_node_number, i + 1, result);
  }

  return result;
}