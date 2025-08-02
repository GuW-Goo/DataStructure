#include "DoublyLinkedList.h"

unsigned int  Count = 0;

//  노드 생성 
Node* DLL_CreateNode( ElementType NewData )
{
    Node* NewNode = (Node*)malloc(sizeof(Node));

    NewNode->Data = NewData;
    NewNode->PrevNode = NULL;
    NewNode->NextNode = NULL;

    return NewNode;
}

//  노드 소멸 
void DLL_DestroyNode( Node* Node )
{
    free(Node);
}

//  노드 추가 
void DLL_AppendNode( Node** Head, Node* NewNode )
{
    //  헤드 노드가 NULL이라면 새로운 노드가 Head 
    if ( (*Head) == NULL ) 
    {
        *Head = NewNode;
    } 
    else
    {
        //  테일을 찾아 NewNode를 연결한다. 
        Node* Tail = (*Head);
        while ( Tail->NextNode != NULL )
        {
            Tail = Tail->NextNode;
        }

        Tail->NextNode = NewNode;
        NewNode->PrevNode = Tail; //  기존의 테일을 새로운 테일의 PrevNode가 가리킨다. 
    }
    Count++;
}

//  노드 삽입 
void DLL_InsertAfter( Node* Current, Node* NewNode )
{
    NewNode->NextNode = Current->NextNode;
    NewNode->PrevNode = Current;

    if ( Current->NextNode != NULL )
    {
        Current->NextNode->PrevNode = NewNode;
        Current->NextNode = NewNode;
    }
    Count++;
}

//  노드 제거 
void DLL_RemoveNode( Node** Head, Node* Remove )
{
    if ( *Head == Remove )
    {
        *Head = Remove->NextNode;
        if ( (*Head) != NULL )
            (*Head)->PrevNode = NULL;
        
        Remove->PrevNode = NULL;
        Remove->NextNode = NULL;
    }
    else
    {
        Node* Temp = Remove;

        if ( Remove->PrevNode != NULL )
            Remove->PrevNode->NextNode = Temp->NextNode;

        if ( Remove->NextNode != NULL )
            Remove->NextNode->PrevNode = Temp->PrevNode;

        Remove->PrevNode = NULL;
        Remove->NextNode = NULL;
    }  
    Count--;
}

//  노드 탐색 
Node* DLL_GetNodeAt( Node* Head, int Location )
{
    Node* Current = Head;

    while ( Current != NULL && (--Location) >= 0)
    {
        Current = Current->NextNode;
    }

    return Current;
}

// 문제 2.
/*
    DLL_GetNodeCount 함수는 노드의 갯수를 리턴해주는 함수입니다.
    그런데 노드의 갯수를 세기 위해서 매번 헤드 노드에서부터 꼬리노드까지
    count를 합니다.
    이 비효율적인 문제를 해결해보세요.
*/

//  노드 개수 세기 
int DLL_GetNodeCount()
{
    return Count;
}

// 문제 1.
/*
    더블링크드 리스트에는 InsertNewHead 함수가 없습니다.
    InsertNewHead 함수는 헤드노드를 변경하는 함수입니다.
    더블링크드 리스트에서 작동하는 InsertNewHead 함수를 만들고
    새로운 노드를 만들어서 값을 6000을 입력하고 새로운 노드를 Head 노드로 만들고 리스트
    출력해보세요.
*/

void DLL_InsertNewHead( Node** Head, Node* NewHead ) {

    if (*Head == NULL)
    {
        (*Head) = NewHead;
    }
    else
    {
        NewHead->NextNode = (*Head);
        (*Head)->PrevNode = NewHead;
        (*Head) = NewHead;
    }

    Count++;
}

void PrintNode( Node* _Node )
{
    if ( _Node->PrevNode == NULL )
        printf("Prev: NULL");
    else
        printf("Prev: %d", _Node->PrevNode->Data);

    printf(" Current: %d ", _Node->Data);

    if ( _Node->NextNode == NULL )
        printf("Next: NULL\n");
    else
        printf("Next: %d\n", _Node->NextNode->Data);
}
