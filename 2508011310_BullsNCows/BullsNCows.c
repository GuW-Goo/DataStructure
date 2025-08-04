#include "LinkedList.h"
#include <string.h>

char NUMBER[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };

// char에 있는 Data가 숫자있지 확인
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

// 숫자로만 이루어진 리스트인지 확인, 문자포함시 : 0을 리턴
int   ListIsNumbers(Node* Head) {    
    Node* Temp = Head;

    while (Temp != NULL) {
        if (IsNumber(Temp->Data) == 0)    // Data가 문자면 return 0
            return 0;

        Temp = Temp->NextNode;
    }

    return 1;
}

// 리스트 제거 (메모리 반납)
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

// 리스트 출력
void  PrintList(Node* Head) {
    Node* Temp = Head;

    while (Temp != NULL) {
        printf("%c", Temp->Data);
        Temp = Temp->NextNode;
    }
}

// 정답 리스트 생성
void  MakeAnswer(Node* AnswerList) {
    Node* Temp = NULL;

    printf("정답 생성중...\n");  

     do {   // 정답의 중복 제거
        Temp = AnswerList;
        while (Temp != NULL) {
            Temp->Data = rand() % 9 + 48;   // 0 ~ 9 사이의 랜덤한 숫자를 문자로 변환하여 저장
            Temp = Temp->NextNode;
        }
     } while (IsDuplicate(AnswerList));

    printf("정답 생성완료\n\n");
}

// 리스트내에 중복값이 있는지 확인. 중복 : 1
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

// 정답리스트와 유저리스트 비교하는 함수 
// xByC 형태로 리턴 (x, y : 숫자)
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

            // 정답리스트와 유저리스트에서 같은 숫자를 찾음
            if (tempAnswerList->Data == tempUserList->Data) {
                if (userListIndex == answerListIndex)   // 1. 숫자의 위치가 같다면
                    bulls++;
                else    // 2. 숫자의 위치가 다르면
                    cows++;

                break;
            }
            
            tempAnswerList = tempAnswerList->NextNode;
            answerListIndex++;
        }
        
        tempUserList = tempUserList->NextNode;
        userListIndex++;
    }

    result[0] = bulls + 48; // 숫자를 문자로 바꿔 문자열에 저장
    result[2] = cows + 48;

    return result;
}

// 입력버퍼 제거
void ClearInputBuffer() {
    int ch;
    while((ch = getchar()) != '\n' && ch != EOF) { }
}

int main() {
    srand(time(NULL));

    Node* AnswerList = NULL;    // 정답을 저장할 리스트의 헤드노드
    Node* UserList = NULL;      // 유저가 입력한 리스트의 헤드노드
    Node* NewNode = NULL;
    Node* TempList = NULL;

    int maxCount = 10;      // 정답맞추기 시도 횟수 (10이면 10번 시도할 수 있음)
    int isFind = 0;
    int isPlay = 1;
    int count = 0;

    char result[5];         // Bulls와 Cows 갯수를 받을 문자열
    char userNumbers[10];   // user숫자 입력받을 공간

    // 정답 List 생성
    for (int i = 0; i < 4; i++) {           
        NewNode = SLL_CreateNode(0);
        SLL_AppendNode(&AnswerList, NewNode);
    }

    while (isPlay) {
        // 새로운 정답 생성
        MakeAnswer(AnswerList);
        isFind = 0;

        for (count = 1; count <= maxCount; count++) {
           
            printf("숫자 4개를 입력하세요: ");
            scanf_s("%s", userNumbers, sizeof(userNumbers));
            ClearInputBuffer();

            // User가 입력한 숫자를 UserList에 저장
            for (int i = 0; i < sizeof(userNumbers); i++) { // 문자열에서 문자 1개씩 UserList에 저장함
                if (userNumbers[i] == '\0') {
                    break;
                }

                NewNode = SLL_CreateNode(userNumbers[i]);
                SLL_AppendNode(&UserList, NewNode);
            }

            // 숫자가 n자리 수인지 확인
            if (SLL_GetNodeCount(UserList) != 4) {
                printf("숫자가 4자리가 아닙니다.\n\n");

                SLL_DestoyList(UserList);   // 유저 리스트 제거
                UserList = NULL;
                count--;

                continue;
            }
            // 숫자에 문자가 포함되어있는지 확인
            if (ListIsNumbers(UserList) == 0) {
                printf("숫자가 아닌 값이 섞여있습니다. \n\n");
                
                SLL_DestoyList(UserList);   // 유저 리스트 제거
                UserList = NULL;
                count--;

                continue;
            }
            // 입력받은 숫자에 중복된 숫자가 있는지 확인
            if (IsDuplicate(UserList)) {
                printf("중복된 숫자가 섞여있습니다. \n\n");

                SLL_DestoyList(UserList);   // 유저 리스트 제거
                UserList = NULL;
                count--;

                continue;
            }

            // Computer의 숫자와 User의 숫자 비교
            strcpy_s(result, sizeof(char) * 5, IsCorrect(AnswerList, UserList));
            if (strcmp(result, "4B0C") == 0) { // 4B0C일 경우 게임 종료
                isFind = 1;
                break;
            }

            SLL_DestoyList(UserList);   // 유저 리스트 제거
            UserList = NULL;

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

    printf("링크드리스트 제거완료.\n");

    return 0;
}