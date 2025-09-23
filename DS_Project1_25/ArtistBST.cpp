#include "ArtistBST.h"

#include <iostream>

#include "ArtistBSTNode.h"
using namespace std;

ArtistBST::ArtistBST() {
    this->root = nullptr;
    this->parent = nullptr;
    this->data = "";
    this->target = nullptr;
}
ArtistBST::~ArtistBST() {
}

void ArtistBST::insert(const string artist, const string title, const string run_time) {
    ArtistBSTNode* curNode = this->root;
    ArtistBSTNode* parentNode = nullptr;

    while (curNode) {
        parentNode = curNode;

        if (artist == curNode->getArtist()) {
            if (curNode->search(title) != -1) {
                cout << "중복";
                return;
            } else {
                curNode->set(artist, title, run_time);
                return;
            }
        }

        if (artist < curNode->getArtist()) {
            curNode = curNode->getLeft();
        } else if (artist > curNode->getArtist()) {
            curNode = curNode->getRight();
        }
    }

    ArtistBSTNode* node = new ArtistBSTNode;
    node->set(artist, title, run_time);

    if (this->root == nullptr) {
        this->root = node;
        return;
    }

    if (artist < parentNode->getArtist()) {
        parentNode->setLeft(node);
    } else if (artist > parentNode->getArtist()) {
        parentNode->setRight(node);
    }
}

void ArtistBST::search(string targetArtist) {
    ArtistBSTNode* curNode = this->root;

    while (curNode) {
        if (targetArtist < curNode->getArtist()) {
            curNode = curNode->getLeft();
        } else if (targetArtist > curNode->getArtist()) {
            curNode = curNode->getRight();
        } else if (targetArtist == curNode->getArtist()) {
            for (int i = 0; i < curNode->getCount(); i++) {
                cout << curNode->getArtist() << '/' << curNode->getTitle()[i] << '/'
                     << curNode->getRunTime()[i] << '\n';
            }
            return;
        }
    }
    cout << "해당 가수 없음";
    return;
}

void ArtistBST::inOrder(ArtistBSTNode* curNode) {
    if (curNode) {
        inOrder(curNode->getLeft());
        for (int i = 0; i < curNode->getCount(); i++) {
            cout << curNode->getArtist() << '/' << curNode->getTitle()[i] << '/'
                 << curNode->getRunTime()[i] << '\n';
        }
        inOrder(curNode->getRight());
    }
    return;
}

void ArtistBST::print() {
    inOrder(this->root);
}

void ArtistBST::delete_node(string targetArtist, string title) {
    ArtistBSTNode* curNode = this->root;
    ArtistBSTNode* parentNode = nullptr;

    while (curNode) {
        if (targetArtist < curNode->getArtist()) {
            parentNode = curNode;
            curNode = curNode->getLeft();
        } else if (targetArtist > curNode->getArtist()) {
            parentNode = curNode;
            curNode = curNode->getRight();
        } else if (targetArtist == curNode->getArtist()) {
            if (title == "" || ((title != "") && (curNode->getCount() == 1))) {
                if (curNode->getLeft() != nullptr && curNode->getRight() != nullptr) {
                    ArtistBSTNode* temp = curNode->getRight();
                    ArtistBSTNode* parentTemp = curNode;

                    while (temp->getLeft()) {
                        parentTemp = temp;
                        temp = temp->getLeft();
                    }

                    if (parentTemp->getLeft() == temp) {
                        parentTemp->setLeft(temp->getRight());
                    } else if (parentTemp->getRight() == temp) {
                        parentTemp->setRight(temp->getRight());
                    }

                    if (parentNode == nullptr) {
                        this->root = temp;
                    } else {
                        if (parentNode->getLeft() == curNode) {
                            parentNode->setLeft(temp);
                        } else if (parentNode->getRight() == curNode) {
                            parentNode->setRight(temp);
                        }
                    }

                    temp->setLeft(curNode->getLeft());
                    temp->setRight(curNode->getRight());

                    delete curNode;

                    return;
                } else if (curNode->getLeft() == nullptr && curNode->getRight() == nullptr) {
                    if (parentNode == nullptr) {
                        this->root = nullptr;
                    } else if (parentNode->getLeft() == curNode) {
                        parentNode->setLeft(nullptr);
                    } else if (parentNode->getRight() == curNode) {
                        parentNode->setRight(nullptr);
                    }

                    delete curNode;

                    return;
                } else if (curNode->getLeft() != nullptr && curNode->getRight() == nullptr) {
                    if (parentNode == nullptr) {
                        this->root = curNode->getLeft();
                    } else if (parentNode->getLeft() == curNode) {
                        parentNode->setLeft(curNode->getLeft());
                    } else if (parentNode->getRight() == curNode) {
                        parentNode->setRight(curNode->getLeft());
                    }

                    delete curNode;

                    return;
                } else if (curNode->getLeft() == nullptr && curNode->getRight() != nullptr) {
                    if (parentNode == nullptr) {
                        this->root = curNode->getRight();
                    } else if (parentNode->getLeft() == curNode) {
                        parentNode->setLeft(curNode->getRight());
                    } else if (parentNode->getRight() == curNode) {
                        parentNode->setRight(curNode->getRight());
                    }

                    delete curNode;

                    return;
                }
            } else {
                int idx = curNode->search(title);
                if (idx == -1) {
                    cout << "해당 곡 없음";
                } else {
                    curNode->getTitle().erase(curNode->getTitle().begin() + idx);
                    curNode->setSumOfRunTime(idx);
                    curNode->getRunTime().erase(curNode->getRunTime().begin() + idx);
                    curNode->setCount();
                }

                return;
            }
        }
    }
    cout << "해당 가수 없음";
    return;
}
