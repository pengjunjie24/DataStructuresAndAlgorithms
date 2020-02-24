
#pragma once

#include <Bitmap/BitmapO1Init.h>
#include <Share/Release.hpp>

#define ROOT 0
#define L_CHILD 1
#define R_CHILD -1*L_CHILD

//�����������ӡ
template <typename T>
void UniPrint::p(BinTree<T>& bt) //������
{
    printf("BinTree\tname:%s\tpoint:%p\tsize:%d:\n", typeid(bt).name(), &bt, bt.size());//������Ϣ
    Bitmap01Init* branchType = new Bitmap01Init;//��¼��ǰ�ڵ����ȵķ���
    printBinTree(bt.root(), -1, ROOT, branchType);
    release(branchType);
    printf("\n");
}

//����������������ͳһ��ӡ
template <typename T>
static void printBinTree(BinNodePosi(T) bt, int depth, int type, Bitmap01Init* bType)
{
    if (!bt)//�ݹ��
    {
        return;
    }

    if (-1 < depth)
    {
        R_CHILD == type ? bType->set(depth) : bType->clear(depth);
    }

    printBinTree(bt->rc, depth + 1, R_CHILD, bType);
    print(bt);
    printf(" *");
    for (int i = -1; i < depth; ++i)
    {
        if ((0 > i) || bType->test(i) == bType->test(i + 1))
        {
            printf("         ");
        }
        else
        {
            printf("|        ");
        }
        switch (type)
        {
        case R_CHILD:
            printf("����");
            break;
        case  L_CHILD:
            printf("����");
            break;
        default:
            printf("����"); //root
            break;
        }
    }
}