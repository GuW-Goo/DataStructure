#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

int main(int argc, char** argv) {
	char* fileName;	// 문장이 기록되오있는 파일의 파일명 (path 포함)

	fileName = argv[1];

	char* pattern = argv[2];

	char Text[512];	// 파일에서 읽은 문장을 저장할 배열

	FILE* fp;

	fp = fopen(fileName, "r");

	if (fp == NULL) {
		printf("파일읽기에 실패했습니다.\n");
		return 0;
	}

	if (argc < 3) {
		printf("Usage: 실행파일명 문자파일명 패턴문자열");
		return 0;
	}

	int patternLength = strlen(pattern);	// 패턴 문자열의 길이
	int line = 1;
	int i, j;

	while (fgets(Text, 512, fp) != NULL) {
		// 읽어들인 문장안에 찾는 패턴문자열이 있는지 확인하고
		// 있으면 해당 라인 번호와 컬럼번호를 출력하면 됩니다.

		int length = strlen(Text);	// 읽은 문자열의 길이를 구한다.

		for (i = 0; i < length - patternLength + 1; i++) {
			/*
			// 1번째 버전
			int isFind = 1;
			// 패턴 문자열의 길이만큼 Text와 비교
			for (j = 0; j < patternLength; j++) {
				if (Text[i + j] != pattern[j]) {
					isFind = 0;
					break;
				}
			}

			if (isFind == 1) {
				printf("라인번호: %d, 컬럼번호: %d\n문자열: %s\n\n", line, i, Text);
			}
			*/

			// 2번째 버전
			for (j = 0; j < patternLength; j++) {
				if (Text[i + j] != pattern[j])
					break;
			}

			if (j == patternLength)
				printf("라인번호: %d, 컬럼번호: %d\n문자열: %s\n\n", line, i, Text);
		}

		line++;
	}

	fclose(fp);

	return 0;
}