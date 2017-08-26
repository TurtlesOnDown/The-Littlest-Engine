#include "Includes.h"

class System;

#ifndef MESSAGEBUS
#define MESSAGEBUS

// Message object
struct Message {
  std::string sender;
  std::string message;
};

// Message bus for communication between systems or inside of systems
class MessageBus {
public:
  // Adds a system listener
  void addSystem(System *);
  // adds a message to the queue
  void addMessage(const Message *);

  // notifies all systems and empties the queue
  void notfitySystems();

  // immediately sends the current message to all systems attached to the bus, use sparingly
  void immediateMessage(const Message &);

private:
  std::queue<const Message *> messages;
  std::vector<System *> systems;
};


#endif // !MESSAGEBUS