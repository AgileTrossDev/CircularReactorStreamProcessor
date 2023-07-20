#ifndef REACTOR_EVENTS_H
#define REACTOR_EVENTS_H

#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <pthread.h>

class ReactorPool {
  public:

    // Constuctors
    ReactorPool(int number_of_threads);     
    ~ReactorPool();
    
    // Queue for Tasks
    template<typename F, typename... Args>
    void enqueue(F&& func, Args&&... args);
    
private:


  void worker_execution_loop();


  // Collection of workers in the pool
  std::vector<std::thread> worker_threads;

  // Colletion of Tasks/functions to be worked
  std::queue<std::function<void()>> tasks;

  // Worker management
  std::mutex queue_mutex;
  std::condition_variable condition; 
  bool stop;
};

#endif