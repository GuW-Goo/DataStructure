#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

int main(int argc, char** argv) {
	char* fileName;	// ������ ��ϵǿ��ִ� ������ ���ϸ� (path ����)

	fileName = argv[1];

	char* pattern = argv[2];

	char Text[512];	// ���Ͽ��� ���� ������ ������ �迭

	FILE* fp;

	fp = fopen(fileName, "r");

	if (fp == NULL) {
		printf("�����б⿡ �����߽��ϴ�.\n");
		return 0;
	}

	if (argc < 3) {
		printf("Usage: �������ϸ� �������ϸ� ���Ϲ��ڿ�");
		return 0;
	}

	int patternLength = strlen(pattern);	// ���� ���ڿ��� ����
	int line = 1;
	int i, j;

	while (fgets(Text, 512, fp) != NULL) {
		// �о���� ����ȿ� ã�� ���Ϲ��ڿ��� �ִ��� Ȯ���ϰ�
		// ������ �ش� ���� ��ȣ�� �÷���ȣ�� ����ϸ� �˴ϴ�.

		int length = strlen(Text);	// ���� ���ڿ��� ���̸� ���Ѵ�.

		for (i = 0; i < length - patternLength + 1; i++) {
			/*
			// 1��° ����
			int isFind = 1;
			// ���� ���ڿ��� ���̸�ŭ Text�� ��
			for (j = 0; j < patternLength; j++) {
				if (Text[i + j] != pattern[j]) {
					isFind = 0;
					break;
				}
			}

			if (isFind == 1) {
				printf("���ι�ȣ: %d, �÷���ȣ: %d\n���ڿ�: %s\n\n", line, i, Text);
			}
			*/

			// 2��° ����
			for (j = 0; j < patternLength; j++) {
				if (Text[i + j] != pattern[j])
					break;
			}

			if (j == patternLength)
				printf("���ι�ȣ: %d, �÷���ȣ: %d\n���ڿ�: %s\n\n", line, i, Text);
		}

		line++;
	}

	fclose(fp);

	return 0;
}