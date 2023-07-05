#include <iostream>

#include "adapter_interface.h"

using namespace std;

AdapterInterface* AdapterInterface::build() {

  return 0;


}
void AdapterBuilder::register_builder(string adapter_name) {
  cout <<"Registering: " << adapter_name << endl;
}

