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
    void push(std::string& target);
    MusicQueueNode* pop();
    MusicQueueNode* front();

    MusicQueueNode* split(const std::string& target);
};