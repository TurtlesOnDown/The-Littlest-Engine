#include "MessageBus.h"
#include "System.h"

void MessageBus::addSystem(System *newSystem) {
  systems.push_back(newSystem);
}

void MessageBus::addMessage(Message &newMessage) {
  messages.push(newMessage);
}

void MessageBus::notfitySystems() {
  // For each message
  while (messages.size()) {
    const Message nextMessage = messages.front();
    // Send that message to each system
    for (auto eachSystem : systems) {
      eachSystem->processMessage(&nextMessage);
    }
    messages.pop();
  }
}

void MessageBus::immediateMessage(const Message &newMessage) {
  for (auto eachSystem : systems) {
    eachSystem->processMessage(&newMessage);
  }
}