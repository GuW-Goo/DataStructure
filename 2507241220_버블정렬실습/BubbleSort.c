#include <stdio.h>

int main() {
	int DataSet[] = { 1, 2, 4, 3, 5, 6 };

	// ���� DataSet �迭�� Data�� ���� ���� ������ �����
	// �����ؼ� ����غ�����...

	int length = sizeof(DataSet) / sizeof(int);

	for (int i = 0; i < length - 1; i++) {
		int isSort = 0;

		for (int j = 0; j < length - (i + 1); j++) {
			if (DataSet[j] > DataSet[j + 1]) {
				int temp = 0;
				temp = DataSet[j];
				DataSet[j] = DataSet[j + 1];
				DataSet[j + 1] = temp;

				isSort = 1;
			}
		}

		if (isSort == 0)
			break;
	}

	for (int i = 0; i < length; i++) {
		printf("DataSet[%d] = %d\n", i, DataSet[i]);
	}

	return 0;
}