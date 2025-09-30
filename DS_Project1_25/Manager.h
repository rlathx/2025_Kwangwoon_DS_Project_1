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
    std::ifstream fcmd;
    std::ofstream flog;

    bool loadCheck = false;

   public:
    Manager();
    ~Manager();

    bool run(const char* command);

    void LOAD();
    void ADD();
    void QPOP();
    void SEARCH();
    void MAKEPL();
    void PRINT();
    void DELETE();
    void EXIT();
};