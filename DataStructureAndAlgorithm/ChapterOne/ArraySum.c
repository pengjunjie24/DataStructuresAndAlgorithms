
//�ֶ���֮����һ�����ģ���⣬�ֽ�����ɸ������⣬��ģ�����൱
//�ֱ���������⣬��������Ľ�õ�ԭ����Ľ�
//T(n) = 2 * T(n/2) + O(1)  T(1) = O(1)
//������ͣ����ֵݹ�
#include <stdio.h>

int sum(int A[], int low, int high)
{
    printf("low = %d, high = %d\n", low, high);
    if (low == high)
    {
        return A[low];
    }

    int mid = (low + high) >> 1;
    return sum(A, low, mid) + sum(A, mid + 1, high);
}

int main()
{
    int a[] = { 2, 4, 6, 3, 7, 4, 1 };
    int result = sum(a, 0, sizeof(a) / sizeof(int) - 1);

    printf("result = %d\n", result);
    getchar();
    return 0;
}