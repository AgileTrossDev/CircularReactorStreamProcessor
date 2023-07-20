#ifndef REACTOR_H
#define REACTOR_H

#include <map>

#include "reactor_events.h"
#include "reactor_event_handler.h"

class Reactor {
  public:
    Reactor():next_event_id(0) {};

    // Register an event handler for a specific event ID
    int register_handler(ReactorEventHandler* handler);

    // Remove an event handler for a specific event ID
    void remove_handler(int event_id);

    // Simulate event occurrence
    void fire_event(const ReactorEvent& event);

  private:
    std::map<int, ReactorEventHandler*> event_handlers;
    int next_event_id;
};

#endif