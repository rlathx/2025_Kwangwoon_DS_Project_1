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

    bool insert(const std::string artist, const std::string title, const std::string run_time);
    ArtistBSTNode* search(std::string targetArtist);
    void inOrder(ArtistBSTNode* curNode);
    bool print();
    bool delete_node(std::string targetArtist, std::string targetTitle);
};
