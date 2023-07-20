#include "reactor_pool.h"

using std::move;
using std::unique_lock;
using std::function;
using std::mutex;
using std::thread;

// Thread Pool Constructor 
ReactorPool::ReactorPool(int number_of_threads) : stop(false) {

  // Start-up the requested Work Threads and add them to the worker_threads collection
  for (int i = 0; i < number_of_threads; ++i) {
    worker_threads.emplace_back([this] { worker_execution_loop(); });
  }
}

void ReactorPool::worker_execution_loop() {
  while (true) {
        function<void()> task;
        
        {
          unique_lock<mutex> lock(queue_mutex);
          condition.wait(lock, [this] { return stop || !tasks.empty(); });

          // Exit function if we are told to stop, and the tasks are empty
          if (stop && tasks.empty()) { return; }
          
          // Pop the new task
          task = move(tasks.front());
          tasks.pop();
        }
        
        // Execute the next Task
        task();
      }


}

// Desctructor, tells Threads executing loop to stop
ReactorPool::~ReactorPool() {
  {
    unique_lock<mutex> lock(queue_mutex);
    stop = true;
  }
  
  // Notify all Works to wake up
  condition.notify_all();
  
  // Allow all threads to complete their final task
  for (thread& worker : worker_threads) {
    worker.join();
  }
}

// Colletion of Tasks/functions to be worked
template<typename F, typename... Args>
void ReactorPool::enqueue(F&& func, Args&&... args) {
  {
    unique_lock<mutex> lock(queue_mutex);
    tasks.emplace([func, args...] { func(args...); });
  }
  
  condition.notify_one();
}
    
