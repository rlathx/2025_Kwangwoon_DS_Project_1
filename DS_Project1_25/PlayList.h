#pragma once
#include "PlayListNode.h"

class PlayList {
private:
	PlayListNode* head;
	PlayListNode* cursor;
	int count;
	int time;
	string data;

public:
	PlayList() {}
	~PlayList(){}
	
};