#ifndef REACTOR_EVENT_HANDLER_H
#define REACTOR_EVENT_HANDLER_H


#include "reactor_events.h"


// Event handler interface for State within the Reactor
class ReactorEventHandler {
  public:
  
    virtual void handle_event(const ReactorEvent& event) = 0;
};

#endif