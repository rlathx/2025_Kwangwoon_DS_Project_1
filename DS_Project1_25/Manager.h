#pragma once
#include <fstream>

#include "ArtistBST.h"
#include "MusicQueue.h"
#include "PlayList.h"
#include "TitleBST.h"

// using namespace std;

class Manager {
   private:
    MusicQueue q;
    ArtistBST ab;
    TitleBST tb;
    PlayList pl;
    std::ifstream commandFile;
    std::ifstream fcmd;
    std::ofstream flog;

    bool loadCheck = false;

   public:
    Manager();
    ~Manager();

    void run();
    std::string split(const std::string& command);
    void LOAD();
    void ADD(std::string command);
    void QPOP();
    void SEARCH(std::string target, std::string targetArtist, std::string targetTitle);
    void MAKEPL(std::string target, std::string targetArtist, std::string targetTitle);
    void PRINT(std::string target);
    void DELETE(std::string target, std::string targetArtist, std::string targetTitle);
    void EXIT();
};