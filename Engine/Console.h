#include "../Engine/Common/Includes.h"

#include "../Engine/System/System.h"

#ifndef CONSOLE
#define CONSOLE

// Console System
class Console : public System {
public:
  Console(MessageBus *);
  // Prints all messages to the console
  void processMessage(const Message *) override;

  // request input from the user
  void getInput();

  // Prints an arbitrary number of arguments to the console
  // Elements must have a valid ostream &operator<<
  // first argument must be a string, indicating what to seperate the strings with, "" means no seperation
  template<typename T>
  void printToConsole(const std::string &, T) const;

  template<typename T, typename... Args>
  void printToConsole(const std::string &, T, Args...) const;


private:
  void processCommand(const std::vector<std::string> &);
};

template<typename T, typename... Args>
void Console::printToConsole(const std::string &delim, T head, Args... tail) const {
  std::cout << head << delim;
  printToConsole(delim, tail...);
}

template<typename T>
void Console::printToConsole(const std::string &delim, T head) const {
  std::cout << head << std::endl;
}

#endif // !CONSOLE
