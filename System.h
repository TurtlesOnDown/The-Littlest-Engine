#include "MessageBus.h"

#ifndef SYSTEM
#define SYSTEM

class System {
public:
  System(MessageBus *mainMessage) :s_MessageBus(mainMessage) { s_MessageBus->addSystem((System *)this); };
  virtual void processMessage(const Message *) = 0;

protected:
  MessageBus *s_MessageBus;
};


#endif // !SYSTEM