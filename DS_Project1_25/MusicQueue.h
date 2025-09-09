#pragma once
#include "MusicQueueNode.h"

class MusicQueue {
private:
	MusicQueueNode* head;
	MusicQueueNode* rear;
	int size = 0;
public:
	MusicQueue();
	~MusicQueue();

	bool empty();
	void push();
	MusicQueueNode* pop();
	MusicQueueNode* front();
};