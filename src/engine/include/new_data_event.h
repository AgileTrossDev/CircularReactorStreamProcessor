#ifndef NEW_DATA_EVENT_H
#define NEW_DATA_EVENT_H

#include <iostream>
#include "reactor_events.h"
#include "reactor_event_handler.h"

template <typename T>
class NewDataEvent : public ReactorEventHandler {
  public:


    NewDataEvent(T& ingester) : data_ingester(ingester){};
    
    
     
    virtual void handle_event(const ReactorEvent& event) {
     
          //std::cout << "Not initialized" << std::endl;
          data_ingester.read();
    }

  private:
    T& data_ingester;
    

};


#endif

