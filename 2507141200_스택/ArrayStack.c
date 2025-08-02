#include "ArrayStack.h"

// ���� 1. ������ ���� á���� �Ǵ��ϴ� �Լ��� ���弼��.
int AS_IsFull(ArrayStack* Stack) {
	return ((Stack->Top) + 1 == Stack->Capacity);	// �뷮�� ���� á�ٸ� true�� ��ȯ
}

// ���� 2. ������ Capacity�� 50���� �����ϰ� while������ Stack�� ������������ 100�� ó�� ������
// ������Ű�鼭 �����ϰ� ������ �������� ���� ����غ�����..

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
// ���ÿ� ���� push�ϴٰ� �뷮�� �����ϸ� �����迭�� �뷮�� 2�� �÷��� ���� �����ϵ���
// ��������..
// �׽�Ʈ �ʱ⿡ �뷮�� 50�� �����ϰ� 100���� �����ؼ� ���� ����غ�����...

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
	// ������ ���� ����ҿ� ����
	(*Stack) = (ArrayStack*)malloc(sizeof(ArrayStack));

	// �Էµ� Capacity��ŭ�� ��带 ���� ����ҿ� ����
	(*Stack)->Nodes = (Node*)malloc(sizeof(Node) * Capacity);

	// Capacity �� Top �ʱ�ȭ
	(*Stack)->Capacity = Capacity;
	(*Stack)->Top = -1;
}

void AS_DestroyStack(ArrayStack* Stack) {
	// ��带 ���� ����ҿ��� ����
	free(Stack->Nodes);

	// ������ ���� ����ҿ��� ����
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