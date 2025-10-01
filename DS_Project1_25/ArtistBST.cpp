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

bool ArtistBST::insert(const string artist, const string title, const string run_time) {
    ArtistBSTNode* targetNode = search(artist);

    if (targetNode == nullptr) {
        ArtistBSTNode* node = new ArtistBSTNode;
        node->set(artist, title, run_time);

        if (this->root == nullptr) {
            this->root = node;
            return true;
        }

        ArtistBSTNode* temp = this->root;
        ArtistBSTNode* parentTemp = nullptr;

        while (temp != nullptr) {
            parentTemp = temp;

            if (artist < temp->getArtist()) {
                temp = temp->getLeft();
            } else if (artist > parentNode->getArtist()) {
                temp = temp->getRight();
            }
        }
        if (artist < parentTemp->getArtist()) {
            parentNode->setLeft(node);
        } else if (artist > parentTemp->getArtist()) {
            parentNode->setRight(node);
        }

        return true;
    } else {
        for (int i = 0; i < targetNode->getCount(); i++) {
            if (targetNode->getTitle()[i] == title) {
                cout << "title 중복\n";
                return false;
            }
        }
        targetNode->set(artist, title, run_time);
    }
}

ArtistBSTNode*& ArtistBST::search(string targetArtist) {
    ArtistBSTNode* curNode = this->root;

    while (curNode) {
        if (targetArtist < curNode->getArtist()) {
            curNode = curNode->getLeft();
        } else if (targetArtist > curNode->getArtist()) {
            curNode = curNode->getRight();
        } else if (targetArtist == curNode->getArtist()) {
            return curNode;
        }
    }
    cout << "해당 가수 없음";
    return nullptr;
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

bool ArtistBST::print() {
    if (this->root == nullptr) {
        return false;
    }
    inOrder(this->root);
    return true;
}

bool ArtistBST::delete_node(string targetArtist, string targetTitle) {
    ArtistBSTNode* targetNode = search(targetArtist);

    if (targetNode == nullptr) {
        cout << "no target\n";
        return false;
    }

    if ((targetNode != nullptr) && (targetTitle != "") && (targetNode->getCount() > 1)) {
        for (int i = 0; i < targetNode->getCount(); i++) {
            if (targetNode->getTitle()[i] == targetTitle) {
                targetNode->getTitle().erase(targetNode->getTitle().begin() + i);
                targetNode->setCount();

                return true;
            }
        }
        cout << "no target\n";
        return false;
    }

    if (targetNode == this->root) {
        this->root = nullptr;
        delete targetNode;

        return true;
    }

    ArtistBSTNode* parentNode = this->root;
    while ((parentNode->getLeft() != targetNode) || (parentNode->getRight() != targetNode)) {
        if (parentNode->getArtist() < targetNode->getArtist()) {
            parentNode = parentNode->getLeft();
        } else if (parentNode->getArtist() > targetNode->getArtist()) {
            parentNode = parentNode->getRight();
        }
    }

    if ((targetNode->getLeft() != nullptr) && (targetNode->getRight() != nullptr)) {
        ArtistBSTNode* inorderSuccessor = targetNode->getRight();

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