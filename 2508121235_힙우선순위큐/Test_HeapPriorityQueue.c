#include "HeapPriorityQueue.h"

void PrintNode(PQNode* Node)
{
    printf("작업명 : %s (우선순위:%d)\n", Node->Data, Node->Priority);
}

int main(void)
{
    PriorityQueue* PQ = PQ_Create(3);
    PQNode Popped;

    PQNode Nodes[7] =
    {
        {34, (void*)"코딩"},
        {12, (void*)"고객미팅"},
        {87, (void*)"커피타기"},
        {45, (void*)"문서작성"},
        {35, (void*)"디버깅"},
        {66, (void*)"이닦기"}
    };

    for(int i = 0; i < sizeof(Nodes) / sizeof(Nodes[0]); i++) {
        PQ_Enqueue(PQ, Nodes[i]);
    }

    printf("큐에 남아 있는 작업의 수 : %d\n", PQ->UsedSize);

    while (!PQ_IsEmpty(PQ))
    {
        PQ_Dequeue(PQ, &Popped);
        PrintNode(&Popped);
    }

    PQ_Destroy(PQ);

    return 0;
}
