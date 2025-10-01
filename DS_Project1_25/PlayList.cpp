#include "PlayList.h"

#include <iostream>
#include <string>

#include "PlayListNode.h"
using namespace std;

PlayList::PlayList() {
    this->head = nullptr;
    this->cursor = nullptr;

    this->count = 0;
    this->time = 0;

    this->data = "";
}

PlayList::~PlayList() {
}

bool PlayList::insert_node(string artist, string title, string runTime) {
    if (full()) {
        cout << "full";
        return false;
    }

    if (exist(artist, title)) {
        cout << "중복";
        return false;
    }

    PlayListNode* node = new PlayListNode;
    node->set(artist, title, runTime);

    this->count++;
    this->time += run_time(runTime);

    if (this->head == nullptr) {
        this->head = node;
        this->cursor = node;
        this->cursor->setNext(this->head);

        return true;
    }

    this->cursor->setNext(node);
    node->setPrev(this->cursor);
    node->setNext(this->head);
    this->cursor = node;

    return true;
}

bool PlayList::delete_node(sstring targetArtist, string targetTitle) {
    if (this->head == nullptr) {
        cout << "지울 게 없음";
        return false;
    }

    if (exist(targetArtist, targetTitle) == false) {
        cout << "지울 게 없음";
        return false;
    }

    PlayListNode* temp = this->head;

    for (int i = 0; i < this->count; i++) {
        if ((temp->getArtist() == targetArtist) && (temp->getTitle() == targetTitle)) {
            break;
        }
        temp = temp->getNext();
    }

    this->count--;
    this->time -= run_time(temp->getRunTime());

    if ((temp == this->head) && (this->count == 0)) {
        delete temp;
        this->head = nullptr;
        this->cursor = nullptr;

        return true;
    }

    if (temp == this->head) {
        this->head = this->head->getNext();
        this->head->setPrev(nullptr);
        this->cursor->setNext(this->head);

        delete temp;
        return true;
    }

    if (temp == this->cursor) {
        this->cursor = this->cursor->getPrev();
        this->cursor->setNext(this->head);

        delete temp;
        return true;
    }

    temp->getPrev()->setNext(temp->getNext());
    temp->getNext()->setPrev(temp->getPrev());

    delete temp;
    return true;
}

bool PlayList::empty() {
    if (this->count == 0) return true;
    return false;
}

bool PlayList::full() {
    if (this->count == 10) return true;
    return false;
}

bool PlayList::exist(string artist, string title) {
    PlayListNode* temp = this->head;

    for (int i = 0; i < this->count; i++) {
        if ((temp->getArtist() == artist) && (temp->getTitle() == title)) {
            break;
        }
        temp = temp->getNext();
    }

    return false;
}

bool PlayList::print() {
    if (this->head == nullptr) {
        return false;
    }
    PlayListNode* temp = this->head;

    for (int i = 0; i < this->count; i++) {
        cout << temp->getArtist() << '/' << temp->getTitle() << '/' << temp->getRunTime() << '\n';
        temp = temp->getNext();
    }

    cout << "Count : " << this->count << " / 10" << '\n'
         << "Time: " << this->time / 60 << "min " << this->time % 60 << "sec" << '\n';

    return true;
}

int PlayList::run_time(string runTime) {
    int separator = runTime.find(":");

    string min = runTime.substr(0, separator);
    string sec = runTime.substr(separator + 1);

    int totalSeconds = (std::stoi(min) * 60) + std::stoi(sec);

    return totalSeconds;
}