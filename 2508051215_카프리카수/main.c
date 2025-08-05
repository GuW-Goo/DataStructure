#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>

/*
카프리카 수
카프리카 수란 인도의 수학자 D.R.카프리카의 의해 정의한 수이다.
어떤 수의 제곱수를 두 부분으로 나누어 더하였을 때 다시 원래의 수가 되는 수들을 의미한다.
예를 들어 45는 카프리카 수인데, 45² = 2025이고, 20 + 25 = 45이기 때문이다.

어떤 수를 입력 받고 그 수가 카프리카 수인지 아닌지를 출력하는 함수를 만드시오.
어떤 수를 입력 받고 자릿수가 그 수인 모든 카프리카 수를 출력하시오.
어떤 수를 입력 받고 어떤 수 이하의 모든 카프리카 수를 출력하시오.
*/

// 카프리카 수인지 확인하는 함수
int IsKaprica(int number) {

	// 입력받은 수를 제곱하여 저장
	int squareNumber = number * number;

	// 숫자를 자를 왼쪽값, 오른쪽값
	int left = 0;
	int right = 0;

	// 제곱한 수의 자릿수를 구함
	int E = 1;
	int length = 0;
	while (squareNumber / E != 0) {
		E = E * 10;
		length++;
	}
	
	for (int i = 0; i < length; i++) {	// 제곱한 수의 자릿수만큼 반복

		// i = 1부터 해서 제곱한 수의 10의자리부터 자르기 시작함
		E = 1;
		for (int j = 0; j < i; j++) {
			E = E * 10;
		}

		// 수를 잘라서 왼쪽, 오른쪽에 저장
		left = squareNumber / E;
		right = squareNumber % E;

		// 입력받은 수와 자른수의 합이 같다면 return 1
		if (number == (left + right))
			return 1;
	}

	return 0;
}


int main() {
	int number = 0;

	// case 1: 어떤 수를 입력 받고 그 수가 카프리카 수인지 아닌지를 출력하는 함수를 만드시오.
	printf("카프리카 수인지 확인 할 숫자를 입력하세요 : ");
	scanf_s("%d", &number);

	if (IsKaprica(number))
		printf("%d는 카프리카 수 입니다.\n", number);
	else
		printf("%d는 카프리카 수가 아닙니다.\n", number);

	// case 2: 어떤 수를 입력 받고 자릿수가 그 수인 모든 카프리카 수를 출력하시오.
	printf("찾고싶은 카프리카 수의 자릿수를 입력하세요 (예: 2자릿수 10 ~ 99) : ");
	scanf_s("%d", &number);

	// 자릿수를 찾는 반복문
	int E = 1;
	for (int i = 0; i < number - 1; i++) {
		E = E * 10;
	}

	printf("%d자릿수의 카프리카 수 : ", number);
	for (int i = E; i < (E * 10); i++) {
		if (IsKaprica(i))
			printf("%d ", i);
	}
	printf("\n");

	// case 3: 어떤 수를 입력 받고 어떤 수 이하의 모든 카프리카 수를 출력하시오.
	printf("임의의 숫자 한개를 입력해주세요 (그 이하의 모든 카프리카 숫자를 출력합니다) : ");
	scanf_s("%d", &number);

	printf("%d 이하의 카프리카 수 : ", number);
	for (int i = 0; i < number; i++) {
		if (IsKaprica(i))
			printf("%d ", i);
	}
	printf("\n");

	return 0;
}