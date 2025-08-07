#include <stdlib.h> 
#include <stdio.h>
#include "Point.h"
#include <time.h>

Point* BinarySearch(Point PointList[], int Size, double Target, int* pcount)
{
    int Left, Right, Mid;

    Left = 0;
    Right = Size - 1;

    int count = 0;

    while (Left <= Right)
    {
        Mid = (Left + Right) / 2;

        //printf("R[%d], L[%d], M[%d], id = %d, point = %lf\n", Right, Left, Mid, PointList[Mid].id, PointList[Mid].point);

        if (Target == PointList[Mid].point)
        {
            printf("Match Count = %d\n", count);
            *pcount = count;

            return &(PointList[Mid]);
        }

        else if (Target > PointList[Mid].point)
            Left = Mid + 1;
        else
            Right = Mid - 1;

        count++;
    }

    return NULL;
}

int ComparePoint(const void* _elem1, const void* _elem2)
{
    Point* elem1 = (Point*)_elem1;
    Point* elem2 = (Point*)_elem2;

    if (elem1->point > elem2->point)
        return 1;
    else if (elem1->point < elem2->point)
        return -1;
    else
        return 0;
}

int main(void)
{
    srand(time(NULL));
    int Length = sizeof DataSet / sizeof DataSet[0];
    Point* found = NULL;

    int countArray[1000] = { 0, };   // 1000번 탐색 횟수를 저장할 배열

    //  구매포인트에 대해 오름차순으로 정렬 
    qsort((void*)DataSet, Length, sizeof(Point), ComparePoint);

    for (int i = 0; i < 1000; i++) {
        int randValue = rand() % 30000;

        found = BinarySearch(DataSet, Length, DataSet[randValue].point, &countArray[i]);

        if (found != NULL) {
            printf("found: %d, %lf\n", found->id, found->point);
        }

    }

    int sum = 0;

    for (int i = 0; i < 1000; i++) {
        sum += countArray[i];
    }

    printf("1000번 탐색 작업시 평균 비교 횟수: sum = %d, average = %lf\n", sum, sum / (float)1000.0f);




    return 0;
}
