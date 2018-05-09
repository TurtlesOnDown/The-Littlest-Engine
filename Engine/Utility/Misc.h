#pragma once

#include "Includes.h"

#ifndef MISCELLANEOUS
#define MISCELLANEOUS

uint32 stringtoUintHash(const std::string &toHash);

// converts a cstring into an unsigned 32-bit int at compile time if possible
constexpr uint32 cstringToUintHash(const char *toHash)
{
  return toHash[0] == 0 ? 0 : (toHash[0] + cstringToUintHash(&toHash[1]));
}

// returns a vector of strings from a string seperated by a delimitor
std::vector<std::string> tokenize(const std::string &, char);

#endif // !MISCELLANEOUS