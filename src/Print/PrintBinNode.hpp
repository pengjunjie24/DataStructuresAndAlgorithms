
#pragma once

//BinNode�ڵ�
template<typename T>
void UniPrint::p(BinNode<T>& node)
{
    p(node.data);

    //������ָ��
    printf(((node.lc && (&node != node.lc->parent))
        || (node.rc && (&node != node.rc->parent)))
        ? "@" : " ");
}
