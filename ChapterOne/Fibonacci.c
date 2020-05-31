

//쳲���������
#include <stdio.h>
#include <stdint.h>

//��Ч��fib���нⷨ���д����ظ��ĵݹ�ʵ��
//ʱ�临�Ӷ�T(n) = O(2^n)
int64_t fib(int n)
{
    return (2 > n) ? (int64_t)n : (fib(n - 1) + fib(n - 2));
}

//��̬�滮
//ʱ�临�Ӷ�T(n) = O(n), �ռ临�Ӷ�O(1)
int64_t improveFib1(int n)
{
    int64_t f = 0;//fib(0)
    int64_t g = 1;//fib(1)

    while (0 < n--)
    {
        g = g + f;//fib(n) = fib(n-1) + fib(n-2)
        f = g - f;//fib(n-1) = fib(n) - fib(n-2)
    }

    return f;
}

int main()
{
    int fibNum = 45;

    printf("fibsum: %ld\n", improveFib1(fibNum));
    getchar();
}
