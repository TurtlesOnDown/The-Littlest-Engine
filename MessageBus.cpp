#include "MessageBus.h"
#include "System.h"

void MessageBus::addSystem(System *newSystem) {
  systems.push_back(newSystem);
}

void MessageBus::addMessage(const Message *newMessage) {
  messages.push(newMessage);
}

void MessageBus::notfitySystems() {
  while (messages.size()) {
    const Message *nextMessage = messages.front();
    for (auto eachSystem : systems) {
      eachSystem->processMessage(nextMessage);
    }
    messages.pop();
  }
}

void MessageBus::immediateMessage(const Message &newMessage) {
  for (auto eachSystem : systems) {
    eachSystem->processMessage(&newMessage);
  }
}