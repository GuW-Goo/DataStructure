#include "DoublyLinkedList.h"
#include "Score.h"
#include "ScoreData.h"


//1. ����Ž��
//������� Ž��
//#�۵� ����
//Ž���� ��� NULL Ȯ��
//Target Match �Ǵ��� Ȯ��
//�ȵǸ� ���� -> ã������ return
//������ �� ã������ NULL���״� ������ �Ÿ���
Node* SequntialSearch(Node* Head, double Target)
{
	Node* Temp = Head;
	
	while (1) {
		// Ž���� ��尡 NULL�̰ų� ������ ��ã���� ���
		if (Temp == NULL) {	
			return NULL;
		}
		// TargetMatch
		if (Temp->Data.score == Target) {	
			return Temp;
		}

		Temp = Temp->NextNode;
	}
}

// 2. �����̵���
// Target �Ű������� ���޵� ���� ���� ��带 ã�� �ش� ��带 ����ũ�� ����Ʈ�� �Ǿ����� �̵���Ų��(������ �����.)
Node* MoveToFront(Node** Head, double Target) {
	Node* Temp = (*Head);

	while (Temp != NULL) {
		// TargetMatch
		if (Temp->Data.score == Target) {
			if (Temp == (*Head)) {	// ����� ���
				return Temp;
			}
			else if (Temp->NextNode == NULL) {	// ������ ���
				Temp->PrevNode->NextNode = NULL;	// ����Ʈ���� Temp ����

				// ����Ʈ�� ���� 2���� ���
				if ((*Head)->NextNode == Temp)
					(*Head)->NextNode = NULL;

				// ����� ����
				Temp->NextNode = (*Head);
				(*Head)->PrevNode = Temp;
				(*Head) = Temp;

				return Temp;
			}
			else {	// �̿��� ���
				Temp->PrevNode->NextNode = Temp->NextNode;	// ����Ʈ���� Temp ����
				Temp->NextNode->PrevNode = Temp->PrevNode;

				// ����� ����
				Temp->NextNode = (*Head);
				(*Head)->PrevNode = Temp;
				(*Head) = Temp;

				return Temp;
			}
		}

		Temp = Temp->NextNode;
	}

	return NULL;
}

//3. ������
//�� ĭ ������
Node* Transpose(Node** Head, double Target)
{
	Node* Temp = (*Head);

	while (Temp != NULL) {
		if (Temp->Data.score == Target) {
			if (Temp == (*Head)) {	// Temp�� ����� ���
				return Temp;
			}
			else if (Temp->NextNode == NULL) {	// Temp�� ������ ���
				// ����Ʈ�� ���� 2������ Ȯ��
				if (Temp->PrevNode == (*Head)) {	// ����Ʈ�� ���� 2���� ���
					(*Head)->NextNode = NULL;
					(*Head)->PrevNode = Temp;

					Temp->NextNode = (*Head);
					Temp->PrevNode = NULL;

					(*Head) = Temp;
				}
				else {		// ����Ʈ�� ���� 2������ ���� ���

					// Temp�� Temp->Prev->Prev(�����������)�� Temp->Prev(�������) ���̿� �����ֱ�
					Temp->NextNode = Temp->PrevNode;
					Temp->PrevNode = Temp->PrevNode->PrevNode;

					// ����Ʈ�� Temp �����ϱ�
					Temp->PrevNode->NextNode = Temp;
					Temp->NextNode->PrevNode = Temp;

					//Temp�� Next��带 ������ �����
					Temp->NextNode->NextNode = NULL;
				}

				return Temp;
			}
			else if (Temp->PrevNode == (*Head)) {	// Temp�� Head ���� ����� ���
				// Head�� Temp�� Temp->Next ���̿� �����ֱ�
				(*Head)->NextNode = Temp->NextNode;
				(*Head)->PrevNode = Temp;

				(*Head)->NextNode->PrevNode = (*Head);
				(*Head)->PrevNode->NextNode = (*Head);

				// Temp�� ���� �����
				Temp->NextNode = (*Head);
				(*Head) = Temp;

				return Temp;
			}
			else {	// �̿��� ����� ���
				// Temp�� ����Ʈ���� ����
				Temp->PrevNode->NextNode = Temp->NextNode;
				Temp->NextNode->PrevNode = Temp->PrevNode;

				// Temp�� Temp������������ Temp������� ���̿� �����ֱ�
				Temp->NextNode = Temp->PrevNode;
				Temp->PrevNode = Temp->PrevNode->PrevNode;

				Temp->PrevNode->NextNode = Temp;
				Temp->NextNode->PrevNode = Temp;

				return Temp;
			}
		}

		Temp = Temp->NextNode;
	}


	return NULL;
}


//4. �����
//��ȸ��(Ž��Ƚ��)�� ���� �̵�
Node* FrequencyMethod(Node** Head, double Target)
{
	Node* TargetNode = (*Head);

	// Target�� ã�� ã�� ��� ��带 �̾ƿ�
	while (TargetNode != NULL) {
		if (TargetNode->Data.score == Target) {
			TargetNode->Frequency++;   // �󵵼� ����

			if (TargetNode == (*Head)) {   // ã�� ��尡 ����� ���. ����Ʈ ���� ���� return
				return TargetNode;
			}
			else if (TargetNode->NextNode == NULL) {   // ��尡 ������ ���
				// TargetNode�� ������带 ������ ����
				TargetNode->PrevNode->NextNode = NULL;

				break;
			}
			else {   // �̿��� ����� ���
				// TargetNode�� ����Ʈ���� ����
				TargetNode->PrevNode->NextNode = TargetNode->NextNode;
				TargetNode->NextNode->PrevNode = TargetNode->PrevNode;

				break;
			}
		}

		TargetNode = TargetNode->NextNode;
	}

	if (TargetNode == NULL)
		return NULL;

	// Current����� Frequency���� ũ�⿡ ���� ����Ʈ�� ����
	Node* Temp = (*Head);

	while (Temp != NULL) {
		if (TargetNode->Frequency > Temp->Frequency) {
			if (Temp == (*Head)) {   // ��忡 ������� ��
				// ��� �տ� TargetNode�� ����
				(*Head)->PrevNode = TargetNode;

				// ��� ����
				TargetNode->NextNode = (*Head);
				TargetNode->PrevNode = NULL;
				(*Head) = TargetNode;

				return TargetNode;
			}
			else {   // �� ��
				// Temp�� Temp->Prev ���̿� TargetNode�� ��������
				TargetNode->PrevNode = Temp->PrevNode;
				TargetNode->NextNode = Temp;

				TargetNode->PrevNode->NextNode = TargetNode;
				TargetNode->NextNode->PrevNode = TargetNode;

				return TargetNode;			
			}
		}
		
		if (Temp->NextNode == NULL) {	// �󵵼��� ������������ �󵵼��� ���� ���� ���
			Temp->NextNode = TargetNode;
			TargetNode->PrevNode = Temp;
			TargetNode->NextNode = NULL;

			return TargetNode;
		}

		Temp = Temp->NextNode;
	}
}


int main(void)
{
	int   i = 0;
	int   Count = 0;
	Node* List = NULL;
	Node* NewNode = NULL;
	Node* Current = NULL;

	double InputValue = 0.0;	// ã�� ��(lf)�� �����ϴ� ����

	int Length = sizeof DataSet / sizeof DataSet[0];
	/*  ��� 30,000�� �߰� */
	for (i = 0; i < Length; i++)
	{
		NewNode = DLL_CreateNode(DataSet[i]);
		DLL_AppendNode(&List, NewNode);
	}

	//Current = DLL_CreateNode(8000);     // 8000���� ���� ���� �����.
	//DLL_InsertNewHead(&List, Current);  //��� ��带 �ٲ۴�.


	while (1) {
		printf("\nã�� score���� �Է��ϼ���: ");
		scanf_s("%lf", &InputValue);

		if (InputValue < 0.0) {
			printf("ã�� �۾��� �ߴ��ϰ� ���α׷��� �����մϴ�.\n");
			break;
		}

		Node* targetNode = FrequencyMethod(&List, InputValue);

		if (targetNode != NULL) {	//ã�� Score���� ���� ��带 ã�� ���
			printf("MATCH!!! searchValue: number:%d, score: %lf, Frequency: %d\n", targetNode->Data.number, targetNode->Data.score, targetNode->Frequency);
		}
		else {	// ã�� score���� ���� ��带 ã�� ���� (���� ���� ���)
			printf("ã�� ���� ���� ��尡 ����!!!\n");
		}

		// �տ� 10��
		for (int i = 0; i < 10; i++) {
			Current = DLL_GetNodeAt(List, i);
			printf("DataSet[%d] number:%d, score: %.4lf, Frequency: %d\n", i, Current->Data.number, Current->Data.score, Current->Frequency);
		}

		printf("===============================================================================\n");

		// �ڿ� 10��
		for (int i = Length - 10; i < Length; i++) {
			Current = DLL_GetNodeAt(List, i);
			printf("DataSet[%d] number:%d, score: %.4lf, Frequency: %d\n", i, Current->Data.number, Current->Data.score, Current->Frequency);
		}

	}



	/*  ��� ��带 �޸𸮿��� ����     */
	printf("\nDestroying List...\n");

	Count = DLL_GetNodeCount(List);

	for (i = 0; i < Count; i++)
	{
		Current = DLL_GetNodeAt(List, 0);

		if (Current != NULL)
		{
			DLL_RemoveNode(&List, Current);
			DLL_DestroyNode(Current);
		}
	}

	return 0;
}