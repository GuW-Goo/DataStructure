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

    char data[100];     // ���ڿ� �Է� ����
    int priority = 0;   // �켱 ���� �Է¿�
    int length = 0;     // ť ���� ����

    while (1) {
        printf("�켱���� ť�� ������ ����Ÿ�� �Է��ϼ��� : ");
        scanf("%d %s", &priority, data);

        if (priority <= -1) break;  // �Է� �ߴ�.

        // �Է¹��� data�� ť�� �����Ѵ�
        LQ_Enqueue(Queue, LQ_CreateNode(priority, data));

        // �켱������ ���� �����͸� �ڷ� ����
        length = Queue->Count;
        if (length > 1) {    // ť�� �����Ͱ� 2�� �̻��̸�

            // �������� ���� �����͸� ������ Queue�� ���̸�ŭ �ݺ�
            for (int i = 0; i < length - 1; i++) {
                TempNode = LQ_Dequeue(Queue);
                TempNode->NextNode = NULL;

                // ���� �����Ϳ� ť�� ������ �������� �켱���� ��
                // ũ�ų� ������ ����, ������ �����ʿ� �����͸� �������
                if (TempNode->priority >= Queue->Rear->priority)
                    LQ_Enqueue(LeftQueue, TempNode);
                else
                    LQ_Enqueue(RightQueue, TempNode);
            }

            // ť�������� ���� �����͸� ���ʿ� �������
            TempNode = LQ_Dequeue(Queue);
            TempNode->NextNode = NULL;
            LQ_Enqueue(LeftQueue, TempNode);

            // Leftť, Rightť�� ť�� ��ħ
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
        
        // ť�� �Էµ� ����Ÿ�� ���
        Node* Current = Queue->Front;   // ������� �ּҰ��� Current�� ����

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