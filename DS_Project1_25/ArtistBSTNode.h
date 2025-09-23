#pragma once
#include <string>
#include <vector>

// #include "ArtistBST.h"
#include "MusicQueueNode.h"

class ArtistBSTNode {
   private:
    std::string artist;
    std::vector<std::string> title;
    std::vector<std::string> run_time;

    int sumOfRunTime;
    int count;

    ArtistBSTNode* left;
    ArtistBSTNode* right;

   public:
    ArtistBSTNode() {
        this->artist = "";
        this->sumOfRunTime = 0;
        this->count = 0;
        this->left = nullptr;
        this->right = nullptr;
    }
    ~ArtistBSTNode() {
    }
    // private set function
    void set(std::string artist, std::string title, std::string run_time) {
        this->artist = artist;
        this->title.push_back(title);
        this->run_time.push_back(run_time);

        this->sumOfRunTime += stringToIntRunTime(run_time);
        this->count++;
    }
    void setCount() {
        this->count--;
    }
    void setSumOfRunTime(int idx) {
        this->sumOfRunTime -= stringToIntRunTime(this->run_time[idx]);
    }
    void setLeft(ArtistBSTNode* left) {
        this->left = left;
    }
    void setRight(ArtistBSTNode* right) {
        this->right = right;
    }
    // private get funtion
    std::string& getArtist() {
        return this->artist;
    }
    std::vector<std::string>& getTitle() {
        return this->title;
    }
    std::vector<std::string>& getRunTime() {
        return this->run_time;
    }
    int getCount() {
        return this->count;
    }
    ArtistBSTNode* getLeft() {
        return this->left;
    }
    ArtistBSTNode* getRight() {
        return this->right;
    }

    int search(std::string title) {
        for (size_t i = 0; i < this->title.size(); i++) {
            if (this->title[i] == title) {
                return i;
            }
        }
        return -1;
    }

    int stringToIntRunTime(std::string run_time) {
        int separator = run_time.find(":");
        std::string min = run_time.substr(0, separator);
        std::string sec = run_time.substr(separator + 1);

        int totalSeconds = (std::stoi(min) * 60) + std::stoi(sec);

        return totalSeconds;
    }
};
