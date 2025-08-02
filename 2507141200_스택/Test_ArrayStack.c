#include "ArrayStack.h"

int main() {
	int i = 0;
	ArrayStack* Stack = NULL;

	AS_CreateStack(&Stack, 10);

	AS_Push(Stack, 3);
	AS_Push(Stack, 37);
	AS_Push(Stack, 11);
	AS_Push(Stack, 12);

	printf("Stack isFull: %d\n\n", AS_IsFull(Stack));

	printf("Capacity: %d, Size: %d, Top: %d\n\n", Stack->Capacity, AS_GetSize(Stack), AS_Top(Stack));

	for (int i = 0; i < 4; i++) {
		if (AS_IsEmpty(Stack)) {
			break;
		}

		printf("Popped: %d, ", AS_Pop(Stack));
		if (!AS_IsEmpty(Stack))
			printf("Current Top: %d\n", AS_Top(Stack));
		else
			printf("Stack Is Enpty.\n");
	}

	AS_DestroyStack(Stack);

	printf("\n");

	ArrayStack* Stack2 = NULL;
	AS_CreateStack(&Stack2, 50);

	for (int i = 0; i < 100; i++) {
		AS_Push(Stack2, i);
	}
	for (int i = 0; i < 100; i++) {
		printf("Popped: %d\n", AS_Pop(Stack2));
	}
	AS_DestroyStack(Stack2);

	return 0;
}