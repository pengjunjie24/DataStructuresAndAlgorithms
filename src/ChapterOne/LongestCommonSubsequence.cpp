
//LCS: ��������������
//�ݹ����
//m == -1 || n == -1,��ȡ�����У��ݹ��
//��A[n] = B[m] = X, ��ȡ��LCS(A[0, n), B[0, m) + X)//������֮
//A[n] ��= B[m],��ȡLCS(A[0, n], B[0, m))��LCS(A[0, n), B[0, m])��ȡ������;
//�����ظ��ĵݹ�ʵ����ʱ�临�Ӷ�ΪO(2^n)
#include <stdio.h>
#include <string.h>

char* LCS(char* sequenceA, char* sequenceB, int sequenceALen, int sequenceBLen, char* lcs, int lcsLen)
{
    if (sequenceALen == -1 || sequenceBLen == -1)
    {
        return lcs;//�ݹ��
    }
    if (sequenceA[sequenceALen] == sequenceB[sequenceBLen])//��һ�������A��BĩβԪ����ͬ
    {
        lcs[lcsLen++] = sequenceA[sequenceALen];
        return LCS(sequenceA, sequenceB, sequenceALen - 1, sequenceBLen - 1, lcs, lcsLen);
    }
    else//�ڶ��������A��B�����
    {
        return strlen(LCS(sequenceA, sequenceB, sequenceALen, sequenceBLen - 1, lcs, lcsLen)) >
            strlen(LCS(sequenceA, sequenceB, sequenceALen - 1, sequenceBLen, lcs, lcsLen)) ?
            LCS(sequenceA, sequenceB, sequenceALen, sequenceBLen - 1, lcs, lcsLen) :
            LCS(sequenceA, sequenceB, sequenceALen - 1, sequenceBLen, lcs, lcsLen);
    }
}

int main()
{
    char a[] = "adbbqs";//����̫�����ر���
    char b[] = "diobdads";

    int lcsMinLen = strlen(a) > strlen(b) ? strlen(b) : strlen(a);
    char lcs[20] = { 0 };

    char* lcsResult = LCS(a, b, strlen(a) - 1, strlen(b) - 1, lcs, 0);

    printf("a = %s, b = %s, lcs = %s\n", a, b, lcs);

    getchar();
    return 0;
}