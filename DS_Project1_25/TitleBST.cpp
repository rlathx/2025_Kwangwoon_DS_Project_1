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

bool TitleBST::insert(const string artist, const string title, const string run_time) {
    TitleBSTNode* curNode = this->root;
    TitleBSTNode* parentNode = nullptr;

    while (curNode) {
        parentNode = curNode;

        if (title == curNode->getTitle()) {
            if (curNode->search(artist) != -1) {
                cout << "artist 중복";
                return false;
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
        return true;
    }

    if (title < parentNode->getTitle()) {
        parentNode->setLeft(node);
    } else if (title > parentNode->getTitle()) {
        parentNode->setRight(node);
    }

    return true;
}

TitleBSTNode* TitleBST::search(string targetTitle) {
    TitleBSTNode* curNode = this->root;

    while (curNode) {
        if (targetTitle < curNode->getTitle()) {
            curNode = curNode->getLeft();
        } else if (targetTitle > curNode->getTitle()) {
            curNode = curNode->getRight();
        } else if (targetTitle == curNode->getTitle()) {
            return curNode;
        }
    }
    cout << "해당 제목 없음";
    return nullptr;
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

bool TitleBST::print() {
    if (this->root == nullptr) {
        return false;
    }
    inOrder(this->root);
    return true;
}

bool TitleBST::delete_node(string targetTitle) {
    TitleBSTNode* targetNode = search(targetTitle);

    if (targetNode == nullptr) {
        cout << "no target\n";
        return false;
    }

    if (targetNode == this->root) {
        this->root = nullptr;
        delete targetNode;

        return true;
    }

    TitleBSTNode* parentNode = this->root;
    while ((parentNode->getLeft() != targetNode) || (parentNode->getRight() != targetNode)) {
        if (parentNode->getTitle() < targetNode->getTitle()) {
            parentNode = parentNode->getLeft();
        } else if (parentNode->getTitle() > targetNode->getTitle()) {
            parentNode = parentNode->getRight();
        }
    }

    if ((targetNode->getLeft() != nullptr) && (targetNode->getRight() != nullptr)) {
        TitleBSTNode* inorderSuccessor = targetNode->getRight();

        while (inorderSuccessor->getLeft() != nullptr) {
            inorderSuccessor = inorderSuccessor->getLeft();
        }

        if (parentNode->getLeft() == targetNode) {
            parentNode->setLeft(inorderSuccessor);
            inorderSuccessor->setLeft(targetNode->getLeft());
            inorderSuccessor->setRight(targetNode->getRight());

            delete targetNode;

            return true;
        }
        if (parentNode->getRight() == targetNode) {
            parentNode->setRight(inorderSuccessor);
            inorderSuccessor->setLeft(targetNode->getLeft());
            inorderSuccessor->setRight(targetNode->getRight());

            delete targetNode;

            return true;
        }
    }

    if (parentNode->getLeft() == targetNode) {
        if ((targetNode->getLeft() == nullptr) && (targetNode->getRight() == nullptr)) {
            delete targetNode;
            parentNode->setLeft(nullptr);

            return true;
        }
        if ((targetNode->getLeft() == nullptr) && (targetNode->getRight() != nullptr)) {
            parentNode->setLeft(targetNode->getRight());
            delete targetNode;

            return true;
        }
        if ((targetNode->getLeft() != nullptr) && (targetNode->getRight() == nullptr)) {
            parentNode->setLeft(targetNode->getLeft());
            delete targetNode;

            return true;
        }
    }

    if (parentNode->getRight() == targetNode) {
        if ((targetNode->getLeft() == nullptr) && (targetNode->getRight() == nullptr)) {
            delete targetNode;
            parentNode->setRight(nullptr);

            return true;
        }
        if ((targetNode->getLeft() == nullptr) && (targetNode->getRight() != nullptr)) {
            parentNode->setRight(targetNode->getRight());
            delete targetNode;

            return true;
        }
        if ((targetNode->getLeft() != nullptr) && (targetNode->getRight() == nullptr)) {
            parentNode->setRight(targetNode->getLeft());
            delete targetNode;

            return true;
        }
    }
}
