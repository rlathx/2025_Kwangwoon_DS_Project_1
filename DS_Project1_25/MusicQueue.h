#pragma once
#include <string>

#include "MusicQueueNode.h"

class MusicQueue {
   private:
    MusicQueueNode* head;
    MusicQueueNode* rear;
    int size = 0;

   public:
    MusicQueue();
    ~MusicQueue();

    bool empty();
    bool exist(std::string artist, std::string title);
    bool push(const std::string& artist, const std::string& title, const std::string& runTime);
    MusicQueueNode* pop();
    void print();
    MusicQueueNode* front();
};