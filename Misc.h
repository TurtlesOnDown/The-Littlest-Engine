#pragma once

#include "Includes.h"

#ifndef MISCELLANEOUS
#define MISCELLANEOUS

uint32 stringtoUintHash(const std::string &toHash);

constexpr uint32 cstringToUintHash(const char *toHash)
{
  return toHash[0] == 0 ? 0 : (toHash[0] + cstringToUintHash(&toHash[1]));
}

#endif // !MISCELLANEOUS