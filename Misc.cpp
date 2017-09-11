#include "Misc.h"

uint32 stringtoUintHash(const std::string &toHash) {
  uint32 result = 0;
  for (auto each : toHash) {
    result += each;
  }
  return result;
}

std::vector<std::string> tokenize(const std::string &input, char delim) {
  std::string newString = input;
  // parse input into tokens
  std::vector<std::string> tokens;
  while (newString.size()) {
    if (newString.find(delim) == std::string::npos) {
      tokens.push_back(newString);
      newString.clear();
    }
    else {
      tokens.push_back(newString.substr(0, newString.find(delim)));
      newString = newString.substr(newString.find(delim) + 1);
    }
  }
  return tokens;
}

