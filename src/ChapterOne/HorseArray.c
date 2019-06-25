
#include <stdio.h>


//������֮����һ����ģ�ϴ������ֽ������������
//����һ������ƽ������һ����ģ����
//�����鷭ת
void swap(int* leftValue, int* rightValue)
{
    int tempValue = *leftValue;
    *leftValue = *rightValue;
    *rightValue = tempValue;
}

void reverse(int* srcArray, int lowIndex, int highIndex)
{
    printf("lowIndex = %d, highIndex = %d\n", lowIndex, highIndex);
    if (lowIndex < highIndex)
    {
        swap(&srcArray[lowIndex], &srcArray[highIndex]);
        reverse(srcArray, lowIndex + 1, highIndex - 1);
    }
}

int main()
{
    int reverseArray[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8 };
    int reverseLen = sizeof(reverseArray) / sizeof(int);
    for (int i = 0; i < reverseLen; ++i)
    {
        printf("%d ", reverseArray[i]);
    }
    printf("\n");
    getchar();

    reverse(reverseArray, 0, reverseLen - 1);
    for (int i = 0; i < reverseLen; ++i)
    {
        printf("%d ", reverseArray[i]);
    }
    printf("\n");
    getchar();
}