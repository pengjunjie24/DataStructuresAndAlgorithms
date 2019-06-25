

#ifndef STACK_HPP
#define STACK_HPP

#include "../ChapterTwo/Vector.h"

template <typename T>
class Stack : public Vector<T>//����������
{
public://size(), empty()�Լ����������ӿھ���ֱ������
    void push(const T& e) { this->insert(this->size(), e); }//��ջ��O(1)
    T pop() { return this->remove(this->size() - 1); }//��ջ,O(1)
    T& top() { return (*this)[this->size() - 1]; }//ȡ��
};

#endif