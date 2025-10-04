#include "Manager.h"

// #include <cstring>
// #include <fstream>
#include <iostream>
#include <string>
#include <vector>

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
        return;
    }

    string line;

    if (!getline(this->commandFile, line)) {
        return;
    }

    this->commandFile.close();
    this->commandFile.open("command.txt");

    while (getline(this->commandFile, line)) {
        while (!line.empty() && (line.back() == '\r' || line.back() == '\n' || line.back() == ' ' ||
                                 line.back() == '\t')) {
            line.pop_back();
        }
        if (line == "LOAD") {
            LOAD();
        } else if (line == "QPOP") {
            QPOP();
        } else if (line == "EXIT") {
            EXIT();
        }

        const size_t p1 = line.find(' ');
        if (p1 == string::npos) {
            cout << "========ERROR========\n"
                 << "1000\n"
                 << "====================\n"
                 << ": 잘못된 명령어\n\n";
            continue;
        }
        const string command = line.substr(0, p1);

        if (command == "ADD") {
            if (split(line.substr(p1 + 1)) == "") {
                cout << "========ERROR========\n"
                     << "1000\n"
                     << "====================\n"
                     << ": 잘못된 명령어\n\n";
                continue;
            }
        } else if (command == "SEARCH") {
            const size_t p2 = line.find(' ', p1 + 1);
            if (p2 == string::npos) {
                cout << "========ERROR========\n"
                     << "1000\n"
                     << "====================\n"
                     << ": 잘못된 명령어\n\n";
                continue;
            }
            const string target = line.substr(p1 + 1, p2 - (p1 + 1));

            string targetArtist;
            string targetTitle;

            const size_t p3 = command.find('|', p2 + 1);
            if ((p3 == string::npos) && (target == "ARTIST")) {
                targetArtist = line.substr(p2 + 1);
                targetTitle = "";
            } else if ((p3 == string::npos) && (target == "TITLE")) {
                targetArtist = "";
                targetTitle = line.substr(p2 + 1);
            } else if ((p3 == string::npos) && (target == "SONG")) {
                targetArtist = line.substr(p2 + 1, p3 - (p2 + 1));
                targetTitle = line.substr(p3 + 1);
            }

            SEARCH(target, targetArtist, targetTitle);

        } else if (command == "MAKEPL") {
            const size_t p2 = line.find(' ', p1 + 1);
            if (p2 == string::npos) {
                cout << "========ERROR========\n"
                     << "1000\n"
                     << "====================\n"
                     << ": 잘못된 명령어\n\n";
                continue;
            }
            const string target = line.substr(p1 + 1, p2 - (p1 + 1));

            string targetArtist;
            string targetTitle;

            const size_t p3 = command.find('|', p2 + 1);
            if ((p3 == string::npos) && target == "ARTIST") {
                targetArtist = line.substr(p2 + 1);
                ArtistBSTNode*& artistNode = this->ab.search(targetArtist);
                if (artistNode == nullptr) {
                    cout << "========ERROR========\n"
                         << "500\n"
                         << "====================\n"
                         << ": 지정 곡이 존재하지 않음\n\n";
                    continue;
                }
                if (artistNode->getCount() > (10 - this->pl.getCount())) {
                    cout << "========ERROR========\n"
                         << "500\n"
                         << "====================\n"
                         << ": Play List 공간 부족\n\n";
                    continue;
                }

                for (int i = 0; i < artistNode->getCount(); i++) {
                    bool plInsertCheckFlag = this->pl.insert_node(
                        targetArtist, artistNode->getTitle()[i], artistNode->getRunTime()[i]);

                    if (plInsertCheckFlag == false) {
                        // insert에서 발생하는 error는 PlayList.cpp - insert_node에서 출력
                        continue;
                    }
                }
            } else if ((p3 == string::npos) && target == "TITLE") {
                targetTitle = line.substr(p2 + 1);
                TitleBSTNode*& titleNode = this->tb.search(targetTitle);
                if (titleNode == nullptr) {
                    cout << "========ERROR========\n"
                         << "500\n"
                         << "====================\n"
                         << ": 지정 곡이 존재하지 않음\n\n";
                    continue;
                }
                if (titleNode->getCount() > (10 - this->pl.getCount())) {
                    cout << "========ERROR========\n"
                         << "500\n"
                         << "====================\n"
                         << ": Play List 공간 부족\n\n";
                    continue;
                }

                for (int i = 0; i < titleNode->getCount(); i++) {
                    bool plInsertCheckFlag = this->pl.insert_node(
                        titleNode->getArtist()[i], targetTitle, titleNode->getRunTime()[i]);

                    if (plInsertCheckFlag == false) {
                        // insert에서 발생하는 error는 PlayList.cpp - insert_node에서 출력
                        continue;
                    }
                }
            } else if ((p3 != string::npos) && (target == "SONG")) {
                string targetArtist = line.substr(p2 + 1, p3 - (p2 + 1));
                string targetTitle = line.substr(p3 + 1);

                if (this->pl.full() == true) {
                    cout << "========ERROR========\n"
                         << "500\n"
                         << "====================\n"
                         << ": Play List 공간 부족\n\n";
                    continue;
                }

                ArtistBSTNode*& targetNode = this->ab.search(targetArtist);

                if (targetNode == nullptr) {
                    cout << "========ERROR========\n"
                         << "500\n"
                         << "====================\n"
                         << ": 지정 곡이 존재하지 않음\n\n";
                    continue;
                }

                for (int i = 0; i < targetNode->getCount(); i++) {
                    if (targetNode->getTitle()[i] == targetTitle) {
                        bool plInsertCheckFlag = this->pl.insert_node(targetArtist, targetTitle,
                                                                      targetNode->getRunTime()[i]);
                        if (plInsertCheckFlag == false) {
                            // insert에서 발생하는 error는 PlayList.cpp - insert_node에서 출력
                            continue;
                        }
                        continue;
                    }
                }
                cout << "========ERROR========\n"
                     << "500\n"
                     << "====================\n"
                     << ": 지정 곡이 존재하지 않음\n\n";
                continue;
            } else if ((p3 == string::npos) && (target == "SONG")) {
                cout << "========ERROR========\n"
                     << "1000\n"
                     << "====================\n"
                     << ": 잘못된 명령어\n\n";
                continue;
            }

        } else if (command == "PRINT") {
            const string target = line.substr(p1 + 1);

            PRINT(target);
        } else if (command == "DELETE") {
            const size_t p2 = line.find(' ', p1 + 1);
            if (p2 == string::npos) {
                cout << "========ERROR========\n"
                     << "1000\n"
                     << "====================\n"
                     << ": 잘못된 명령어\n\n";
                continue;
            }
            const string target = line.substr(p1 + 1, p2 - (p1 + 1));

            string targetArtist;
            string targetTitle;

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
                cout << "========ERROR========\n"
                     << "1000\n"
                     << "====================\n"
                     << ": 잘못된 명령어\n\n";
                continue;
            }

            DELETE(target, targetArtist, targetTitle);
        } else {
            cout << "========ERROR========\n"
                 << "1000\n"
                 << "====================\n"
                 << ": 잘못된 명령어\n\n";
            continue;
        }
    }
}
// load add
string Manager::split(const string& command) {
    // 1) 구분자 찾기 (안전)
    const size_t p1 = command.find('|');
    if (p1 == string::npos) {
        cout << "========ERROR========\n"
             << "1000\n"
             << "====================\n"
             << ": 잘못된 명령어\n\n";
        return "";
    }

    const size_t p2 = command.find('|', p1 + 1);
    if (p2 == string::npos) {
        cout << "========ERROR========\n"
             << "1000\n"
             << "====================\n"
             << ": 잘못된 명령어\n\n";
        return "";
    }

    // 2) 필드 분리
    const string artist = command.substr(0, p1);
    const string title = command.substr(p1 + 1, p2 - (p1 + 1));
    string runTime = command.substr(p2 + 1);
    if (!runTime.empty() && runTime.back() == '\n') runTime.pop_back();
    if (!runTime.empty() && runTime.back() == '\r') runTime.pop_back();

    if (artist.empty() || title.empty() || runTime.empty()) {
        cout << "========ERROR========\n"
             << "1000\n"
             << "====================\n"
             << ": 잘못된 명령어\n\n";
        return "";
    }

    // 3) runTime 형식 검사: m:ss 또는 mm:ss (초는 00~59)
    {
        // 끝의 CR/LF/공백 방어 제거
        while (!runTime.empty() && (runTime.back() == '\r' || runTime.back() == '\n' ||
                                    runTime.back() == ' ' || runTime.back() == '\t')) {
            runTime.pop_back();
        }

        auto isAllDigits = [](const std::string& s) -> bool {
            if (s.empty()) return false;
            for (char ch : s) {
                if (ch < '0' || ch > '9') return false;
            }
            return true;
        };

        bool ok = false;
        const size_t colon = runTime.find(':');
        if (colon != std::string::npos) {
            std::string mm = runTime.substr(0, colon);   // 분
            std::string ss = runTime.substr(colon + 1);  // 초

            // 분: 1~2자리 숫자, 초: 정확히 2자리 숫자, 초는 00~59
            if ((mm.size() == 1 || mm.size() == 2) && ss.size() == 2 && isAllDigits(mm) &&
                isAllDigits(ss)) {
                int sec = (ss[0] - '0') * 10 + (ss[1] - '0');
                ok = (sec >= 0 && sec <= 59);
            }
        }

        if (!ok) {
            cout << "========ERROR========\n"
                 << "1000\n"
                 << "====================\n"
                 << ": 잘못된 명령어\n\n";
            return "";
        }
    }

    // 4) 큐에 추가 (아래 2번 설명처럼 '큐 내부에서' 노드 생성/소유)
    const bool existed = this->q.exist(artist, title);
    if (existed) {
        cout << "========ERROR========\n"
             << "200\n"
             << "====================\n"
             << ": 이미 Queue에 존재하는 곡을 추가한 상태\n\n";
        return "";
    }
    const bool pushed = this->q.push(artist, title, runTime);
    if (!pushed) {
        return "";
    }

    string result;
    result += artist;
    result += '/';
    result += title;
    result += '/';
    result += runTime;

    return result;
}

void Manager::LOAD() {
    if (this->loadCheck == true) {
        cout << "========ERROR========\n"
             << "100\n"
             << "====================\n"
             << ": 이미 해당 명령어 사용 완료\n\n";
        return;
    }
    if (!this->fcmd.is_open()) {
        cout << "========ERROR========\n"
             << "100\n"
             << "====================\n"
             << ": Music_List.txt 없음\n\n";
        return;
    }

    string line;

    if (!getline(this->fcmd, line)) {
        cout << "========ERROR========\n"
             << "100\n"
             << "====================\n"
             << ": Music_List.txt 내에 데이터 없음\n\n";
        return;
    }

    this->fcmd.close();
    this->fcmd.open("Music_List.txt");

    while (getline(this->fcmd, line)) {
        if (!line.empty() && line.back() == '\n') line.pop_back();
        if (!line.empty() && line.back() == '\r') line.pop_back();
        if (split(line) == "") {
            return;
        }
    }

    cout << "========LOAD========\n";
    this->q.print();
    cout << "====================\n" << ": 데이터 로드를 성공함\n\n";

    loadCheck = true;
}

void Manager::ADD(string command) {
    string result = split(command);

    if (result == "") {
        return;
    }

    cout << "========ADD========\n"
         << result << "\n"
         << "====================\n"
         << ": 새로운 데이터를 추가한 상태\n\n";

    return;
}

void Manager::QPOP() {
    bool flag = false;

    while (true) {
        MusicQueueNode* node = this->q.pop();

        if (node == nullptr) break;

        string artist = node->getArtist();
        string title = node->getTitle();
        string runTime = node->getRunTime();

        delete node;

        // 이미 artist bst에 있는 곡 : BST - insert 에서 에러 코드 출력
        if (this->ab.insert(artist, title, runTime) == false) {
            cout << "========ERROR========\n"
                 << "300\n"
                 << "====================\n"
                 << ": BST에 겹치는 곡 있음\n\n";
            return;
        }

        // 이미 title bst에 있는 곡 : BST - insert 에서 에러 코드 출력
        if (this->tb.insert(artist, title, runTime) == false) {
            cout << "========ERROR========\n"
                 << "300\n"
                 << "====================\n"
                 << ": BST에 겹치는 곡 있음\n\n";
            return;
        }

        flag = true;
    }

    if (flag) {
        cout << "========QPOP========\n"
             << "Success\n"
             << "====================\n"
             << ": QPOP 명령어를 성공하여 BST 구조 형성 성공\n\n";
        return;
    }
    cout << "========ERROR========\n"
         << "300\n"
         << "====================\n"
         << ": pop할 곡 없음\n\n";
    return;
}

void Manager::SEARCH(string target, string targetArtist, string targetTitle) {
    if (target == "ARTIST") {
        ArtistBSTNode*& targetNode = this->ab.search(targetArtist);
        if (targetNode == nullptr) {
            cout << "========ERROR========\n"
                 << "400\n"
                 << "====================\n"
                 << ": ArtistBST에 해당 곡 없음\n\n";
            return;
        }

        cout << "========SEARCH========\n";
        for (int i = 0; i < targetNode->getCount(); i++) {
            cout << targetArtist << '/' << targetNode->getTitle()[i] << '/'
                 << targetNode->getRunTime()[i] << '\n';
        }
        cout << "====================\n"
             << ": 해당 Artist 명으로 노래 검색\n\n";
    }
    if (target == "TITLE") {
        TitleBSTNode*& targetNode = this->tb.search(targetTitle);

        if (targetNode == nullptr) {
            cout << "========ERROR========\n"
                 << "400\n"
                 << "====================\n"
                 << ": TitleBST에 해당 곡 없음\n\n";
            return;
        }

        cout << "========SEARCH========\n";
        for (int i = 0; i < targetNode->getCount(); i++) {
            cout << targetNode->getArtist()[i] << '/' << targetTitle << '/'
                 << targetNode->getRunTime()[i] << '\n';
        }
        cout << "====================\n"
             << ": 노래 제목을 기준으로 검색\n\n";
    }
    if (target == "SONG") {
        ArtistBSTNode*& targetNode = this->ab.search(targetArtist);
        if (targetNode == nullptr) {
            cout << "========ERROR========\n"
                 << "400\n"
                 << "====================\n"
                 << ": TitleBST에 해당 곡 없음\n\n";
            return;
        }

        for (int i = 0; i < targetNode->getCount(); i++) {
            if (targetNode->getTitle()[i] == targetTitle) {
                cout << "========SEARCH========\n"
                     << targetArtist << '/' << targetTitle << '/' << targetNode->getRunTime()[i]
                     << '\n'
                     << "====================\n"
                     << ": 하나의 음원에 대한 검색\n\n";

                return;
            }
        }

        cout << "========ERROR========\n"
             << "400\n"
             << "====================\n"
             << ": BST에 해당 곡 없음\n\n";
        return;
    }
}
// pl insert
void Manager::MAKEPL(string target, string targetArtist, string targetTitle) {
    if (target == "ARTIST") {
        ArtistBSTNode*& artistTemp = this->ab.search(targetArtist);

        if (artistTemp == nullptr) {
            cout << "========ERROR========\n"
                 << "500\n"
                 << "====================\n"
                 << ": ArtistBST에 해당 곡 없음\n\n";
            return;
        }
        if (artistTemp->getCount() > (10 - this->pl.getCount())) {
            cout << "========ERROR========\n"
                 << "500\n"
                 << "====================\n"
                 << ": 넣고자 하는 곡의 수가 playlist 여유공간을 넘어선 경우\n\n";
            return;
        }

        vector<string> titles = artistTemp->getTitle();
        vector<string> runTimes = artistTemp->getRunTime();

        for (int i = 0; i < this->pl.getCount(); i++) {
            for (int j = 0; j < artistTemp->getCount(); j++) {
                if (this->pl.exist(targetArtist, titles[j]) == true) {
                    cout << "========ERROR========\n"
                         << "500\n"
                         << "====================\n"
                         << ": Play List에 중복 곡 있음\n\n";
                    return;
                }
            }
        }

        for (int i = 0; i < artistTemp->getCount(); i++) {
            if (this->pl.insert_node(targetArtist, titles[i], runTimes[i]) == false) {
                return;
            }
        }

        cout << "========MAKEPL========\n";
        this->pl.print();
        cout << "====================\n" << ": Artist 기준으로 노래 추가\n\n";

        return;
    }
    if (target == "TITLE") {
        TitleBSTNode*& titleTemp = this->tb.search(targetTitle);

        if (titleTemp == nullptr) {
            cout << "========ERROR========\n"
                 << "500\n"
                 << "====================\n"
                 << ": TitleBST에 해당 곡 없음\n\n";
            return;
        }

        if (titleTemp->getCount() > (10 - this->pl.getCount())) {
            cout << "========ERROR========\n"
                 << "500\n"
                 << "====================\n"
                 << ": 넣고자 하는 곡의 수가 playlist 여유공간을 넘어선 경우\n\n";
            return;
        }

        vector<string> artists = titleTemp->getArtist();
        vector<string> runTimes = titleTemp->getRunTime();

        for (int i = 0; i < this->pl.getCount(); i++) {
            for (int j = 0; j < titleTemp->getCount(); j++) {
                if (this->pl.exist(artists[j], targetTitle) == true) {
                    cout << "========ERROR========\n"
                         << "500\n"
                         << "====================\n"
                         << ": Play List에 중복 곡 있음\n\n";
                    return;
                }
            }
        }

        for (int i = 0; i < titleTemp->getCount(); i++) {
            if (this->pl.insert_node(artists[i], targetTitle, runTimes[i]) == false) {
                return;
            }
        }

        cout << "========MAKEPL========\n";
        this->pl.print();
        cout << "====================\n" << ": Title 기준으로 노래 추가\n\n";
    }
    if (target == "SONG") {
        ArtistBSTNode*& artistTemp = this->ab.search(targetArtist);

        if (artistTemp == nullptr) {
            cout << "========ERROR========\n"
                 << "500\n"
                 << "====================\n"
                 << ": BST에 해당 곡 없음\n\n";
            return;
        }

        for (int i = 0; i < artistTemp->getCount(); i++) {
            if (artistTemp->getTitle()[i] == targetTitle) {
                if (this->pl.insert_node(targetArtist, targetTitle, artistTemp->getRunTime()[i]) ==
                    false) {
                    return;
                }
                cout << "========MAKEPL========\n";
                this->pl.print();
                cout << "====================\n" << ": 특정 음원 하나 기준으로 노래 추가\n\n";
                return;
            }
        }
        cout << "========ERROR========\n"
             << "500\n"
             << "====================\n"
             << ": BST에 해당 곡 없음\n\n";
        return;
    }
}
// print
void Manager::PRINT(string target) {
    if (target == "ARTIST") {
        if (this->ab.print() == false) {
            cout << "========ERROR========\n"
                 << "600\n"
                 << "====================\n"
                 << ": ArtistBST에 출력할 곡 없음\n\n";
            return;
        }
        return;
    }
    if (target == "TITLE") {
        if (this->tb.print() == false) {
            cout << "========ERROR========\n"
                 << "600\n"
                 << "====================\n"
                 << ": TitleBST에 출력할 곡 없음\n\n";
            return;
        }
        return;
    }
    if (target == "LIST") {
        if (this->pl.getCount() == 0) {
            cout << "========ERROR========\n"
                 << "600\n"
                 << "====================\n"
                 << ": PlayList에 출력할 곡 없음\n\n";
            return;
        }

        cout << "========Print========\n";
        this->pl.print();
        cout << "====================\n" << ": playlist 전체 출력\n\n";

        return;
    }
}

void Manager::DELETE(string target, string targetArtist, string targetTitle) {
    if (target == "ARTIST") {
        // --- Precheck ---
        ArtistBSTNode*& artistNode = this->ab.search(targetArtist);
        if (artistNode == nullptr) {
            cout << "========ERROR========\n"
                 << "700\n"
                 << "====================\n"
                 << ": 존재 하지 않는 데이터에 대한 명령어 1\n\n";

            return;
        }
        const vector<string>& titles = artistNode->getTitle();
        const int n = artistNode->getCount();

        // TitleBST에 (artist, title) 쌍이 모두 존재하는지 확인
        for (int i = 0; i < n; i++) {
            TitleBSTNode*& tnode = this->tb.search(titles[i]);
            if (tnode == nullptr) {
                cout << "========ERROR========\n"
                     << "700\n"
                     << "====================\n"
                     << ": 존재 하지 않는 데이터에 대한 명령어 2\n\n";

                return;
            }
            const vector<string>& artists = tnode->getArtist();
            bool foundPair = false;
            for (int j = 0; j < tnode->getCount(); ++j) {
                if (artists[j] == targetArtist) {
                    foundPair = true;
                    break;
                }
            }
            if (!foundPair) {
                cout << "========ERROR========\n"
                     << "700\n"
                     << "====================\n"
                     << ": 존재 하지 않는 데이터에 대한 명령어 3\n\n";

                return;
            }
        }

        // --- Apply (모두 확인됐으니 실제 삭제) ---
        for (int i = 0; i < n; i++) {
            // TitleBST에서 (artist,title) 삭제 실패 시 전체 롤백을 위해 그냥 에러 처리
            if (!this->tb.delete_node(targetArtist, titles[i])) {
                cout << "========ERROR========\n"
                     << "700\n"
                     << "====================\n"
                     << ": 존재 하지 않는 데이터에 대한 명령어 4\n\n";

                return;
            }
        }
        // PlayList는 있으면만 삭제 (없어도 성공에 영향 없음)
        for (int i = 0; i < n; ++i) {
            if (this->pl.exist(targetArtist, titles[i])) {
                (void)this->pl.delete_node(targetArtist, titles[i]);  // 실패해도 무시
            }
        }
        // ArtistBST에서 artist 노드 제거
        if (!this->ab.delete_node(targetArtist, "")) {
            cout << "========ERROR========\n"
                 << "700\n"
                 << "====================\n"
                 << ": 존재 하지 않는 데이터에 대한 명령어 5\n\n";

            return;
        }

        cout << "========DELETE========\n"
             << "Success\n"
             << "====================\n"
             << ": 해당 곡에 대한 데이터 전부 삭제\n\n";
        return;
    }

    // =========================
    // DELETE TITLE
    // =========================
    if (target == "TITLE") {
        // --- Precheck ---
        TitleBSTNode*& titleNode = this->tb.search(targetTitle);
        if (titleNode == nullptr) {
            cout << "========ERROR========\n"
                 << "700\n"
                 << "====================\n"
                 << ": 존재 하지 않는 데이터에 대한 명령어\n\n";

            return;
        }
        const vector<string>& artists = titleNode->getArtist();
        const int n = titleNode->getCount();

        // ArtistBST에 (artist, title) 쌍이 모두 존재하는지 확인
        for (int i = 0; i < n; ++i) {
            ArtistBSTNode*& anode = this->ab.search(artists[i]);
            if (anode == nullptr) {
                cout << "========ERROR========\n"
                     << "700\n"
                     << "====================\n"
                     << ": 존재 하지 않는 데이터에 대한 명령어\n\n";

                return;
            }
            const vector<string>& titles = anode->getTitle();
            bool foundPair = false;
            for (int j = 0; j < anode->getCount(); ++j) {
                if (titles[j] == targetTitle) {
                    foundPair = true;
                    break;
                }
            }
            if (!foundPair) {
                cout << "========ERROR========\n"
                     << "700\n"
                     << "====================\n"
                     << ": 존재 하지 않는 데이터에 대한 명령어\n\n";

                return;
            }
        }

        // --- Apply ---
        for (int i = 0; i < n; ++i) {
            if (!this->ab.delete_node(artists[i], targetTitle)) {
                cout << "========ERROR========\n"
                     << "700\n"
                     << "====================\n"
                     << ": 존재 하지 않는 데이터에 대한 명령어\n\n";

                return;
            }
        }
        for (int i = 0; i < n; ++i) {
            if (this->pl.exist(artists[i], targetTitle)) {
                (void)this->pl.delete_node(artists[i], targetTitle);  // 실패 무시
            }
        }
        if (!this->tb.delete_node("", targetTitle)) {
            cout << "========ERROR========\n"
                 << "700\n"
                 << "====================\n"
                 << ": 존재 하지 않는 데이터에 대한 명령어\n\n";

            return;

            cout << "========DELETE========\n"
                 << "Success\n"
                 << "====================\n"
                 << ": 해당 곡에 대한 데이터 전부 삭제\n\n";
            return;
        }

        // =========================
        // DELETE LIST (playlist only)
        // =========================
        if (target == "LIST") {
            // --- Precheck ---
            if (!this->pl.exist(targetArtist, targetTitle)) {
                cout << "========ERROR========\n"
                     << "700\n"
                     << "====================\n"
                     << ": 존재 하지 않는 데이터에 대한 명령어\n\n";

                return;
            }
            // --- Apply ---
            if (!this->pl.delete_node(targetArtist, targetTitle)) {
                cout << "========ERROR========\n"
                     << "700\n"
                     << "====================\n"
                     << ": 존재 하지 않는 데이터에 대한 명령어\n\n";

                return;
            }

            cout << "========DELETE========\n"
                 << "Success\n"
                 << "====================\n"
                 << ": 해당 곡에 대한 데이터 전부 삭제\n\n";
            return;
        }

        // =========================
        // DELETE SONG (single pair across all)
        // =========================
        if (target == "SONG") {
            // --- Precheck ---
            ArtistBSTNode*& anode = this->ab.search(targetArtist);
            if (anode == nullptr) {
                cout << "========ERROR========\n"
                     << "700\n"
                     << "====================\n"
                     << ": 존재 하지 않는 데이터에 대한 명령어\n\n";

                return;
            }
            TitleBSTNode*& tnode = this->tb.search(targetTitle);
            if (tnode == nullptr) {
                cout << "========ERROR========\n"
                     << "700\n"
                     << "====================\n"
                     << ": 존재 하지 않는 데이터에 대한 명령어\n\n";

                return;
            }
            bool titleFlag = false, artistFlag = false;
            const vector<string>& titles = anode->getTitle();
            const vector<string>& artists = tnode->getArtist();
            for (int i = 0; i < anode->getCount(); ++i)
                if (titles[i] == targetTitle) {
                    titleFlag = true;
                    break;
                }
            for (int i = 0; i < tnode->getCount(); ++i)
                if (artists[i] == targetArtist) {
                    artistFlag = true;
                    break;
                }
            if (!titleFlag || !artistFlag) {
                cout << "========ERROR========\n"
                     << "700\n"
                     << "====================\n"
                     << ": 존재 하지 않는 데이터에 대한 명령어\n\n";

                return;
            }

            // --- Apply ---
            if (!this->ab.delete_node(targetArtist, targetTitle) ||
                !this->tb.delete_node(targetArtist, targetTitle)) {
                cout << "========ERROR========\n"
                     << "700\n"
                     << "====================\n"
                     << ": 존재 하지 않는 데이터에 대한 명령어\n\n";

                return;
            }
            if (this->pl.exist(targetArtist, targetTitle)) {
                (void)this->pl.delete_node(targetArtist, targetTitle);  // 실패 무시
            }

            cout << "========DELETE========\n"
                 << "Success\n"
                 << "====================\n"
                 << ": 해당 곡에 대한 데이터 전부 삭제\n\n";
            return;
        }
    }
}

void Manager::EXIT() {
}