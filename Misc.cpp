#include "Misc.h"

uint32 stringtoUintHash(const std::string &toHash) {
  uint32 result = 0;
  for (auto each : toHash) {
    result += each;
  }
  return result;
}

