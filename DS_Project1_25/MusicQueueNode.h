#pragma once
// #include "MusicQueue.h"
// #include <cstring>
// #include <sstream>
#include <string>

class MusicQueueNode {
   private:
    std::string artist;
    std::string title;
    std::string run_time;

    MusicQueueNode* next;
    MusicQueueNode* prev;

   public:
    MusicQueueNode() {
        this->artist = "";
        this->title = "";
        this->run_time = "";

        this->next = nullptr;
        this->prev = nullptr;
    }
    ~MusicQueueNode() {
    }
    // set the data
    void insert(std::string artist, std::string title, std::string runTime) {
        this->artist = artist;
        this->title = title;
        this->run_time = runTime;
    }
    void setNext(MusicQueueNode* next) {
        this->next = next;
    }
    void setPrev(MusicQueueNode* prev) {
        this->prev = prev;
    }

    // get the data
    std::string getArtist() {
        return this->artist;
    }
    std::string getTitle() {
        return this->title;
    }
    std::string getRunTime() {
        return this->run_time;
    }
    MusicQueueNode* getNext() {
        return this->next;
    }
    MusicQueueNode* getPrev() {
        return this->prev;
    }

    bool exist(std::string artist, std::string title) {
        if (this->artist == artist && this->title == title) {
            return true;
        }
        return false;
    }
};