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
            } else if (artist > temp->getArtist()) {
                temp = temp->getRight();
            }
        }
        if (artist < parentTemp->getArtist()) {
            parentTemp->setLeft(node);
        } else if (artist > parentTemp->getArtist()) {
            parentTemp->setRight(node);
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

        return true;
    }
}

ArtistBSTNode* ArtistBST::search(string targetArtist) {
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

    // (1) 동일 아티스트 내 특정 제목만 지우는 분기(원형 유지)
    if ((targetNode != nullptr) && (targetTitle != "") && (targetNode->getCount() > 1)) {
        for (int i = 0; i < targetNode->getCount(); i++) {
            if (targetNode->getTitle()[i] == targetTitle) {
                targetNode->getTitle().erase(targetNode->getTitle().begin() + i);
                targetNode->setCount();  // 카운트 감소 함수가 맞는지 확인 필요
                return true;
            }
        }
        cout << "no target\n";
        return false;
    }

    // (2) 루트 삭제 분기 보강: 리프/단일자식/두자식 케이스 처리  // CHANGED
    if (targetNode == this->root) {
        // 리프
        if ((targetNode->getLeft() == nullptr) && (targetNode->getRight() == nullptr)) {
            this->root = nullptr;
            delete targetNode;
            return true;
        }
        // 한 쪽 자식만
        if ((targetNode->getLeft() == nullptr) && (targetNode->getRight() != nullptr)) {
            ArtistBSTNode* child = targetNode->getRight();
            this->root = child;
            delete targetNode;
            return true;
        }
        if ((targetNode->getLeft() != nullptr) && (targetNode->getRight() == nullptr)) {
            ArtistBSTNode* child = targetNode->getLeft();
            this->root = child;
            delete targetNode;
            return true;
        }
        // 두 자식: 중위 후계자 로직 보강  // CHANGED
        ArtistBSTNode* succParent = targetNode;
        ArtistBSTNode* succ = targetNode->getRight();
        while (succ->getLeft() != nullptr) {
            succParent = succ;
            succ = succ->getLeft();
        }
        // 후계자를 원래 자리에서 떼어내기
        if (succParent != targetNode) {
            // succ는 왼쪽 자식이 없으므로, succParent->left 를 succ->right 로 치환
            succParent->setLeft(succ->getRight());
        } else {
            // 바로 오른쪽 자식이 후계자인 경우: 자기참조 방지
            targetNode->setRight(succ->getRight());  // CHANGED
        }
        // succ를 루트 자리로 이식
        succ->setLeft(targetNode->getLeft());
        succ->setRight(targetNode->getRight());
        this->root = succ;
        delete targetNode;
        return true;
    }

    // (3) 루트가 아닌 경우 부모 탐색
    ArtistBSTNode* parentNode = this->root;

    // CHANGED: 조건 || → && (무한루프 방지)
    while ((parentNode->getLeft() != targetNode) && (parentNode->getRight() != targetNode)) {
        // CHANGED: 비교 방향 보정 (BST 탐색의 올바른 방향)
        if (parentNode->getArtist() < targetNode->getArtist()) {
            parentNode = parentNode->getRight();  // 키가 크면 오른쪽으로
        } else if (parentNode->getArtist() > targetNode->getArtist()) {
            parentNode = parentNode->getLeft();  // 키가 작으면 왼쪽으로
        } else {
            break;
        }
    }

    // (4) 두 자식 모두 있는 경우: 후계자 분리 로직 보강판  // CHANGED
    if ((targetNode->getLeft() != nullptr) && (targetNode->getRight() != nullptr)) {
        ArtistBSTNode* succParent = targetNode;
        ArtistBSTNode* succ = targetNode->getRight();
        while (succ->getLeft() != nullptr) {
            succParent = succ;
            succ = succ->getLeft();
        }

        // 후계자를 원래 자리에서 떼어내기
        if (succParent != targetNode) {
            succParent->setLeft(succ->getRight());
        } else {
            targetNode->setRight(succ->getRight());  // CHANGED: 자기참조 방지
        }

        // succ를 target 자리로 이식
        succ->setLeft(targetNode->getLeft());
        succ->setRight(targetNode->getRight());

        // 부모와 연결
        if (parentNode->getLeft() == targetNode) {
            parentNode->setLeft(succ);
        } else if (parentNode->getRight() == targetNode) {
            parentNode->setRight(succ);
        }

        delete targetNode;
        return true;
    }

    // (5) 한 자식 또는 리프: 기존 형태 유지
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

    return false;  // 안전망
}
