#include "DoublyLinkedList.h"
#include "Score.h"
#include "ScoreData.h"


//1. 순차탐색
//순서대로 탐색
//#작동 순서
//탐색할 노드 NULL 확인
//Target Match 되는지 확인
//안되면 다음 -> 찾았으면 return
//끝까지 못 찾았으면 NULL일테니 위에서 거르기
Node* SequntialSearch(Node* Head, double Target)
{
	Node* Temp = Head;
	
	while (1) {
		// 탐색할 노드가 NULL이거나 끝까지 못찾았을 경우
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

// 2. 전진이동법
// Target 매개변수에 전달된 값을 가진 노드를 찾고 해당 노드를 더블링크드 리스트의 맨앞으로 이동시킨다(헤드노드로 만들다.)
Node* MoveToFront(Node** Head, double Target) {
	Node* Temp = (*Head);

	while (Temp != NULL) {
		// TargetMatch
		if (Temp->Data.score == Target) {
			if (Temp == (*Head)) {	// 헤드일 경우
				return Temp;
			}
			else if (Temp->NextNode == NULL) {	// 꼬리일 경우
				Temp->PrevNode->NextNode = NULL;	// 리스트에서 Temp 제거

				// 리스트에 값이 2개인 경우
				if ((*Head)->NextNode == Temp)
					(*Head)->NextNode = NULL;

				// 헤드노드 변경
				Temp->NextNode = (*Head);
				(*Head)->PrevNode = Temp;
				(*Head) = Temp;

				return Temp;
			}
			else {	// 이외일 경우
				Temp->PrevNode->NextNode = Temp->NextNode;	// 리스트에서 Temp 제거
				Temp->NextNode->PrevNode = Temp->PrevNode;

				// 헤드노드 변경
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

//3. 전위법
//한 칸 앞으로
Node* Transpose(Node** Head, double Target)
{
	Node* Temp = (*Head);

	while (Temp != NULL) {
		if (Temp->Data.score == Target) {
			if (Temp == (*Head)) {	// Temp가 헤드일 경우
				return Temp;
			}
			else if (Temp->NextNode == NULL) {	// Temp가 꼬리일 경우
				// 리스트에 값이 2개인지 확인
				if (Temp->PrevNode == (*Head)) {	// 리스트에 값이 2개인 경우
					(*Head)->NextNode = NULL;
					(*Head)->PrevNode = Temp;

					Temp->NextNode = (*Head);
					Temp->PrevNode = NULL;

					(*Head) = Temp;
				}
				else {		// 리스트에 값이 2개보다 많을 경우

					// Temp를 Temp->Prev->Prev(이전이전노드)와 Temp->Prev(이전노드) 사이에 끼워넣기
					Temp->NextNode = Temp->PrevNode;
					Temp->PrevNode = Temp->PrevNode->PrevNode;

					// 리스트에 Temp 연결하기
					Temp->PrevNode->NextNode = Temp;
					Temp->NextNode->PrevNode = Temp;

					//Temp의 Next노드를 꼬리로 만들기
					Temp->NextNode->NextNode = NULL;
				}

				return Temp;
			}
			else if (Temp->PrevNode == (*Head)) {	// Temp가 Head 다음 노드일 경우
				// Head를 Temp와 Temp->Next 사이에 끼워넣기
				(*Head)->NextNode = Temp->NextNode;
				(*Head)->PrevNode = Temp;

				(*Head)->NextNode->PrevNode = (*Head);
				(*Head)->PrevNode->NextNode = (*Head);

				// Temp를 헤드로 만들기
				Temp->NextNode = (*Head);
				(*Head) = Temp;

				return Temp;
			}
			else {	// 이외의 노드일 경우
				// Temp를 리스트에서 제거
				Temp->PrevNode->NextNode = Temp->NextNode;
				Temp->NextNode->PrevNode = Temp->PrevNode;

				// Temp를 Temp이전이전노드와 Temp이전노드 사이에 끼워넣기
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


//4. 계수법
//조회수(탐색횟수)에 따른 이동
Node* FrequencyMethod(Node** Head, double Target)
{
	Node* TargetNode = (*Head);

	// Target을 찾고 찾은 경우 노드를 뽑아옴
	while (TargetNode != NULL) {
		if (TargetNode->Data.score == Target) {
			TargetNode->Frequency++;   // 빈도수 증가

			if (TargetNode == (*Head)) {   // 찾은 노드가 헤드일 경우. 리스트 변경 없이 return
				return TargetNode;
			}
			else if (TargetNode->NextNode == NULL) {   // 노드가 꼬리일 경우
				// TargetNode의 이전노드를 꼬리로 만듦
				TargetNode->PrevNode->NextNode = NULL;

				break;
			}
			else {   // 이외의 노드일 경우
				// TargetNode를 리스트에서 제거
				TargetNode->PrevNode->NextNode = TargetNode->NextNode;
				TargetNode->NextNode->PrevNode = TargetNode->PrevNode;

				break;
			}
		}

		TargetNode = TargetNode->NextNode;
	}

	if (TargetNode == NULL)
		return NULL;

	// Current노드의 Frequency값의 크기에 따라 리스트에 삽입
	Node* Temp = (*Head);

	while (Temp != NULL) {
		if (TargetNode->Frequency > Temp->Frequency) {
			if (Temp == (*Head)) {   // 헤드에 집어넣을 때
				// 헤드 앞에 TargetNode를 연결
				(*Head)->PrevNode = TargetNode;

				// 헤드 변경
				TargetNode->NextNode = (*Head);
				TargetNode->PrevNode = NULL;
				(*Head) = TargetNode;

				return TargetNode;
			}
			else {   // 그 외
				// Temp와 Temp->Prev 사이에 TargetNode를 끼워넣음
				TargetNode->PrevNode = Temp->PrevNode;
				TargetNode->NextNode = Temp;

				TargetNode->PrevNode->NextNode = TargetNode;
				TargetNode->NextNode->PrevNode = TargetNode;

				return TargetNode;			
			}
		}
		
		if (Temp->NextNode == NULL) {	// 빈도수가 증가했음에도 빈도수가 제일 낮은 경우
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

	double InputValue = 0.0;	// 찾는 값(lf)을 저장하는 변수

	int Length = sizeof DataSet / sizeof DataSet[0];
	/*  노드 30,000개 추가 */
	for (i = 0; i < Length; i++)
	{
		NewNode = DLL_CreateNode(DataSet[i]);
		DLL_AppendNode(&List, NewNode);
	}

	//Current = DLL_CreateNode(8000);     // 8000값을 현재 노드로 만든다.
	//DLL_InsertNewHead(&List, Current);  //헤드 노드를 바꾼다.


	while (1) {
		printf("\n찾는 score값을 입력하세요: ");
		scanf_s("%lf", &InputValue);

		if (InputValue < 0.0) {
			printf("찾는 작업을 중단하고 프로그램을 종료합니다.\n");
			break;
		}

		Node* targetNode = FrequencyMethod(&List, InputValue);

		if (targetNode != NULL) {	//찾는 Score값을 가진 노드를 찾은 경우
			printf("MATCH!!! searchValue: number:%d, score: %lf, Frequency: %d\n", targetNode->Data.number, targetNode->Data.score, targetNode->Frequency);
		}
		else {	// 찾는 score값을 가진 노드를 찾지 못함 (값이 없는 경우)
			printf("찾는 값을 가진 노드가 없음!!!\n");
		}

		// 앞에 10개
		for (int i = 0; i < 10; i++) {
			Current = DLL_GetNodeAt(List, i);
			printf("DataSet[%d] number:%d, score: %.4lf, Frequency: %d\n", i, Current->Data.number, Current->Data.score, Current->Frequency);
		}

		printf("===============================================================================\n");

		// 뒤에 10개
		for (int i = Length - 10; i < Length; i++) {
			Current = DLL_GetNodeAt(List, i);
			printf("DataSet[%d] number:%d, score: %.4lf, Frequency: %d\n", i, Current->Data.number, Current->Data.score, Current->Frequency);
		}

	}



	/*  모든 노드를 메모리에서 제거     */
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