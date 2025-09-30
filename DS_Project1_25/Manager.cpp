#include "Manager.h"

#include <cstring>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

Manager::Manager() {
    this->fcmd.open("Music_List.txt");
    this->loadCheck = false;
}

Manager::~Manager() {
}

bool Manager::run(const string& command) {
    // 1) 구분자 찾기 (안전)
    const std::size_t p1 = command.find('|');
    if (p1 == string::npos) {
        std::cout << "입력 규격 안 맞음";
        return false;
    }

    const std::size_t p2 = command.find('|', p1 + 1);
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
    const std::size_t L = runTime.size();
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
        // 예: 중복, 용량 초과 등은 push가 false로 알려주도록
        cout << "추가 실패";
        return false;
    }

    return true;
}

void Manager::LOAD() {
    if (loadCheck == true) {
        cout << "이제 해당 명령어 사용 불가";
        return;
    }
    if (!fcmd.is_open()) {
        cout << "파일 없음";
        return;
    }

    string line;
    while (getline(fcmd, line)) {
        if (run(line) == false) {
            cout << "error\n";
            return;
        }
    }

    fcmd.close();

    loadCheck = true;
}

void Manager::ADD(string command) {
    // Music_List.txt 데이터들과 비교해 같은 곡이 들어올 경우 에러 코드를 출력
    // a|a|a 하나의 string 전체를 Music_List에 있는 데이터 한줄한줄과 비교 -> 중복 없으면 add
    // 입력 규격 안 맞음 -> queue - push 에서 error 출력
    // queue - push 성공 시 해당 데이터 출력됨 -> 여기서 출력 포맷 만들어줘야함

    // if (리스트랑 비교했는데 중복됨) {에러 출력; return;}
    MusicQueueNode* temp = split(command);
    if (temp) {
        // ==add==
        // queue->push(temp)
        // =======
        // return;
    }
    // 입력 규격 안 맞아서 에러 출력
    cout << 200;
}

void Manager::QPOP() {
    // if(queue->pop() == nullptr) {에러코드 출력; return;}
    // bst->insert(temp)
    // 이미 bst에 있는 곡 : BST - insert 에서 에러 코드 출력
}

void Manager::SEARCH() {
}

void Manager::MAKEPL() {
}

void Manager::PRINT() {
}

void Manager::DELETE() {
}

void Manager::EXIT() {
}

// +a

// Enter data into each variable based on '/'
// '' : char
// "" : const char*, string (end letter == null)

// If any of the following fields are missing: singer name, song title, or playing time, nullptr is
// returned.