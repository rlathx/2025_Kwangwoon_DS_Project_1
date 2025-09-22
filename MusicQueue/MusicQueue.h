#pragma once
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
    bool exist(string artist, string title);
    void push(string& target);
    MusicQueueNode* pop();
    MusicQueueNode* front();

    MusicQueueNode* split(const string& target);
};