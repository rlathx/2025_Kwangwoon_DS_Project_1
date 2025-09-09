#pragma once
#include "ArtistBSTNode.h"

class ArtistBST {
private:
	ArtistBSTNode* root;
	ArtistBSTNode* parent;
	string data;
	ArtistBSTNode* target;


public:
	ArtistBST();
	~ArtistBST();

};