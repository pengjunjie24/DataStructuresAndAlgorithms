
#pragma once

class Fib
{
public:
    Fib(int maxN)//��ʼ��Ϊ��С��n����СFibonacci��
        :f(1)//fib(-1)
        , g(0)//fib(0)
        , n(0)
        , maxItem(maxN)
    {
        while (n < maxItem)
        {
            next();
        }
    }

    int get() { return g; }//��ȡ��ǰFibonacci�O(1)ʱ��
    int getItem() { return n; }//��ȡ��ǰ������O(1)ʱ��
    int next()//ת����һFibonacci�O(1)ʱ��
    {
        g += f;
        f = g - f;
        ++n;
        return g;
    }
    int prev()//ת����һFibonacci�O(1)ʱ��
    {
        f = g - f;
        g -= f;
        --n;
        return g;
}

private:
    int f;//f = fib(k - 1), g = fib(k),��Ϊint�ͣ��ܿ�ͻ���ֵ���
    int g;
    int n;//��ǰ����
    int maxItem;
};