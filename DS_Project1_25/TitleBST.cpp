#include "TitleBST.h"

#include <iostream>

#include "TitleBSTNode.h"
using namespace std;

TitleBST::TitleBST() {
    this->root = nullptr;
    this->parent = nullptr;
    this->data = "";
    this->target = nullptr;
}
TitleBST::~TitleBST() {
}

void TitleBST::insert(const string artist, const string title, const string run_time) {
    TitleBSTNode* curNode = this->root;
    TitleBSTNode* parentNode = nullptr;

    while (curNode) {
        parentNode = curNode;

        if (title == curNode->getTitle()) {
            if (curNode->search(artist) != -1) {
                cout << "중복";
                return;
            } else {
                curNode->set(artist, title, run_time);
                return;
            }
        }

        if (title < curNode->getTitle()) {
            curNode = curNode->getLeft();
        } else if (title > curNode->getTitle()) {
            curNode = curNode->getRight();
        }
    }

    TitleBSTNode* node = new TitleBSTNode;
    node->set(artist, title, run_time);

    if (this->root == nullptr) {
        this->root = node;
        return;
    }

    if (title < parentNode->getTitle()) {
        parentNode->setLeft(node);
    } else if (title > parentNode->getTitle()) {
        parentNode->setRight(node);
    }
}

void TitleBST::search(string targetTitle) {
    TitleBSTNode* curNode = this->root;

    while (curNode) {
        if (targetTitle < curNode->getTitle()) {
            curNode = curNode->getLeft();
        } else if (targetTitle > curNode->getTitle()) {
            curNode = curNode->getRight();
        } else if (targetTitle == curNode->getTitle()) {
            for (int i = 0; i < curNode->getCount(); i++) {
                cout << curNode->getArtist()[i] << '/' << curNode->getTitle() << '/'
                     << curNode->getRunTime()[i] << '\n';
            }
            return;
        }
    }
    cout << "해당 제목 없음";
    return;
}

void TitleBST::inOrder(TitleBSTNode* curNode) {
    if (curNode) {
        inOrder(curNode->getLeft());
        for (int i = 0; i < curNode->getCount(); i++) {
            cout << curNode->getArtist()[i] << '/' << curNode->getTitle() << '/'
                 << curNode->getRunTime()[i] << '\n';
        }
        inOrder(curNode->getRight());
    }
    return;
}

void TitleBST::print() {
    inOrder(this->root);
}

void TitleBST::delete_node(string targetTitle) {
    TitleBSTNode* curNode = this->root;
    TitleBSTNode* parentNode = nullptr;

    while (curNode) {
        if (targetTitle < curNode->getTitle()) {
            parentNode = curNode;
            curNode = curNode->getLeft();
        } else if (targetTitle > curNode->getTitle()) {
            parentNode = curNode;
            curNode = curNode->getRight();
        } else if (targetTitle == curNode->getTitle()) {
            if (curNode->getLeft() != nullptr && curNode->getRight() != nullptr) {
                TitleBSTNode* temp = curNode->getRight();
                TitleBSTNode* parentTemp = curNode;

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
        }
    }
    cout << "해당 제목 없음";
    return;
}
