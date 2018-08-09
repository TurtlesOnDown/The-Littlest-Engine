#include "Console.h"

#include <numeric>

#include "../Engine/Utility/Misc.h"

Console::Console(MessageBus *mainBus):System(mainBus) {
}

void Console::processMessage(const Message *newMessage) {
  printToConsole(" : ", newMessage->sender, newMessage->message);
}

void Console::getInput() {
  std::string command;
  while (true) {
    // Get the input
    getline(std::cin, command);
    if (command == "exitconsole") break;
    // process tokens
    processCommand(tokenize(command, ' '));
  }

}

void Console::processCommand(const std::vector<std::string> &args) {
  if (args.size() < 1) return;
  switch (stringtoUintHash(args[0]))
  {
  case cstringToUintHash("execute"): // send content to message bus
    s_MessageBus->immediateMessage({ "CONSOLE" , std::accumulate(args.begin() + 2, args.end(), std::string(args[1]), [](std::string a, std::string b) {return a + ":" + b; }) });
    break;
  case cstringToUintHash("notify"): // send content to message bus
    s_MessageBus->notfitySystems();
    break;
  default: // command not found
    printToConsole(":", "ERROR", "CONSOLE", "INVALID COMMAND");
    break;
  }
}
