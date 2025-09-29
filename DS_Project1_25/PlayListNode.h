#pragma once
#include <string>

// #include "PlayList.h"

class PlayListNode {
   private:
    std::string artist;
    std::string title;
    std::string run_time;

    PlayListNode* prev;
    PlayListNode* next;

   public:
    PlayListNode() {
        this->artist = "";
        this->title = "";
        this->run_time = "";

        this->prev = nullptr;
        this->next = nullptr;
    }
    ~PlayListNode() {
    }

    void set(std::string artist, std::string title, std::string run_time) {
        this->artist = artist;
        this->title = title;
        this->run_time = run_time;
    }
    void setPrev(PlayListNode* prev) {
        this->prev = prev;
    }
    void setNext(PlayListNode* next) {
        this->next = next;
    }

    std::string getArtist() {
        return this->artist;
    }
    std::string getTitle() {
        return this->title;
    }
    std::string getRunTime() {
        return this->run_time;
    }
    PlayListNode* getNext() {
        return this->next;
    }
    PlayListNode* getPrev() {
        return this->prev;
    }
};