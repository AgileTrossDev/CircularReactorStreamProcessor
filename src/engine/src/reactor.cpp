#include "reactor.h"

// Register an event handler for a specific event ID
int Reactor::register_handler(ReactorEventHandler* handler) {
    event_handlers[next_event_id] = handler;
    next_event_id++;
    return next_event_id;
}

// Remove an event handler for a specific event ID
void Reactor::remove_handler(int event_id) {
    event_handlers.erase(event_id);
}

// Executes an Event
void Reactor::fire_event(const ReactorEvent& event) {
    auto it = event_handlers.find(event.id);
    if (it != event_handlers.end()) {
        ReactorEventHandler* handler = it->second;
        handler->handle_event(event);
    }
}

