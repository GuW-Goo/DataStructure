#include <stdio.h>

// »ğÀÔÁ¤·Ä

int main() {
	int DataSet[] = { 6, 4, 2, 3, 1, 5 };

	int length = sizeof(DataSet) / sizeof(int);

	for (int i = 1; i < length; i++) {

		if (DataSet[i] < DataSet[i - 1]) {
			int temp = DataSet[i];
			int j = 0;

			for (j = i - 1; j >= 0; j--) {
				if (temp < DataSet[j]) {
					DataSet[j + 1] = DataSet[j];
				}
				else {
					break;
				}
			}

			DataSet[j + 1] = temp;
		}
		
	}

	printf("DataSet = ");
	for (int i = 0; i < length; i++) {
		printf("%d ", DataSet[i]);
	}

	return 0;
}