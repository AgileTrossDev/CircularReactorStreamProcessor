#ifndef ADAPTER_H
#define ADAPTER_H

#include <string>
#include <map>
#include <mutex>
#include <thread>
#include <pthread.h>


#include "types.h"

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
    virtual void open() = 0;          // Opens up the data and makes it active
 
    // ------------------------------------------------------    
    // Functions
    // ------------------------------------------------------    
    void start();
    void stop();

  protected:
    AdapterInterface():active(false) {}

    void set_active(bool new_state);

  private:  

    std::mutex attribute_mutex; // Mutex for thread safety
    bool active;
    std::thread execution_thread;
 
    void execute();

};




#endif
