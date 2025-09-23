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
    void push(MusicQueueNode* newNode);
    MusicQueueNode* pop();
    MusicQueueNode* front();
};