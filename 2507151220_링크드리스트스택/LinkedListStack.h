#ifndef LINKEDLIST_STACK_H
#define LINKEDLIST_STACK_H
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct tagNode {
	char* Data;
	struct tagNode* NextNode;
	struct tagNode* PrevNode;
} Node;

typedef struct tagLinkedListStack {
	Node* List;
	Node* Top;
	int Count;
} LinkedListStack;

void LLS_CreateStack(LinkedListStack** Stack);
void LLS_DestroyStack(LinkedListStack* Stack);

Node* LLS_CreateNode(char* NewData);
void LLS_DestroyNode(Node* _Node);

void LLS_Push(LinkedListStack* Stack, Node* NewNode);
Node* LLS_Pop(LinkedListStack* Stack);

Node* LLS_Top(LinkedListStack* Stack);
int LLS_GetSize(LinkedListStack* Stack);
int LLS_IsEmpty(LinkedListStack* Stack);


#endif