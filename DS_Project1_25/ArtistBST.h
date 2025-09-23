#pragma once
#include <string>

#include "ArtistBSTNode.h"

class ArtistBST {
   private:
    ArtistBSTNode* root;
    ArtistBSTNode* parent;
    std::string data;
    ArtistBSTNode* target;

   public:
    ArtistBST();
    ~ArtistBST();

    void insert(const std::string artist, const std::string title, const std::string run_time);
    void search(std::string targetArtist);
    void inOrder(ArtistBSTNode* curNode);
    void print();
    void delete_node(std::string artist, std::string title);
};
