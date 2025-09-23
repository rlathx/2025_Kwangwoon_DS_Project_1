#pragma once
#include <string>

#include "TitleBSTNode.h"

class TitleBST {
   private:
    TitleBSTNode* root;
    TitleBSTNode* parent;
    std::string data;
    TitleBSTNode* target;

   public:
    TitleBST();
    ~TitleBST();

    void insert(const std::string artist, const std::string title, const std::string run_time);
    void search(std::string targetTitle);
    void inOrder(TitleBSTNode* curNode);
    void print();
    void delete_node(std::string targetTitle);
};
