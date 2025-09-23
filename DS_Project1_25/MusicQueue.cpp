#include "MusicQueue.h"

#include <iostream>
using namespace std;

MusicQueue::MusicQueue() {
    this->head = nullptr;
    this->rear = nullptr;
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

void MusicQueue::push(MusicQueueNode* newNode) {
    if (this->size == 100) {
        cout << "들어갈 자리 없음" return;
    }
    this->size++;

    if (this->head == nullptr) {
        this->head = temp;
        this->rear = temp;
    } else {
        this->rear->setNext(newNode);
        newNode->setPrev(this->rear);
        this->rear = newNode;
    }
    cout << temp->getArtist() << '/' << temp->getTitle() << '/' << temp->getRunTime() << '\n';
}

MusicQueueNode* MusicQueue::pop() {
    if (empty()) {
        return nullptr;
    }

    MusicQueueNode* temp = this->head;
    this->head = this->head->getNext();
    this->head->setPrev(nullptr);
    this->size--;

    return temp;
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