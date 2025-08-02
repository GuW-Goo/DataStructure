#include <stdio.h> 
#include <string.h>
#include "Score.h"

// �����Ʈ
void BubbleSort(Score DataSet[], int Length)
{
    int i = 0;
    int j = 0;
    Score temp;

    for (i = 0; i < Length - 1; i++)
    {
        for (j = 0; j < Length - (i + 1); j++)
        {
            if (DataSet[j].score > DataSet[j + 1].score)
            {
                temp = DataSet[j + 1];
                DataSet[j + 1] = DataSet[j];
                DataSet[j] = temp;
            }
        }
    }
}

// ��������
void InsertionSort(Score DataSet[], int Length)
{
    int i = 0;
    int j = 0;
    Score value;

    for (i = 1; i < Length; i++)
    {
        if (DataSet[i - 1].score <= DataSet[i].score)
            continue;

        value = DataSet[i];

        for (j = 0; j < i; j++)
        {
            if (DataSet[j].score > value.score)
            {
                memmove(&DataSet[j + 1], &DataSet[j], sizeof(DataSet[0]) * (i - j));
                DataSet[j] = value;
                break;
            }
        }
    }
}

// ����Ʈ1
void Swap(Score A[], Score B[]) {
    Score Temp = *A;
    *A = *B;
    *B = Temp;
}

int Partition(Score DataSet[], int Left, int Right) {
    int First = Left;
    Score Pivot = DataSet[First];

    ++Left;

    while (Left <= Right) {
        while (DataSet[Left].score <= Pivot.score && Left < Right)
            ++Left;

        while (DataSet[Right].score >= Pivot.score && Left <= Right)
            --Right;

        if (Left < Right)
            Swap(&DataSet[Left], &DataSet[Right]);
        else
            break;
    }

    Swap(&DataSet[First], &DataSet[Right]);

    return Right;
}

void QuickSort(Score DataSet[], int Left, int Right) {
    if (Left < Right) {
        int Index = Partition(DataSet, Left, Right);

        QuickSort(DataSet, Left, Index - 1);
        QuickSort(DataSet, Index + 1, Right);
    }
}

// ����Ʈ2
int ComparePoint(const void* _elem1, const void* _elem2)
{
    Score* elem1 = (Score*)_elem1;
    Score* elem2 = (Score*)_elem2;

    if (elem1->score > elem2->score)
        return 1;
    else if (elem1->score < elem2->score)
        return -1;
    else
        return 0;
}

// ����
// score.h ���Ͽ� ����� 3������ ����Ÿ�� score ������ �����ؼ� �տ� 1 ~ 10�� �ڿ� 29990 ~ 29999���� ����غ�����.
// �����Ʈ
// ��������
// ����Ʈ
// ����Ʈ2

int main(void)
{
    // int DataSet[] = { 6, 4, 2, 3, 1, 5 };
    int Length = sizeof DataSet / sizeof DataSet[0];
    int i = 0;

    // ��������
    // BubbleSort(DataSet, Length);

    // ��������
    // InsertionSort(DataSet, Length);

    // ����Ʈ1
    // QuickSort(DataSet, 0, Length - 1);

    // ����Ʈ2
    qsort((Score*)DataSet, Length, sizeof(Score), ComparePoint);

    printf("���� 10��\n");
    for (i = 0; i < 10; i++)
    {
        printf("number: %d, score: %.2lf\n", DataSet[i].number, DataSet[i].score);
    }

    printf("\n���� 10��\n");
    for (i = Length - 10; i < Length; i++) {
        printf("number: %d, score: %.2lf\n", DataSet[i].number, DataSet[i].score);
    }

    printf("\n");

    return 0;
}
