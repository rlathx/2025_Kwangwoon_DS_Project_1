#include "Manager.h"

#include <cstring>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

// 에러 코드는 전부 여기서 다루는 게 안 헷갈릴 듯

Manager::Manager() {
}

Manager::~Manager() {
}

void Manager::run(const char* command) {
}
// ==== 여기서 추가
void Manager::LOAD() {
    // Music_List.txt 해당 파일 자체가 없을 때 에러 코드 출력
    // 한 번만 가능한 명령어, 두 번 부터는 에러코드 출력
}

void Manager::ADD(string target) {
    // Music_List.txt 데이터들과 비교해 같은 곡이 들어올 경우 에러 코드를 출력
    // a|a|a 하나의 string 전체를 Music_List에 있는 데이터 한줄한줄과 비교 -> 중복 없으면 add
    // 입력 규격 안 맞음 -> queue - push 에서 error 출력
    // queue - push 성공 시 해당 데이터 출력됨 -> 여기서 출력 포맷 만들어줘야함

    // if (리스트랑 비교했는데 중복됨) {에러 출력; return;}
    MusicQueueNode* temp = split(target);
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
MusicQueueNode* split(const string& target) {
    string artist = "";
    string title = "";
    string runTime = "";

    size_t idx = 0;

    for (; target[idx] != '|'; idx++) {
        artist += target[idx];
    }
    idx++;
    for (; target[idx] != '|'; idx++) {
        title += target[idx];
    }
    idx++;
    for (; idx < target.size(); idx++) {
        runTime += target[idx];
    }

    if (artist == "" || title == "" || runTime == "") {
        return nullptr;
    }

    MusicQueueNode* newNode = new MusicQueueNode;
    newNode->insert(artist, title, runTime);

    return newNode;
}