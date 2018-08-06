/*
 * LinkedList.h
 *
 *  Created on: Jun 19, 2018
 *      Author: dhruvjhamb
 */

#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

#include <iostream>

using namespace std;

class Node {
    friend class LinkedList;
private:
    char value[81] = "\0";    // Size corresponds to maxLineSize
    Node *prev;
    Node *next;
    int valIndex;
    int tempValIndex;
    int valSize;

public:
    Node(Node *p, Node *n);
    ~Node();
};

class LinkedList {
    friend class Node;
private:
	Node *sentinel;
	Node *currentNode;
	Node *tempNode;
	int tempPos;
	int cursorPos;
	int size;
	int maxLineSize = 80;
	bool shifting;

public:
	LinkedList();
	~LinkedList();
	void addChar(char c);
	void shiftChar(char c);
	void addNode(char c, Node *p);
	void addNode();
	void removeChar();
	void removeNode();
	void printList();
	int getSize();
	Node* getCurrentNode();
	int getCursorPos();
	void decreaseIndex();
	void increaseIndex();
	void decreaseCurrentNode();
	void increaseCurrentNode();
	int getMaxLineSize();
	string toString();
};



#endif /* LINKEDLIST_H_ */
