#include "LinkedQueue.h"

int main(void)
{
    Node* Popped;
    Node* TempNode = NULL;

    LinkedQueue* Queue;
    LinkedQueue* LeftQueue;
    LinkedQueue* RightQueue;

    LQ_CreateQueue(&Queue);
    LQ_CreateQueue(&LeftQueue);
    LQ_CreateQueue(&RightQueue);

    char data[100];     // 문자열 입력 공간
    int priority = 0;   // 우선 순위 입력용
    int length = 0;     // 큐 길이 저장

    while (1) {
        printf("우선순위 큐에 저장할 데이타를 입력하세요 : ");
        scanf("%d %s", &priority, data);

        if (priority <= -1) break;  // 입력 중단.

        // 입력받은 data를 큐에 저장한다
        LQ_Enqueue(Queue, LQ_CreateNode(priority, data));

        // 우선순위가 낮은 데이터를 뒤로 빼냄
        length = Queue->Count;
        if (length > 1) {    // 큐에 데이터가 2개 이상이면

            // 마지막에 들어온 데이터를 제외한 Queue의 길이만큼 반복
            for (int i = 0; i < length - 1; i++) {
                TempNode = LQ_Dequeue(Queue);
                TempNode->NextNode = NULL;

                // 빼낸 데이터와 큐의 마지막 데이터의 우선순위 비교
                // 크거나 같으면 왼쪽, 작으면 오른쪽에 데이터를 집어넣음
                if (TempNode->priority >= Queue->Rear->priority)
                    LQ_Enqueue(LeftQueue, TempNode);
                else
                    LQ_Enqueue(RightQueue, TempNode);
            }

            // 큐마지막에 남은 데이터를 왼쪽에 집어넣음
            TempNode = LQ_Dequeue(Queue);
            TempNode->NextNode = NULL;
            LQ_Enqueue(LeftQueue, TempNode);

            // Left큐, Right큐를 큐에 합침
            while (!LQ_IsEmpty(LeftQueue)) {    // Queue << LeftQueue
                TempNode = LQ_Dequeue(LeftQueue);
                TempNode->NextNode = NULL;
                LQ_Enqueue(Queue, TempNode);
            }
            while (!LQ_IsEmpty(RightQueue)) {   // Queue << RightQueue
                TempNode = LQ_Dequeue(RightQueue);
                TempNode->NextNode = NULL;
                LQ_Enqueue(Queue, TempNode);
            }
        }
        
        // 큐에 입력된 데이타를 출력
        Node* Current = Queue->Front;   // 헤드노드의 주소값을 Current에 저장

        while (Current != NULL) {
            printf("priority: %d, Data: %s\n", Current->priority, Current->Data);

            Current = Current->NextNode;
        }


    }

    while ( LQ_IsEmpty( Queue ) == 0 )
    {
        Popped = LQ_Dequeue( Queue );

        printf( "Dequeue: %s \n", Popped->Data );

        LQ_DestroyNode( Popped );
    }

    LQ_DestroyQueue( Queue );
    LQ_DestroyQueue( LeftQueue );
    LQ_DestroyQueue( RightQueue );

    return 0;
}