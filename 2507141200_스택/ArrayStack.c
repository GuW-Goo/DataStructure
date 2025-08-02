#include "ArrayStack.h"

// 문제 1. 스택이 가득 찼는지 판단하는 함수를 만드세요.
int AS_IsFull(ArrayStack* Stack) {
	return ((Stack->Top) + 1 == Stack->Capacity);	// 용량이 가득 찼다면 true를 반환
}

// 문제 2. 스택의 Capacity를 50개로 설정하고 while문으로 Stack이 가득찰때까지 100을 처음 값으로
// 증가시키면서 저장하고 스택이 빌때까지 값을 출력해보세요..

int AS_PushNPop(ArrayStack* Stack) {
	int i = 100;
	while (!AS_IsFull(Stack)) {
		AS_Push(Stack, i++);
	}
	while (!AS_IsEmpty(Stack)) {
		printf("Popped: %d\n", AS_Pop(Stack));
	}
}

// extra.
// 스택에 값을 push하다가 용량이 부족하면 동적배열의 용량을 2배 늘려서 값을 저장하도록
// 만들어보세요..
// 테스트 초기에 용량을 50개 설정하고 100개를 저장해서 값을 출력해보세요...

void AS_Push(ArrayStack* Stack, ElementType Data) {

	if (AS_IsFull(Stack)) {
		int Capacity = Stack->Capacity * 2;
		Stack->Nodes = realloc(Stack->Nodes, sizeof(Node) * Capacity);
		Stack->Capacity = Capacity;
	}

	Stack->Top++;
	Stack->Nodes[Stack->Top].Data = Data;
}

void AS_CreateStack(ArrayStack** Stack, int Capacity) {
	// 스택을 자유 저장소에 생성
	(*Stack) = (ArrayStack*)malloc(sizeof(ArrayStack));

	// 입력된 Capacity만큼의 노드를 자유 저장소에 생성
	(*Stack)->Nodes = (Node*)malloc(sizeof(Node) * Capacity);

	// Capacity 및 Top 초기화
	(*Stack)->Capacity = Capacity;
	(*Stack)->Top = -1;
}

void AS_DestroyStack(ArrayStack* Stack) {
	// 노드를 자유 저장소에서 해제
	free(Stack->Nodes);

	// 스택을 자유 저장소에서 해제
	free(Stack);
}

ElementType AS_Pop(ArrayStack* Stack) {
	int Position = Stack->Top--;
	return Stack->Nodes[Position].Data;
}

ElementType AS_Top(ArrayStack* Stack) {
	return Stack->Nodes[Stack->Top].Data;
}

int AS_GetSize(ArrayStack* Stack) {
	return Stack->Top + 1;
}

int AS_IsEmpty(ArrayStack* Stack) {
	return (Stack->Top == -1);
}