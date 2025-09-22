#pragma once
// #include "MusicQueue.h"
// #include <cstring>
// #include <sstream>
#include <string>

class MusicQueueNode {
   private:
    string artist;
    string title;
    string run_time;

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
    void insert(string artist, string title, string runTime) {
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
    string getArtist() {
        return this->artist;
    }
    string getTitle() {
        return this->title;
    }
    string getRunTime() {
        return this->run_time;
    }
    MusicQueueNode* getNext() {
        return this->next;
    }
    MusicQueueNode* getPrev() {
        return this->prev;
    }

    bool exist(string artist, string title) {
        if (this->artist == artist && this->title == title) {
            return true;
        }
        return false;
    }
};