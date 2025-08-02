#include "LinkedList.h"
#include <string.h>

char NUMBER[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };

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

int   StringIsNumbers(char* Numbers) {    // ���ڷ� �̷���� ���ڿ����� Ȯ��, �������Խ� : 0�� ����
    for (int i = 0; Numbers[i] != '\0'; i++) {
        if (IsNumber(Numbers[i]) == 0)
            return 0;
    }
    return 1;
}

void  MakeAnswer(Node* AnswerList) {
    Node* Temp = NULL;

    printf("���� ������...\n");  // ������ �ߺ� ����

     do {
        Temp = AnswerList;
        while (Temp != NULL) {
            Temp->Data = rand() % 9 + 48;
            Temp = Temp->NextNode;
        }
     } while (IsDuplicate(AnswerList));

    printf("���� �����Ϸ�\n\n");
}

int   IsDuplicate(Node* List) {   // ����Ʈ���� �ߺ����� �ִ��� Ȯ��. �ߺ� : 1
    Node* Temp = List;
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

char* IsCorrect(Node* AnswerList, Node* UserList) { // xByC ���·� ���� (x, y : ����)
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
            if (tempAnswerList->Data == tempUserList->Data) {
                if (userListIndex == answerListIndex)
                    bulls++;
                else
                    cows++;

                break;
            }

            answerListIndex++;
            tempAnswerList = tempAnswerList->NextNode;
        }

        userListIndex++;
        tempUserList = tempUserList->NextNode;
    }

    result[0] = bulls + 48;
    result[2] = cows + 48;

    return result;
}

int main() {
    srand(time(NULL));

    Node* AnswerList = NULL;    // ������ ������ ����Ʈ�� �����
    Node* UserList = NULL;      // ������ּҰ��� ����
    Node* NewNode = NULL;

    int maxCount = 10;  // ������߱� �õ� Ƚ�� (10�̸� 10�� �õ��� �� ����)
    int isFind = 0;
    int isPlay = 1;
    int count = 0;
    int i = 0;

    char result[5];       // Bulls�� Cows ������ ���� ���ڿ�
    char userNumbers[10]; // user���� �Է¹��� ����

    for (i = 0; i < 4; i++) {           // ���� List ����
        NewNode = SLL_CreateNode(0);
        SLL_AppendNode(&AnswerList, NewNode);
    }

    for (i = 0; i < 4; i++) {           // User List ����
        NewNode = SLL_CreateNode(0);
        SLL_AppendNode(&UserList, NewNode);
    }

    while (isPlay) {
        MakeAnswer(AnswerList); // �������
        isFind = 0;

        for (count = 1; count <= maxCount; count++) {  // User ���� �Է�
           
            printf("���� 4���� �Է��ϼ���: ");
            scanf_s("%s", userNumbers, sizeof(userNumbers));

            if (strlen(userNumbers) != 4) {
                printf("���ڰ� 4�ڸ��� �ƴմϴ�.\n\n");
                count--;
                continue;
            }
            if (StringIsNumbers(userNumbers) == 0) {
                printf("���ڰ� �ƴ� ���� �����ֽ��ϴ�. \n\n");
                count--;
                continue;
            }

            Node* TempList = UserList;    // User�� �Է��� ���ڸ� UserList�� ����
            i = 0;
            while (TempList != NULL) {
                TempList->Data = userNumbers[i++];
                TempList = TempList->NextNode;
            }

            if (IsDuplicate(UserList)) {
                printf("�ߺ��� ���ڰ� �����ֽ��ϴ�. \n\n");
                count--;
                continue;
            }

            // Computer�� ���ڿ� User�� ���� ��
            strcpy_s(result, sizeof(char) * 5, IsCorrect(AnswerList, UserList));
            if (result[0] == '4') {
                isFind = 1;
                break;
            }

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
    SLL_DestoyList(UserList);

    printf("��ũ�帮��Ʈ ���ſϷ�.\n");

    return 0;
}