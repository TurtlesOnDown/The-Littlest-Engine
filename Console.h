#include "Includes.h"

#include "System.h"

#ifndef CONSOLE
#define CONSOLE

class Console : public System {
public:
  Console(MessageBus *);
  void processMessage(const Message *) override;

  void getInput();

  template<typename T>
  void printToConsole(T) const;

  template<typename T, typename... Args>
  void printToConsole(T, Args...) const;


private:
  void processCommand(const std::vector<std::string> &);
};

template<typename T, typename... Args>
void Console::printToConsole(T head, Args... tail) const {
  std::cout << head << " : ";
  printToConsole(tail...);
}

template<typename T>
void Console::printToConsole(T head) const {
  std::cout << head << std::endl;
}

#endif // !CONSOLE
