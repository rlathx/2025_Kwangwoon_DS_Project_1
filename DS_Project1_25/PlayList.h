#pragma once
#include <string>

#include "PlayListNode.h"

class PlayList {
   private:
    PlayListNode* head;
    PlayListNode* cursor;
    int count;
    int time;
    std::string data;

   public:
    PlayList();
    ~PlayList();

    int getCount();
    bool insert_node(std::string artist, std::string title, std::string runTime);
    bool delete_node(std::string artist, std::string title);
    bool empty();
    bool full();
    bool exist(std::string artist, std::string title);
    bool print();
    int run_time(std::string runTime);
};