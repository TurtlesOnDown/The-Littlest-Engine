#include "Profiler.h"

void Stopwatch::start() {
  duration = std::clock();
}

void Stopwatch::stop() {
  duration = std::clock() - duration;
}

double Stopwatch::getSeconds() const {
  return duration / (double) CLOCKS_PER_SEC;
}

double Stopwatch::getMiliseconds() const {
  return (duration / (double) CLOCKS_PER_SEC) * 1000.0;
}