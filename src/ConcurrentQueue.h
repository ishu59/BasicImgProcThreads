//
// Created by ishu on 4/4/20.
//

#ifndef IMAGEPROC_CONCURRENTQUEUE_H
#define IMAGEPROC_CONCURRENTQUEUE_H
#include <condition_variable>
#include <mutex>
#include <queue>

template <typename T> class ConcurrentQueue {
private:
  std::queue<T> myQue;
  mutable std::mutex mtx;
  std::condition_variable local_cond_var;

public:
  void push(T const &data) {
    std::unique_lock<std::mutex> lock(mtx);
    myQue.push(data);
    lock.unlock();
    local_cond_var.notify_one();
  }

  bool empty() const {
    std::lock_guard<std::mutex> lock(mtx);
    return myQue.empty();
  }

  bool try_pop(T &popped_value) {
    std::lock_guard<std::mutex> lock(mtx);
    if (myQue.empty()) {
      return false;
    }

    popped_value = myQue.front();
    myQue.pop();
    return true;
  }

  void wait_and_pop(T &popped_value) {
    std::unique_lock<std::mutex> lock(mtx);
    while (myQue.empty()) {
      local_cond_var.wait(lock);
    }
    popped_value = myQue.front();
    myQue.pop();
  }
};

#endif // IMAGEPROC_CONCURRENTQUEUE_H
