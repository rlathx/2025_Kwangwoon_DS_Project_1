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
// Check if the input specification is correct with the split function
// temp == nullptr : specification error -> error code 200
// temp != nullptr : no error
// Check if there are overlapping nodes with the exist function
// exist(temp) == false: No overlapping nodes
// exist(temp) == true: There are overlapping nodes
void MusicQueue::push(string& target) {
    MusicQueueNode* temp = split(target);
    if (temp) {
        this->size++;

        if (this->head == nullptr) {
            this->head = temp;
            this->rear = temp;

            cout << temp->getArtist() << '/' << temp->getTitle() << '/' << temp->getRunTime()
                 << '\n';

            return;
        } else {
            if (exist(temp->getArtist(), temp->getTitle())) {
                cout << "========ERROR========" << '\n'
                     << "200 / MusicQueue.cpp - push / 겹치는 노드 있음" << '\n'
                     << "=====================" << '\n';
                return;
            }
            this->rear->setNext(temp);
            temp->setPrev(this->rear);
            this->rear = temp;

            cout << "========ADD========" << '\n'
                 << temp->getArtist() << '/' << temp->getTitle() << '/' << temp->getRunTime()
                 << '\n'
                 << "====================";
        }
    } else {
        cout << "========ERROR========" << '\n'
             << "200 / MusicQueue.cpp - push / 규격 안 맞음" << '\n'
             << "=====================" << '\n';
        return;
    }
}

MusicQueueNode* MusicQueue::pop() {
    if (empty()) {
        cout << "========ERROR========" << '\n'
             << "300 / MusicQueue.cpp - pop / 아무것도 없는데 pop" << '\n'
             << "=====================" << '\n';
        return nullptr;
    }

    MusicQueueNode* temp = this->head;
    this->head = this->head->getNext();
    this->size--;

    return temp;
}

MusicQueueNode* MusicQueue::front() {
    return this->head;
}

// Enter data into each variable based on '/'
// '' : char
// "" : const char*, string (end letter == null)

// If any of the following fields are missing: singer name, song title, or playing time, nullptr is
// returned.
MusicQueueNode* MusicQueue::split(const string& target) {
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