
#include <Vector/Vector.hpp>

//����:��������˳�����
template <typename T>
void TestFind(Vector<T>& V, int n)
{
    //���β���������Ԫ�أ���Ȼ�ɹ�
    for (int i = 0; i < V.size(); ++i)
    {
        T e = V[i];
        print(e);
        Rank r = V.find(e);
        if (r < 0)
        {
            printf(": not found until rank V[%d] <> %d", r, e);
        }
        else
        {
            printf(": found at rank V[%d] = %d", r, V[r]);
        }

        printf("\n");
    }
    //���β���ÿ������Ԫ�صľ�ֵ�����ܳɹ�
    for (int i = 0; i <= V.size(); ++i)
    {
        T a = (0 < i) ? V[i - 1] : V[0] - 4;
        T b = (i < V.size()) ? V[i] : V[V.size() - 1] + 4;
        T e = (a + b) / 2;
        print(e);
        Rank r = V.find(e);
        if (r < 0)
        {
            printf(": not found until rank V[%d] <> %d", r, e);
        }
        else
        {
            printf(": found at rank V[%d] = %d", r, V[r]);
        }
        printf("\n");
    }
}

//���ԣ����������Ĳ��ң�binSearch��fibSearch��
template<typename T>
void TestSearch(Vector<T>& v)
{
    //���β���������Ԫ�أ���Ȼ�ɹ�
    for (int i = 0; i < V.size(); ++i)
    {
        T e = V[i];
        print(e);
        printf(": by ");
        Rank r = v.search();
        if (V[r] == e)
        {
            printf("found at rank V[%d] = %d", r, V[r]);
        }
        else
        {
            printf("found at rank V[%d] = %d <> %d\a\a", r, V[r], e);
        }
        printf("\n\n");
    }

    //��������Ԫ�صľ�ֵ�����ܳɹ�
    for (int i = 0; i < V.size(); ++i)
    {
        T a = (0 < i) ? V[i - 1] : V[0] - 4;
        T b = (i < V.size()) ? V[i] : V[V.size() - 1] + 4;
        T e = (a + b) / 2; print(e); printf(": by ");
        Rank r = V.search(e);
        printf("V[%3d] =", r);
        (r < 0) ? print("-INF") : print(V[r]); printf("  ~  ");
        printf("V[%3d] =", r + 1);
        (r + 1 < V.size()) ? print(V[r + 1]) : print("+INF");
        bool ordered = true;
        if ((r >= 0) && (V[r] > e))
        {
            ordered = false;
        }
        if ((r + 1 < V.size()) && (V[r + 1] <= e))
        {
            ordered = false;
        }
        if (!ordered)
        {
            printf("\tincorrect search\a\a");
        }
        printf("\n\n");
    }
}

//���ԣ����������Ĳ���
template <typename T>
void TestOrderedInsertion(Vector<T>& V, int n)
{
    while (n * 2 > V.size())
    {
        T e = dice((T)n * 2);
        printf("Inserting ");
        print(e);
        printf(" by ");
        V.insert(V.search(e) + 1, e);
        print(V);
    }
}