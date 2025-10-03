#include "MusicQueue.h"

#include <iostream>
using namespace std;

MusicQueue::MusicQueue() {
    this->head = nullptr;
    this->rear = nullptr;
    this->size = 0;
}

MusicQueue::~MusicQueue() {
}

bool MusicQueue::empty() {
    if (this->size == 0) return true;
    return false;
}

bool MusicQueue::exist(string artist, string title) {
    MusicQueueNode* temp = this->head;

    while (temp) {
        if (temp->exist(artist, title)) {
            return true;
        }
        temp = temp->getNext();
    }
    return false;
}

bool MusicQueue::push(const std::string& artist, const std::string& title,
                      const std::string& runTime) {
    if (this->size >= 100) {
        cout << "========ERROR========\n"
             << "200\n"
             << "====================\n"
             << ": Queue Full\n\n";
        return false;
    }

    MusicQueueNode* newNode = new MusicQueueNode;
    newNode->insert(artist, title, runTime);

    if (this->head == nullptr) {
        this->head = newNode;
        this->rear = newNode;
    } else {
        this->rear->setNext(newNode);
        newNode->setPrev(this->rear);
        this->rear = newNode;
    }
    this->size++;

    return true;
}

MusicQueueNode* MusicQueue::pop() {
    if (this->head == nullptr) return nullptr;

    MusicQueueNode* temp = this->head;
    MusicQueueNode* next = temp->getNext();

    // 새 head 설정
    this->head = next;
    if (next != nullptr) {
        next->setPrev(nullptr);
    } else {
        // 큐가 비게 되었으므로 rear도 nullptr로
        this->rear = nullptr;
    }

    // 반환 노드를 안전하게 분리
    temp->setNext(nullptr);
    temp->setPrev(nullptr);

    this->size--;
    return temp;
}

void MusicQueue::print() {
    MusicQueueNode* temp = this->head;
    while (temp != nullptr) {
        cout << temp->getArtist() << '/' << temp->getTitle() << '/' << temp->getRunTime() << "\n";

        temp = temp->getNext();
    }
    return;
}

MusicQueueNode* MusicQueue::front() {
    return this->head;
}

// int main() {
//     string command, target;
//     MusicQueue* list = new MusicQueue;
//     while (true) {
//         cin >> command;

//         if (command == "push") {
//             cin >> std::ws;
//             getline(cin, target);
//             list->push(target);
//         } else if (command == "pop") {
//             MusicQueueNode* temp = list->pop();
//             if (temp == nullptr) continue;
//             cout << temp->getArtist() << '/' << temp->getTitle() << '/' << temp->getRunTime()
//                  << "\n";
//         }
//     }
//     return 0;
// }