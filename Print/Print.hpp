
/******************************************************************************************
 * 数据元素、数据结构通用输出接口
 ******************************************************************************************/
#pragma once

#include <BinTree/BinTree.hpp>//二叉树
#include <BinTree/BinNode.hpp>
#include <AVL/AVL.hpp>//AVL树
#include <Splay/Splay.hpp>//伸展树
#include <BTree/BTree.hpp>//B树
#include <RedBlack/RedBlack.hpp>//红黑树

#include <stdio.h>


class UniPrint
{
public:
    static void p(int e) { printf(" %04d", e); }
    static void p(float e) { printf(" %4.3f", e); }
    static void p(double e) { printf(" %4.3f", e); }
    static void p(char e) { printf(" %c", (31 < e) && (e < 128) ? e : '$'); }

    template <typename T>
    static void p(BinNode<T>&); //BinTree节点
    template <typename T>
    static void p(BinTree<T>&); //二叉树
    template <typename T>
    static void p(AVL<T>&); //AVL
    template <typename T>
    static void p(Splay<T>&); //Splay
    template <typename T>
    static void p(BTree<T>&); //BTree
    template <typename T>
    static void p(RedBlack<T>&); //RedBlack
};

template <typename T> static void print(T& x) { UniPrint::p(x); }
template <typename T> static void print(const T& x) { UniPrint::p(x); } //for Stack
//static void print(char* x) { printf(" %s", x ? x : "<NULL>"); } //字符串特别处理
//static void print(const char* x) { printf(" %s", x ? x : "<NULL>"); } //字符串特别处理
template <typename T> static void print(T* x) { x ? print(*x) : print(" <NULL>"); }

#include <Print/PrintImplementation.hpp>