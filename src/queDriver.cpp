//
// Created by ishu on 4/4/20.
//
#include "ConcurrentQueue.h"
#include <future>
#include <iostream>
#include <thread>
#include <vector>
ConcurrentQueue<int> que;
void addtoQueue(int data) {

  std::string s("Processing data: " + std::to_string(data) + '\n');
  std::cout << s;
  que.push(data);
}
int process() {
  int data = 0;
  que.wait_and_pop(data);
  std::this_thread::sleep_for(std::chrono::milliseconds(10));
  return data * data;
}
int main() {
  std::vector<int> vec;
  for (int i = 0; i < 100; i++) {
    vec.push_back(i);
  }
  std::thread input([&](){
    for (int i = 0; i < vec.size(); ++i) {
      std::this_thread::sleep_for(std::chrono::milliseconds(1));
      que.push(vec[i]);
      std::string s("Adding data: " + std::to_string(i) + '\n');
      std::cout << s;
    }
  });
  std::this_thread::sleep_for(std::chrono::milliseconds(1));
  std::thread proc([&](){
      while(true){
      int data = 0;
      std::this_thread::sleep_for(std::chrono::milliseconds(1));
      que.wait_and_pop(data);
      std::string s("Processing data: " + std::to_string(data*data) + '\n');
      std::cout << s;
      }
  });
  input.join();
  proc.join();

  return 0;
}