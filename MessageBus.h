#include "Includes.h"

class System;

#ifndef MESSAGEBUS
#define MESSAGEBUS

// Message structure for each system to use
struct Message {
  std::string sender;
  std::string message;
};

class MessageBus {
public:
  void addSystem(System *);
  void addMessage(const Message *);

  void notfitySystems();

  void immediateMessage(const Message &);

private:
  std::queue<const Message *> messages;
  std::vector<System *> systems;
};


#endif // !MESSAGEBUS