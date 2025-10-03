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
    // 여러개 추가 시 하나라도 겹치면 out
    // 겹치는 게 하나라도 있는 지 확인 하고 this->pl.insert_node()
    manager.MAKEPL("SONG", "Maroon 5", "sugar");
    manager.MAKEPL("ARTIST", "PSY", "");
    manager.PRINT("ARTIST");
    manager.PRINT("TITLE");
    manager.PRINT("LIST");

    return 0;
}