#include "Console.h"

#include <numeric>

#include "Misc.h"

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
    // parse input into tokens
    std::vector<std::string> arguments;
    while (command.size()) {
      if (command.find(" ") == std::string::npos) {
        arguments.push_back(command);
        command.clear();
      }
      else {
        arguments.push_back(command.substr(0, command.find(" ")));
        command = command.substr(command.find(" ") + 1);
      }
    }
    // process tokens
    processCommand(arguments);
  }

}

void Console::processCommand(const std::vector<std::string> &args) {
  switch (stringtoUintHash(args[0]))
  {
  case cstringToUintHash("execute"): // send content to message bus
    s_MessageBus->immediateMessage({ "CONSOLE" , std::accumulate(args.begin() + 2, args.end(), std::string(args[1]), [](std::string a, std::string b) {return a + ":" + b; }) });
    break;
  default: // command not found
    printToConsole(":", "ERROR", "CONSOLE", "INVALID COMMAND");
    break;
  }
}
