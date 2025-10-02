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

bool TitleBST::delete_node(string targetTitle, string targetArtist) {
    TitleBSTNode* targetNode = search(targetTitle);

    if (targetNode == nullptr) {
        cout << "no target\n";
        return false;
    }

    // (1) 동일 제목 내 특정 아티스트만 지우는 분기(원형 유지)
    if ((targetNode != nullptr) && (targetArtist != "") && (targetNode->getCount() > 1)) {
        for (int i = 0; i < targetNode->getCount(); i++) {
            if (targetNode->getArtist()[i] == targetArtist) {
                targetNode->getArtist().erase(targetNode->getArtist().begin() + i);
                targetNode->setCount();  // 카운트 감소 함수가 맞는지 확인 필요
                return true;
            }
        }
        cout << "no target\n";
        return false;
    }

    // (2) 루트 삭제 분기 보강: 리프/단일자식/두자식 케이스 처리  // CHANGED: 루트면 무조건 nullptr
    // → 케이스별 처리
    if (targetNode == this->root) {
        // 리프
        if ((targetNode->getLeft() == nullptr) && (targetNode->getRight() == nullptr)) {
            this->root = nullptr;
            delete targetNode;
            return true;
        }
        // 한 쪽 자식만
        if ((targetNode->getLeft() == nullptr) && (targetNode->getRight() != nullptr)) {
            TitleBSTNode* child = targetNode->getRight();
            this->root = child;
            delete targetNode;
            return true;
        }
        if ((targetNode->getLeft() != nullptr) && (targetNode->getRight() == nullptr)) {
            TitleBSTNode* child = targetNode->getLeft();
            this->root = child;
            delete targetNode;
            return true;
        }
        // 두 자식: 중위 후계자 로직(아래와 동일한 보강판 사용)  // CHANGED: 후계자 분리 로직 보강
        TitleBSTNode* succParent = targetNode;
        TitleBSTNode* succ = targetNode->getRight();
        while (succ->getLeft() != nullptr) {
            succParent = succ;
            succ = succ->getLeft();
        }
        // 후계자를 원래 자리에서 떼어내기
        if (succParent != targetNode) {
            // succ는 왼쪽 자식이 없으므로, succParent->left 를 succ->right 로 치환
            succParent->setLeft(succ->getRight());
            // target의 오른쪽 서브트리는 이후 succ->setRight에서 붙음
        } else {
            // 후계자가 target의 바로 오른쪽 자식인 경우 자기참조 방지
            targetNode->setRight(succ->getRight());  // CHANGED: 자기참조 방지 핵심
        }
        // succ를 루트 자리로 이식
        succ->setLeft(targetNode->getLeft());
        succ->setRight(targetNode->getRight());
        this->root = succ;
        delete targetNode;
        return true;
    }

    // (3) 루트가 아닌 경우 부모 탐색
    TitleBSTNode* parentNode = this->root;

    // CHANGED: 조건 || → && (네가 이미 바꾼 것 반영)
    while ((parentNode->getLeft() != targetNode) && (parentNode->getRight() != targetNode)) {
        // CHANGED: 비교 방향 보정 (BST 탐색의 올바른 방향)
        if (parentNode->getTitle() < targetNode->getTitle()) {
            parentNode = parentNode->getRight();  // 키가 크면 오른쪽으로
        } else if (parentNode->getTitle() > targetNode->getTitle()) {
            parentNode = parentNode->getLeft();  // 키가 작으면 왼쪽으로
        } else {
            // 같은 키일 일은 일반적으로 없음(찾은 target까지 내려오는 루프)
            break;
        }
    }

    // (4) 두 자식 모두 있는 경우: 후계자 분리 로직 보강판  // CHANGED: 전체 보강
    if ((targetNode->getLeft() != nullptr) && (targetNode->getRight() != nullptr)) {
        TitleBSTNode* succParent = targetNode;
        TitleBSTNode* succ = targetNode->getRight();
        while (succ->getLeft() != nullptr) {
            succParent = succ;
            succ = succ->getLeft();
        }

        // 후계자를 원래 자리에서 떼어내기
        if (succParent != targetNode) {
            // succParent의 왼쪽을 succ의 오른쪽으로 치환
            succParent->setLeft(succ->getRight());
        } else {
            // 바로 오른쪽 자식이 후계자인 경우: 자기참조 방지
            targetNode->setRight(succ->getRight());  // CHANGED
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

    // (5) 한 자식 또는 리프: 기존 형태 유지 (부모 왼/오른쪽 분기)
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
