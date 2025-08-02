#include "LinkedList.h"
#include "Score.h"
#include "ScoreData.h"

// 1. ����Ž��
// �̱۸�ũ�� ����Ʈ�� ����� 3������ ����Ÿ �ȿ��� Target�Ű������� ���޵� ���� ���� ��带 ã��
// �ش� ����� �ּҰ��� �����Ѵ�.
Node* SequentialSearch(Node* Head, double Target) {
	Node* Temp = Head;
	while (Temp != NULL) {
		if (Temp->Data.score == Target)
			return Temp;
		else
			Temp = Temp->NextNode;
	}
	return NULL;
}


// 2. �����̵���
// Target �Ű������� ���޵� ���� ���� ��带 ã�� �ش� ��带 �̱۸�ũ�� ����Ʈ�� �Ǿ����� �̵���Ų��(������ �����.)
Node* MoveToFront(Node** Head, double Target) {
	if (Head == NULL)
		return NULL;
	if ((*Head)->Data.score == Target) {
		return (*Head);
	}

	Node* PrevNode = (*Head);
	Node* TargetNode = (*Head)->NextNode;
	
	while (TargetNode != NULL) {
		if (TargetNode->Data.score == Target) {

			PrevNode->NextNode = TargetNode->NextNode;
			TargetNode->NextNode = (*Head);
			(*Head) = TargetNode;
			
			return TargetNode;
		}
		else {
			PrevNode = TargetNode;
			TargetNode = TargetNode->NextNode;
		}
	}

	return NULL;
}

// 3. ������
// Target �Ű������� ���޵� ���� ���� ��带 ã�� �ش� ��带 �̱۸�ũ�� ����Ʈ����
// ã�� ��带 ��ĭ �������� �̵���Ų��.
Node* Transpose(Node** Head, double Target) {
	if (Head == NULL)
		return NULL;
	if ((*Head)->Data.score == Target) {
		return (*Head);
	}

	Node* TargetNode = (*Head)->NextNode;
	Node* PrevNode = (*Head);
	Node* PrevNode2 = NULL;

	while (TargetNode != NULL) {

		if (TargetNode->Data.score == Target) {

			if (PrevNode2 != NULL) {
				PrevNode->NextNode = TargetNode->NextNode;
				PrevNode2->NextNode = TargetNode;
				TargetNode->NextNode = PrevNode;
			}
			else {
				PrevNode->NextNode = TargetNode->NextNode;
				TargetNode->NextNode = PrevNode;
				(*Head) = TargetNode;
			}

			return TargetNode;
		}
		else {
			PrevNode2 = PrevNode;
			PrevNode = TargetNode;
			TargetNode = TargetNode->NextNode;
		}
	}

	return NULL;
}


// 4. �����
// Node�� �󵵼�(Frequency)�� �����ϴ� ������ �����
// Target�� ���޵� ���� ���� ��带 ã�� �� �󵵼��� ������Ű��
// �󵵼��� ũ�⸦ ���Ͽ� �ش� ��带 ��ġ ��Ų��.
Node* FrequencyMethod(Node** Head, double Target) {
	Node* TargetNode = (*Head);
	Node* PrevNode = NULL;

	while (TargetNode != NULL) {	// Target ã��
		if (TargetNode->Data.score == Target) {
			TargetNode->Frequency++;

			if (PrevNode != NULL) {	// head�� �ƴѰ��
				PrevNode->NextNode = TargetNode->NextNode;	// TargetNode �̾ƿ���
			}

			break;
		}
		else {
			PrevNode = TargetNode;
			TargetNode = TargetNode->NextNode;
		}
	}

	if (TargetNode != NULL) {		// Frequency���� �´� ��ġ�� ����
		Node* TempNode = (*Head);
		PrevNode = NULL;

		while (1) {
			if (TargetNode->Frequency > TempNode->Frequency) {
				if (TargetNode == (*Head))
					return TargetNode;

				if (PrevNode != NULL) {
					PrevNode->NextNode = TargetNode;
				}
				else {	// TargetNode�� �� ��ġ�� head�� ��� head ����
					(*Head) = TargetNode;
				}
				TargetNode->NextNode = TempNode;

				return TargetNode;
			}
			else {
				PrevNode = TempNode;
				TempNode = TempNode->NextNode;
			}
		}
	}
	
	return NULL;
}

int main(void)
{
	int   i = 0;
	int   Count = 0;
	Node* List = NULL;  // ������ּҰ��� ����
	Node* Current = NULL;
	Node* NewNode = NULL;

	double InputValue = 0.0;	// ã�� ���� �����ϴ� ����

	int Length = sizeof(DataSet) / sizeof(Score);	// DataSet �迭����� ���� (30000��)

	//  ��� 30000�� �߰� 
	for (i = 0; i < Length; i++)
	{
		NewNode = SLL_CreateNode(DataSet[i]);
		SLL_AppendNode(&List, NewNode);
	}

	// ã�� ���� ã�� �ݺ�����
	while (1) {
		printf("\nã�� score���� �Է��ϼ���: ");
		scanf_s("%lf", &InputValue);

		if (InputValue < 0.0) {
			printf("ã�� �۾��� �ߴ��ϰ� ���α׷��� �����մϴ�.\n");
			break;
		}	

		Node* targetNode = FrequencyMethod(&List, InputValue);

		if (targetNode != NULL) {	// ã�� score���� ���� ��带 ã�� ���
			printf("MATCH!!!! searchValue Frequency : %d number: %d, score: %lf\n", 
				targetNode->Frequency, targetNode->Data.number, targetNode->Data.score);
		}
		else {	// ã�� score���� ���� ��带 �� ã�� ���
			printf("ã�� ���� ���� ��尡 ����!!!!\n");
		}

		// �տ� 10��
		for (int i = 0; i < 10; i++) {
			Current = SLL_GetNodeAt(List, i);
			printf("DataSet[%d] Frequency : %d Number: %d, Score: %.4lf\n",
				i, Current->Frequency, Current->Data.number, Current->Data.score);
		}

		printf("===============================================\n");

		for (int i = Length - 10; i < Length; i++) {
			Current = SLL_GetNodeAt(List, i);
			printf("DataSet[%d] Frequency : %d Number: %d, Score: %.4lf\n",
				i, Current->Frequency, Current->Data.number, Current->Data.score);
		}

	}



	//  ��� ��带 �޸𸮿��� ����     
	printf("\nDestroying List...\n");

	for (i = 0; i < Count; i++)
	{
		Current = SLL_GetNodeAt(List, 0);

		if (Current != NULL)
		{
			SLL_RemoveNode(&List, Current);
			SLL_DestroyNode(Current);
		}
	}

	return 0;
}
