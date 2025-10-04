#pragma once
#include <string>
#include <vector>

// #include "MusicQueueNode.h"

class TitleBSTNode {
   private:
    std::string title;
    std::vector<std::string> artist;
    std::vector<std::string> run_time;

    int sumOfRunTime;
    int count;

    TitleBSTNode* left;
    TitleBSTNode* right;

   public:
    TitleBSTNode() {
        this->title = "";
        this->sumOfRunTime = 0;
        this->count = 0;
        this->left = nullptr;
        this->right = nullptr;
    }
    ~TitleBSTNode() {
    }
    // private set function
    void set(std::string artist, std::string title, std::string run_time) {
        this->title = title;
        this->artist.push_back(artist);
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
    void setLeft(TitleBSTNode* left) {
        this->left = left;
    }
    void setRight(TitleBSTNode* right) {
        this->right = right;
    }
    // private get funtion
    std::string& getTitle() {
        return this->title;
    }
    std::vector<std::string>& getArtist() {
        return this->artist;
    }
    std::vector<std::string>& getRunTime() {
        return this->run_time;
    }
    int getCount() {
        return this->count;
    }
    TitleBSTNode* getLeft() {
        return this->left;
    }
    TitleBSTNode* getRight() {
        return this->right;
    }

    int search(std::string artist) {
        for (size_t i = 0; i < this->artist.size(); i++) {
            if (this->artist[i] == artist) {
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

    TitleBSTNode*& leftLink() {
        return left;
    }
    TitleBSTNode*& rightLink() {
        return right;
    }
};
