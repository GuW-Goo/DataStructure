#include "LinkedList.h"
#include <string.h>

char NUMBER[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };

// char�� �ִ� Data�� �������� Ȯ��
int   IsNumber(char Cipher)
{
    int i = 0;
    int ArrayLength = sizeof(NUMBER);

    for (i = 0; i < ArrayLength; i++)
    {
        if (Cipher == NUMBER[i])
            return 1;
    }

    return 0;
}

// ���ڷθ� �̷���� ����Ʈ���� Ȯ��, �������Խ� : 0�� ����
int   ListIsNumbers(Node* Head) {    
    Node* Temp = Head;

    while (Temp != NULL) {
        if (IsNumber(Temp->Data) == 0)    // Data�� ���ڸ� return 0
            return 0;

        Temp = Temp->NextNode;
    }

    return 1;
}

// ����Ʈ ���� (�޸� �ݳ�)
void  SLL_DestoyList(Node* Head) {
    Node* Current = NULL;
    int Length = SLL_GetNodeCount(Head);

    for (int i = 0; i < Length; i++)
    {
        Current = SLL_GetNodeAt(Head, 0);

        if (Current != NULL)
        {
            SLL_RemoveNode(&Head, Current);
            SLL_DestroyNode(Current);
        }
    }
}

// ����Ʈ ���
void  PrintList(Node* Head) {
    Node* Temp = Head;

    while (Temp != NULL) {
        printf("%c", Temp->Data);
        Temp = Temp->NextNode;
    }
}

// ���� ����Ʈ ����
void  MakeAnswer(Node* AnswerList) {
    Node* Temp = NULL;

    printf("���� ������...\n");  

     do {   // ������ �ߺ� ����
        Temp = AnswerList;
        while (Temp != NULL) {
            Temp->Data = rand() % 9 + 48;   // 0 ~ 9 ������ ������ ���ڸ� ���ڷ� ��ȯ�Ͽ� ����
            Temp = Temp->NextNode;
        }
     } while (IsDuplicate(AnswerList));

    printf("���� �����Ϸ�\n\n");
}

// ����Ʈ���� �ߺ����� �ִ��� Ȯ��. �ߺ� : 1
int   IsDuplicate(Node* Head) {   
    Node* Temp = Head;
    Node* Temp2 = NULL;

    while (Temp != NULL) {
        Temp2 = Temp->NextNode;

        while (Temp2 != NULL) {
            if (Temp->Data == Temp2->Data)
                return 1;

            Temp2 = Temp2->NextNode;
        }

        Temp = Temp->NextNode;
    }

    return 0;
}

// ���丮��Ʈ�� ��������Ʈ ���ϴ� �Լ� 
// xByC ���·� ���� (x, y : ����)
char* IsCorrect(Node* AnswerList, Node* UserList) { 
    Node* tempAnswerList = AnswerList;
    Node* tempUserList = UserList;

    int bulls = 0;
    int cows = 0;
    int userListIndex = 0, answerListIndex = 0;

    char result[5] = "0B0C";

    while (tempUserList != NULL) {
        
        tempAnswerList = AnswerList;
        answerListIndex = 0;

        while (tempAnswerList != NULL) {

            // ���丮��Ʈ�� ��������Ʈ���� ���� ���ڸ� ã��
            if (tempAnswerList->Data == tempUserList->Data) {
                if (userListIndex == answerListIndex)   // 1. ������ ��ġ�� ���ٸ�
                    bulls++;
                else    // 2. ������ ��ġ�� �ٸ���
                    cows++;

                break;
            }
            
            tempAnswerList = tempAnswerList->NextNode;
            answerListIndex++;
        }
        
        tempUserList = tempUserList->NextNode;
        userListIndex++;
    }

    result[0] = bulls + 48; // ���ڸ� ���ڷ� �ٲ� ���ڿ��� ����
    result[2] = cows + 48;

    return result;
}

// �Է¹��� ����
void ClearInputBuffer() {
    int ch;
    while((ch = getchar()) != '\n' && ch != EOF) { }
}

int main() {
    srand(time(NULL));

    Node* AnswerList = NULL;    // ������ ������ ����Ʈ�� �����
    Node* UserList = NULL;      // ������ �Է��� ����Ʈ�� �����
    Node* NewNode = NULL;
    Node* TempList = NULL;

    int maxCount = 10;      // ������߱� �õ� Ƚ�� (10�̸� 10�� �õ��� �� ����)
    int isFind = 0;
    int isPlay = 1;
    int count = 0;

    char result[5];         // Bulls�� Cows ������ ���� ���ڿ�
    char userNumbers[10];   // user���� �Է¹��� ����

    // ���� List ����
    for (int i = 0; i < 4; i++) {           
        NewNode = SLL_CreateNode(0);
        SLL_AppendNode(&AnswerList, NewNode);
    }

    while (isPlay) {
        // ���ο� ���� ����
        MakeAnswer(AnswerList);
        isFind = 0;

        for (count = 1; count <= maxCount; count++) {
           
            printf("���� 4���� �Է��ϼ���: ");
            scanf_s("%s", userNumbers, sizeof(userNumbers));
            ClearInputBuffer();

            // User�� �Է��� ���ڸ� UserList�� ����
            for (int i = 0; i < sizeof(userNumbers); i++) { // ���ڿ����� ���� 1���� UserList�� ������
                if (userNumbers[i] == '\0') {
                    break;
                }

                NewNode = SLL_CreateNode(userNumbers[i]);
                SLL_AppendNode(&UserList, NewNode);
            }

            // ���ڰ� n�ڸ� ������ Ȯ��
            if (SLL_GetNodeCount(UserList) != 4) {
                printf("���ڰ� 4�ڸ��� �ƴմϴ�.\n\n");

                SLL_DestoyList(UserList);   // ���� ����Ʈ ����
                UserList = NULL;
                count--;

                continue;
            }
            // ���ڿ� ���ڰ� ���ԵǾ��ִ��� Ȯ��
            if (ListIsNumbers(UserList) == 0) {
                printf("���ڰ� �ƴ� ���� �����ֽ��ϴ�. \n\n");
                
                SLL_DestoyList(UserList);   // ���� ����Ʈ ����
                UserList = NULL;
                count--;

                continue;
            }
            // �Է¹��� ���ڿ� �ߺ��� ���ڰ� �ִ��� Ȯ��
            if (IsDuplicate(UserList)) {
                printf("�ߺ��� ���ڰ� �����ֽ��ϴ�. \n\n");

                SLL_DestoyList(UserList);   // ���� ����Ʈ ����
                UserList = NULL;
                count--;

                continue;
            }

            // Computer�� ���ڿ� User�� ���� ��
            strcpy_s(result, sizeof(char) * 5, IsCorrect(AnswerList, UserList));
            if (strcmp(result, "4B0C") == 0) { // 4B0C�� ��� ���� ����
                isFind = 1;
                break;
            }

            SLL_DestoyList(UserList);   // ���� ����Ʈ ����
            UserList = NULL;

            printf("�Է��� Ƚ�� : %d result : %s \n\n", count, result);
        }

        if (isFind == 1) {
            printf("�����Դϴ�. �� �Է��� Ƚ��: %d, ���� : ", count);
            PrintList(AnswerList);
        }
        else {
            printf("Game Over.. ���� : ");
            PrintList(AnswerList);
        }

        while (1) {
            printf("\n\n�ٽ� �÷��� �Ͻðڽ��ϱ�? (0: ����, 1: �ٽý���): ");
            scanf_s("%d", &isPlay);
            if (isPlay == 0 || isPlay == 1)
                break;

            printf("0 �Ǵ� 1�� �Է����ּ���..");
        }
    }
    
    printf("\n������ �����մϴ�. \n\n");
    printf("��ũ�帮��Ʈ ������...\n");

    SLL_DestoyList(AnswerList);

    printf("��ũ�帮��Ʈ ���ſϷ�.\n");

    return 0;
}