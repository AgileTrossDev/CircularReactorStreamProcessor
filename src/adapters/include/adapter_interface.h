#ifndef ADAPTER_H
#define ADAPTER_H

#include <string>

// An abstract class representing the interface that all adapters must adhere too
class AdapterInterface {
    
public:

    // ------------------------------------------------------
    // Builder Functions
    // ------------------------------------------------------
    static AdapterInterface* build();
    

    // ------------------------------------------------------
    // Pure Virtual Interface
    // ------------------------------------------------------    
    virtual void read() = 0;          // Reads the next block of data        
    virtual void write() = 0;         // Writes a block of data to a destination
 
    /* Other members */


};


// Class used for builder classes of Adpaters implementing the Adapter Interface
//
// NOTE: The intention here is that each derived class creates a static instance
// of the Adapter Builder. So that when the class is loaded at run time, it 
// registered with the builder.
class AdapterBuilder {
  public:

    // ------------------------------------------------------
    // Static Functions
    // ------------------------------------------------------
    static void register_builder(std::string AdapterName);
    
    // ------------------------------------------------------
    // Constructor
    // ------------------------------------------------------
    AdapterBuilder(std::string adapter_name) {AdapterBuilder::register_builder(adapter_name);}    
    
  
};

#endif
