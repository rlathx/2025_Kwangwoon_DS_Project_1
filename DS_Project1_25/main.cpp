#include <iostream>

#include "Manager.h"
using namespace std;

int main() {
    Manager manager;

    // manager.run();
    manager.LOAD();
    manager.ADD("KDA|pop stars|3:23");
    manager.ADD("N.Flying|songbird|3:46");
    manager.QPOP();
    manager.SEARCH("ARTIST", "N.Flying", "");
    manager.SEARCH("TITLE", "", "blue moon");
    manager.SEARCH("TITLE", "", "my love");
    manager.SEARCH("SONG", "N.Flying", "blue moon");
    manager.MAKEPL("ARTIST", "N.Flying", "");
    manager.MAKEPL("TITLE", "", "blue moon");
    manager.MAKEPL("TITLE", "", "my love");
    manager.MAKEPL("SONG", "Maroon 5", "sugar");
    manager.MAKEPL("ARTIST", "PSY", "");
    manager.PRINT("ARTIST");
    manager.PRINT("TITLE");
    manager.PRINT("LIST");

    manager.DELETE("ARTIST", "PSY", "");
    cout << "1\n";
    // manager.DELETE("ARTIST", "PSY", "");
    // cout << "2\n";
    // manager.DELETE("TITLE", "", "blue moon");
    // cout << "3\n";
    // manager.DELETE("TITLE", "", "blue moon");
    // cout << "4\n";
    // manager.DELETE("LIST", "N.Flying", "songbird");
    // cout << "5 ok\n";
    // manager.DELETE("LIST", "N.Flying", "songbird");
    // cout << "6 ok\n";
    // manager.DELETE("SONG", "N.Flying", "rooftop");
    // cout << "7\n";
    // manager.DELETE("SONG", "N.Flying", "rooftop");
    // cout << "8\n";

    // manager.PRINT("ARTIST");

    // manager.DELETE("SONG", "N.Flying", "songbird");

    // manager.PRINT("ARTIST");
    // manager.PRINT("TITLE");
    // manager.PRINT("LIST");

    return 0;
}