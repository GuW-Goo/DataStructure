#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>

/*
ī����ī ��
ī����ī ���� �ε��� ������ D.R.ī����ī�� ���� ������ ���̴�.
� ���� �������� �� �κ����� ������ ���Ͽ��� �� �ٽ� ������ ���� �Ǵ� ������ �ǹ��Ѵ�.
���� ��� 45�� ī����ī ���ε�, 45�� = 2025�̰�, 20 + 25 = 45�̱� �����̴�.

� ���� �Է� �ް� �� ���� ī����ī ������ �ƴ����� ����ϴ� �Լ��� ����ÿ�.
� ���� �Է� �ް� �ڸ����� �� ���� ��� ī����ī ���� ����Ͻÿ�.
� ���� �Է� �ް� � �� ������ ��� ī����ī ���� ����Ͻÿ�.
*/

// ī����ī ������ Ȯ���ϴ� �Լ�
int IsKaprica(int number) {

	// �Է¹��� ���� �����Ͽ� ����
	int squareNumber = number * number;

	// ���ڸ� �ڸ� ���ʰ�, �����ʰ�
	int left = 0;
	int right = 0;

	// ������ ���� �ڸ����� ����
	int E = 1;
	int length = 0;
	while (squareNumber / E != 0) {
		E = E * 10;
		length++;
	}
	
	for (int i = 0; i < length; i++) {	// ������ ���� �ڸ�����ŭ �ݺ�

		// i = 1���� �ؼ� ������ ���� 10���ڸ����� �ڸ��� ������
		E = 1;
		for (int j = 0; j < i; j++) {
			E = E * 10;
		}

		// ���� �߶� ����, �����ʿ� ����
		left = squareNumber / E;
		right = squareNumber % E;

		// �Է¹��� ���� �ڸ����� ���� ���ٸ� return 1
		if (number == (left + right))
			return 1;
	}

	return 0;
}


int main() {
	int number = 0;

	// case 1: � ���� �Է� �ް� �� ���� ī����ī ������ �ƴ����� ����ϴ� �Լ��� ����ÿ�.
	printf("ī����ī ������ Ȯ�� �� ���ڸ� �Է��ϼ��� : ");
	scanf_s("%d", &number);

	if (IsKaprica(number))
		printf("%d�� ī����ī �� �Դϴ�.\n", number);
	else
		printf("%d�� ī����ī ���� �ƴմϴ�.\n", number);

	// case 2: � ���� �Է� �ް� �ڸ����� �� ���� ��� ī����ī ���� ����Ͻÿ�.
	printf("ã����� ī����ī ���� �ڸ����� �Է��ϼ��� (��: 2�ڸ��� 10 ~ 99) : ");
	scanf_s("%d", &number);

	// �ڸ����� ã�� �ݺ���
	int E = 1;
	for (int i = 0; i < number - 1; i++) {
		E = E * 10;
	}

	printf("%d�ڸ����� ī����ī �� : ", number);
	for (int i = E; i < (E * 10); i++) {
		if (IsKaprica(i))
			printf("%d ", i);
	}
	printf("\n");

	// case 3: � ���� �Է� �ް� � �� ������ ��� ī����ī ���� ����Ͻÿ�.
	printf("������ ���� �Ѱ��� �Է����ּ��� (�� ������ ��� ī����ī ���ڸ� ����մϴ�) : ");
	scanf_s("%d", &number);

	printf("%d ������ ī����ī �� : ", number);
	for (int i = 0; i < number; i++) {
		if (IsKaprica(i))
			printf("%d ", i);
	}
	printf("\n");

	return 0;
}