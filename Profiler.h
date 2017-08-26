#include "Includes.h"

#include <ctime>

#ifndef PROFILER
#define PROFILER

class Stopwatch {
public:
  void start();
  void stop();

  double getSeconds() const;
  double getMiliseconds() const;

private:
  double duration;
};

#endif // !PROFILER

