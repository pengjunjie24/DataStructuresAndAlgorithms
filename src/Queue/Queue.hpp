
#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <List/List.hpp>

template <typename T>
class Queue : public List<T>//����ģ���ࣨ�̳�Listԭ�нӿڣ�
{
public://size(), empty()�Լ����������ӿھ���ֱ������
    void enqueue(T const& e) { insertAsLast(e); } //��ӣ�β������
    T dequeue() { return remove(first()); } //���ӣ��ײ�ɾ��
    T& front() { return first()->data; } //����
};

#endif