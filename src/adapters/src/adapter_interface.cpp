#include <iostream>

#include "adapter_interface.h"

using namespace std;

AdapterInterface* AdapterInterface::build() {
  return 0;
}

// Thread safe function to change the value of active.
void AdapterInterface::set_active(bool new_state) {
  
  lock_guard<mutex> lock(attribute_mutex); // Obtains the mutex lock for life of function
  active = new_state;
}

void AdapterInterface::start() {

  execution_thread = thread(&AdapterInterface::execute, this);
  set_active(true);
}


void AdapterInterface::execute() {

  set_active(true);
  open();

  while (active) {


  }



}