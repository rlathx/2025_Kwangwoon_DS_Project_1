#include "Manager.h"

#include <cstring>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

Manager::Manager() {
    this->commandFile.open("command.txt");
    this->fcmd.open("Music_List.txt");
    this->loadCheck = false;
}

Manager::~Manager() {
}

void Manager::run() {
    if (!this->commandFile.is_open()) {
        cout << "파일 없음";
        return;
    }

    string line;
    while (getline(this->commandFile, line)) {
        if (line == "LOAD") {
            LOAD();
        } else if (line == "QPOP") {
            QPOP();
        } else if (line == "EXIT") {
            EXIT();
        }

        const size_t p1 = line.find(' ');
        if (p1 == string::npos) {
            cout << "입력 규격 안 맞음";
            continue;
        }
        const string command = line.substr(0, p1);

        if (command == "ADD") {
            if (split(line.substr(p1 + 1))) {
                cout << "error\n";
                continue;
            }
        } else if (command == "SEARCH") {
            const size_t p2 = line.find(' ', p1 + 1);
            if (p2 == string::npos) {
                cout << "입력 규격 안 맞음";
                continue;
            }
            const string target = line.substr(p1 + 1, p2 - (p1 + 1));

            const string targetArtist;
            const string targetTitle;

            const size_t p3 = command.find('|', p2 + 1);
            if ((p3 == string::npos) && target == "ARTIST") {
                targetArtist = line.substr(p2 + 1);
                targetTitle = "";
            } else if ((p3 == string::npos) && target == "TITLE") {
                targetArtist = "";
                targetTitle = line.substr(p2 + 1);
            } else if ((p3 == string::npos) && target == "SONG") {
                targetArtist = line.substr(p2 + 1, p3 - (p2 + 1));
                targetTitle = line.substr(p3 + 1);
            }

            SEARCH(target, targetArtist, targetTitle);

        } else if (command == "MAKEPL") {
            const size_t p2 = line.find(' ', p1 + 1);
            if (p2 == string::npos) {
                cout << "입력 규격 안 맞음";
                continue;
            }
            const string target = line.substr(p1 + 1, p2 - (p1 + 1));

            const string targetArtist;
            const string targetTitle;

            const size_t p3 = command.find('|', p2 + 1);
            if ((p3 == string::npos) && target == "ARTIST") {
                targetArtist = line.substr(p2 + 1);
                ArtistBSTNode* artistNode = this->ab.search(targetArtist);
                if (artistNode == nullptr) {
                    cout << "error\n";
                    continue;
                }
                if (artistNode->getCount() > (10 - this->pl.getCount())) {
                    cout << "error\n";
                    continue;
                }

                for (int i = 0; i < artistNode->getCount(); i++) {
                    if (this->pl.insert_node(targetArtist, artistNode->getTitle()[i],
                                             artistNode->getRunTime()[i]) == false) {
                        cout << "error\n";
                        continue;
                    }
                }
            } else if ((p3 == string::npos) && target == "TITLE") {
                targetTitle = line.substr(p2 + 1);
                TitleBSTNode* titleNode = this->tb.search(targetTitle);
                if (titleNode == nullptr) {
                    cout << "error\n";
                    continue;
                }
                if (titleNode->getCount() > (10 - this->pl.getCount())) {
                    cout << "error\n";
                    continue;
                }

                for (int i = 0; i < titleNode->getCount(); i++) {
                    if (this->pl.insert_node(titleNode->getArtist()[i], targetTitle,
                                             titleNode->getRunTime()[i]) == false) {
                        cout << "error\n";
                        continue;
                    }
                }
            } else if ((p3 != string::npos) && (target == "SONG")) {
                string targetArtist = line.substr(p2 + 1, p3 - (p2 + 1));
                string targetTitle = line.substr(p3 + 1);

                if (this->pl.full() == true) {
                    cout << "error\n";
                    continue;
                }

                ArtistBSTNode* targetNode = this->ab.search(targetArtist);

                if (targetNode == nullptr) {
                    cout << "error\n";
                    continue;
                }

                for (int i = 0; i < targetNode->getCount(); i++) {
                    if (targetNode->getTitle()[i] == targetTitle) {
                        if (this->pl.insert_node(targetArtist, targetTitle,
                                                 targetNode->getRunTime()[i])) {
                            cout << "error\n";
                            continue;
                        }
                        continue;
                    }
                }
                cout << "error\n";
                continue;
            } else if ((p3 == string::npos) && (target == "SONG")) {
                cout << "error\n";
                continue;
            }

        } else if (command == "PRINT") {
            const string target = line.substr(p1 + 1);

            PRINT(target);
        } else if (command == "DELETE") {
            const size_t p2 = line.find(' ', p1 + 1);
            if (p2 == string::npos) {
                cout << "입력 규격 안 맞음";
                continue;
            }
            const string target = line.substr(p1 + 1, p2 - (p1 + 1));

            const string targetArtist;
            const string targetTitle;

            const size_t p3 = command.find('|', p2 + 1);
            if ((p3 == string::npos) && target == "ARTIST") {
                targetArtist = line.substr(p2 + 1);
                targetTitle = "";
            } else if ((p3 == string::npos) && target == "TITLE") {
                targetArtist = "";
                targetTitle = line.substr(p2 + 1);
            } else if ((p3 != string::npos) && ((target == "SONG") || (target == "LIST"))) {
                targetArtist = line.substr(p2 + 1, p3 - (p2 + 1));
                targetTitle = line.substr(p3 + 1);
            } else if ((p3 == string::npos) && ((target == "SONG") || (target == "LIST"))) {
                cout << "error\n";
                continue;
            }

            DELETE(target, targetArtist, targetTitle);
        }
    }
}
// load add
bool Manager::split(const string& command) {
    // 1) 구분자 찾기 (안전)
    const size_t p1 = command.find('|');
    if (p1 == string::npos) {
        std::cout << "입력 규격 안 맞음";
        return false;
    }

    const size_t p2 = command.find('|', p1 + 1);
    if (p2 == string::npos) {
        std::cout << "입력 규격 안 맞음";
        return false;
    }

    // 2) 필드 분리
    const string artist = command.substr(0, p1);
    const string title = command.substr(p1 + 1, p2 - (p1 + 1));
    const string runTime = command.substr(p2 + 1);

    if (artist.empty() || title.empty() || runTime.empty()) {
        std::cout << "입력 규격 안 맞음";
        return false;
    }

    // 3) runTime 형식 검사: m:ss 또는 mm:ss
    const size_t L = runTime.size();
    auto isDigit = [](char c) { return c >= '0' && c <= '9'; };

    bool ok = false;
    if (L == 4) {  // m:ss
        ok = (isDigit(runTime[0]) && runTime[1] == ':' && isDigit(runTime[2]) &&
              isDigit(runTime[3]));
    } else if (L == 5) {  // mm:ss
        ok = (isDigit(runTime[0]) && isDigit(runTime[1]) && runTime[2] == ':' &&
              isDigit(runTime[3]) && isDigit(runTime[4]));
    }
    if (!ok) {
        cout << "입력 규격 안 맞음";
        return false;
    }

    // 4) 큐에 추가 (아래 2번 설명처럼 '큐 내부에서' 노드 생성/소유)
    const bool pushed = q.push(artist, title, runTime);
    if (!pushed) {
        // error는 push가 false로 알려주도록
        cout << "추가 실패";
        return false;
    }

    cout << artist << '/' << title << '/' << runTime << '\n';

    return true;
}

void Manager::LOAD() {
    if (this->loadCheck == true) {
        cout << "이제 해당 명령어 사용 불가";
        return;
    }
    if (!this->fcmd.is_open()) {
        cout << "파일 없음";
        return;
    }

    string line;
    while (getline(this->fcmd, line)) {
        if (split(line) == false) {
            cout << "error\n";
            return;
        }
    }

    loadCheck = true;
}

void Manager::ADD(string command) {
    // txt랑 중복 확인
    string line;
    while (getline(this->fcmd, line)) {
        if (line == command) {
            cout << "txt랑 중복\n";
            return;
        }
    }

    split(command);
}

void Manager::QPOP() {
    MusicQueueNode* node = this->q.pop();

    // if(queue->pop() == nullptr) {에러코드 출력; return;}
    if (node == nullptr) {
        cout << "empty\n";
        return;
    }

    // 이미 artist bst에 있는 곡 : BST - insert 에서 에러 코드 출력
    if (this->ab.insert(node->getArtist(), node->getTitle(), node->getRunTime()) == false) {
        cout << "error\n";
        return;
    }

    // 이미 title bst에 있는 곡 : BST - insert 에서 에러 코드 출력
    if (this->tb.insert(node->getArtist(), node->getTitle(), node->getRunTime()) == false) {
        cout << "error\n";
        return;
    }

    cout << "success\n";
    return;
}

void Manager::SEARCH(string target, string targetArtist, string targetTitle) {
    if (target == "ARTIST") {
        if (this->ab.search() == nullptr) {
            cout << "error\n";
            return;
        }

        for (int i = 0; i < curNode->getCount(); i++) {
            cout << curNode->getArtist() << '/' << curNode->getTitle()[i] << '/'
                 << curNode->getRunTime()[i] << '\n';
        }
    }
    if (target == "TITLE") {
        if (this->tb.search() == nullptr) {
            cout << "error\n";
            return;
        }

        for (int i = 0; i < curNode->getCount(); i++) {
            cout << curNode->getArtist() << '/' << curNode->getTitle()[i] << '/'
                 << curNode->getRunTime()[i] << '\n';
        }
    }
    if (target == "LIST") {
        if (this->pl.search() == nullptr) {
            cout << "error\n";
            return;
        }

        for (int i = 0; i < curNode->getCount(); i++) {
            if (curNode->getTitle()[i] == targetTitle) {
                cout << curNode->getArtist() << '/' << curNode->getTitle()[i] << '/'
                     << curNode->getRunTime()[i] << '\n';

                return;
            }
        }

        cout << "error\n";
        return;
    }
}
// pl insert
void Manager::MAKEPL(string target, string targetArtist, string targetTitle) {
    if (target == "ARTIST") {
        ArtistBSTNode* artistTemp = this->ab.search();

        if (artistTemp == false) {
            cout << "error\n";
            return;
        }

        for (int i = 0; i < artistTemp->getCount(); i++) {
            if (this->pl.insert_node(artistTemp->getArtist(), artistTemp->getTitle()[i],
                                     artistTemp->getRunTime()[i]) == false) {
                cout << "error\n";
                return;
            }
        }
    }
    if (target == "TITLE") {
        ArtistBSTNode* titleTemp = this->tb.search();

        if (titleTemp == false) {
            cout << "error\n";
            return;
        }

        for (int i = 0; i < titleTemp->getCount(); i++) {
            if (this->pl.insert_node(titleTemp->getArtist()[i], titleTemp->getTitle(),
                                     titleTemp->getRunTime()[i]) == false) {
                cout << "error\n";
                return;
            }
        }
    }
    if (target == "SONG") {
        ArtistBSTNode* artistTemp = this->ab.search();

        if (artistTemp == false) {
            cout << "error\n";
            return;
        }

        for (int i = 0; i < artistTemp->getCount(); i++) {
            if (artistTemp->getTitle()[i] == targetTitle) {
                this->pl.insert_node(targetArtist, targetTitle, artistTemp->getRunTime()[i]);
                return;
            }
        }
        cout << "error\n";
        return;
    }
}
// print
void Manager::PRINT(string target) {
    if (target == "ARTIST") {
        if (this->ab.print() == false) {
            cout << "error\n";
            return;
        }
    }
    if (target == "TITLE") {
        if (this->tb.print() == false) {
            cout << "error\n";
            return;
        }
    }
    if (target == "LIST") {
        if (this->pl.print() == false) {
            cout << "error\n";
            return;
        }
    }
}
// bst delete_node search
void Manager::DELETE(string target, string targetArtist, string targetTitle) {
    if (target == "ARTIST") {
        ArtistBSTNode* targetNode = this->ab.search(targetArtist);

        if (targetNode == nullptr) {
            cout << "no target\n";
            return;
        }

        for (int i = 0; i < targetNode->getCount(); i++) {
            if (this->tb.delete_node(targetArtist, targetNode->getTitle()[i]) == false) {
                cout << "error\n";
                return;
            }
            if (this->pl.delete_node(targetArtist, targetNode->getTitle()[i]) == false) {
                cout << "error\n";
                return;
            }
        }

        if (this->ab.delete_node(targetArtist, targetTitle) == false) {
            cout << "error\n";
            return;
        }

        return;
    }
    if (target == "TITLE") {
        TitleBSTNode* targetNode = this->tb.search(targetTitle);

        if (targetNode == nullptr) {
            cout << "no target\n";
            return;
        }

        for (int i = 0; i < targetNode->getCount(); i++) {
            if (this->tb.delete_node(targetNode->getArtist()[i], targetTitle) == false) {
                cout << "error\n";
                return;
            }
            if (this->pl.delete_node(targetNode->getArtist()[i], targetTitle) == false) {
                cout << "error\n";
                return;
            }
        }
        if (this->tb.delete_node(targetArtist, targetTitle) == false) {
            cout << "error\n";
            return;
        }

        return;
    }
    if (target == "LIST") {
        if (this->pl.delete_node(targetArtist, targetTitle) == false) {
            cout << "error\n";
        }
        return;
    }
    if (target == "SONG") {
        if (this->ab.delete_node(targetArtist, targetTitle) == false) {
            cout << "error\n";
            return;
        }
        if (this->tb.delete_node(targetArtist, targetTitle) == false) {
            cout << "error\n";
            return;
        }
        if (this->pl.delete_node(targetArtist, targetTitle) == false) {
            cout << "error\n";
            return;
        }

        return;
    }
}

void Manager::EXIT() {
}

// +a

// Enter data into each variable based on '/'
// '' : char
// "" : const char*, string (end letter == null)

// If any of the following fields are missing: singer name, song title, or playing time, nullptr is
// returned.