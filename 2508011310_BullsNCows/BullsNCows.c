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

int   StringIsNumbers(char* Numbers) {    // 숫자로 이루어진 문자열인지 확인, 문자포함시 : 0을 리턴
    for (int i = 0; Numbers[i] != '\0'; i++) {
        if (IsNumber(Numbers[i]) == 0)
            return 0;
    }
    return 1;
}

void  MakeAnswer(Node* AnswerList) {
    Node* Temp = NULL;

    printf("정답 생성중...\n");  // 정답의 중복 제거

     do {
        Temp = AnswerList;
        while (Temp != NULL) {
            Temp->Data = rand() % 9 + 48;
            Temp = Temp->NextNode;
        }
     } while (IsDuplicate(AnswerList));

    printf("정답 생성완료\n\n");
}

int   IsDuplicate(Node* List) {   // 리스트내에 중복값이 있는지 확인. 중복 : 1
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

char* IsCorrect(Node* AnswerList, Node* UserList) { // xByC 형태로 리턴 (x, y : 숫자)
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

    Node* AnswerList = NULL;    // 정답을 저장할 리스트의 헤드노드
    Node* UserList = NULL;      // 헤드노드주소값을 저장
    Node* NewNode = NULL;

    int maxCount = 10;  // 정답맞추기 시도 횟수 (10이면 10번 시도할 수 있음)
    int isFind = 0;
    int isPlay = 1;
    int count = 0;
    int i = 0;

    char result[5];       // Bulls와 Cows 갯수를 받을 문자열
    char userNumbers[10]; // user숫자 입력받을 공간

    for (i = 0; i < 4; i++) {           // 정답 List 생성
        NewNode = SLL_CreateNode(0);
        SLL_AppendNode(&AnswerList, NewNode);
    }

    for (i = 0; i < 4; i++) {           // User List 생성
        NewNode = SLL_CreateNode(0);
        SLL_AppendNode(&UserList, NewNode);
    }

    while (isPlay) {
        MakeAnswer(AnswerList); // 정답생성
        isFind = 0;

        for (count = 1; count <= maxCount; count++) {  // User 숫자 입력
           
            printf("숫자 4개를 입력하세요: ");
            scanf_s("%s", userNumbers, sizeof(userNumbers));

            if (strlen(userNumbers) != 4) {
                printf("숫자가 4자리가 아닙니다.\n\n");
                count--;
                continue;
            }
            if (StringIsNumbers(userNumbers) == 0) {
                printf("숫자가 아닌 값이 섞여있습니다. \n\n");
                count--;
                continue;
            }

            Node* TempList = UserList;    // User가 입력한 숫자를 UserList에 저장
            i = 0;
            while (TempList != NULL) {
                TempList->Data = userNumbers[i++];
                TempList = TempList->NextNode;
            }

            if (IsDuplicate(UserList)) {
                printf("중복된 숫자가 섞여있습니다. \n\n");
                count--;
                continue;
            }

            // Computer의 숫자와 User의 숫자 비교
            strcpy_s(result, sizeof(char) * 5, IsCorrect(AnswerList, UserList));
            if (result[0] == '4') {
                isFind = 1;
                break;
            }

            printf("입력한 횟수 : %d result : %s \n\n", count, result);
        }

        if (isFind == 1) {
            printf("정답입니다. 총 입력한 횟수: %d, 정답 : ", count);
            PrintList(AnswerList);
        }
        else {
            printf("Game Over.. 정답 : ");
            PrintList(AnswerList);
        }


        while (1) {
            printf("\n\n다시 플레이 하시겠습니까? (0: 종료, 1: 다시시작): ");
            scanf_s("%d", &isPlay);
            if (isPlay == 0 || isPlay == 1)
                break;

            printf("0 또는 1을 입력해주세요..");
        }
    }
    
    printf("\n게임을 종료합니다. \n\n");
    printf("링크드리스트 제거중...\n");

    SLL_DestoyList(AnswerList);
    SLL_DestoyList(UserList);

    printf("링크드리스트 제거완료.\n");

    return 0;
}