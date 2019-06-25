

#ifndef LIST_HPP
#define LIST_HPP

#include "ListNode.hpp"

template<typename T>
class List
{
public:
    //���캯��
    List(){ init(); }//Ĭ��
    List(List<T> const& L);//���帴���б�L
    List(List<T> const& L, Rank r, int n);//�����б�L���Ե�r����ĵ�n��
    List(ListNodePosi(T)p, int n);//�����б�����λ��p��ĵ�n��

    //��������
    ~List()
    {
        clear();
        delete _header;
        delete _trailer;
    }

    // ֻ�����ʽӿ�
    Rank size() const { return _size; } //��ģ
    bool empty() const { return _size <= 0; } //�п�

    T& operator[] (Rank r) const //���أ�֧��ѭ�ȷ��ʣ�Ч�ʵͣ�O(r)
    {
        ListNodePosi(T) p = first();//���׽ڵ����
        while (0 < r--)
        {
            p = p->succ;//˳����r���ڵ㼴��Ŀ��ڵ�
        }
        return p->data;//����Ŀ��ڵ�
    }

    ListNodePosi(T) first() const { return _header->succ; } //�׽ڵ�λ��
    ListNodePosi(T) last() const { return _trailer->pred; } //ĩ�ڵ�λ��
    bool valid(ListNodePosi(T) p) //�ж�λ��p�Ƿ����Ϸ�
    {
        return p && (_trailer != p) && (_header != p);
    } //��ͷ��β�ڵ��ͬ��NULL
    int disordered() const; //�ж��б��Ƿ�������
    ListNodePosi(T) find(T const& e) const //�����б����
    {
        return find(e, _size, _trailer);
    }

    ListNodePosi(T) find(T const& e, int n,
        ListNodePosi(T) p) const //����������ң��ӽڵ�p��n��ǰ�����ҵ�����e�������,0(n)
    {
        while (0 < n--)//�������������p��ǰ����e�Ƚ�
        {
            if (e == (p = p->pred)->data)
            {
                return p;//ֱ�����з���
            }
        }

        return NULL;//Խ�緵��null
    }

    ListNodePosi(T) search(T const& e) const //�����б����
    {
        return search(e, _size, _trailer);
    }

    ListNodePosi(T) search(T const& e, int n, ListNodePosi(T) p) const //�����������,
    //�������б��ڽڵ�p��n��(��)ǰ���У��ҵ�������e������ߣ�O(n),ʱ�临�Ӷ�������һ��
    {
        while (0 <= n--)//����p���������nǰ������������
        {
            if (((p = p->pred)->data) <= e)//һ�����Ƚ�
            {
                break;
            }
        }
        return p;//ֱ�����У���ֵԽ����߷�ΧԽ��󣬷��ز�����ֹλ��
    }

    ListNodePosi(T) selectMax(ListNodePosi(T) p, int n) //��p����n-1�������ѡ�������
    {
        ListNodePosi(T) pMax = p;//�ݶ����Ԫ��Ϊ�׽ڵ�p
        ListNodePosi(T) pCur = p;//��ǰԪ��Ϊp
        for (int i = 1; i < n; ++i)
        {
            pMax = ((pMax->data) < ((pCur = pCur->succ)->data)) ?
            pCur : pMax;//��ǰ���Ԫ��С�ڵ�ǰԪ�أ����µ�ǰ���Ԫ��
            //�Զ����ͬ��pMax������ѡȡ���ĵ�pMax
        }

        return pMax;//�������ڵ�λ��
    }

    ListNodePosi(T) selectMax() { return selectMax(header->succ, _size);} //���������

    // ��д���ʽӿ�
    ListNodePosi(T) insertAsFirst(T const& e) //��e�����׽ڵ����
    {
        insertA(first(), e);//�������ڱ��ĺ�������
    }

    ListNodePosi(T) insertAsLast(T const& e) //��e����ĩ�ڵ����
    {
        insertB(last(), e);//����β�ڱ���ǰ������
    }

    ListNodePosi(T) insertA(ListNodePosi(T) p, T const& e) //��e����p�ĺ�̲��루After��
    {
        _size++;
        return p->insertAsSucc(e);
    }

    ListNodePosi(T) insertB(ListNodePosi(T) p, T const& e) //��e����p��ǰ�����루Before��
    {
        _size++;
        return p->insertAsPred(e);
    }

    T remove(ListNodePosi(T) p) //ɾ���Ϸ�λ��p���Ľڵ�,���ر�ɾ���ڵ�
    {
        T e = p->data;//���ݴ�ɾ���ڵ���ֵ
        p->pred->succ = p->succ;
        p->succ->pred = p->pred;
        delete p;
        _size--;
        return e;//���ر�������
    }

    void merge(List<T>& L) { merge(first(), size, L, L.first(), L._size); } //ȫ�б�鲢
    void sort(ListNodePosi(T) p, int n); //�б���������
    void sort() { sort(first(), _size); } //�б���������

    int deduplicate() //����ȥ��, O(n^2)
    {
        if (_size < 2)//��ģС��2���������ظ�Ԫ��
        {
            return 0;
        }
        int oldSize = _size;
        ListNodePosi(T) p = first();
        Rank r = 1;//���׽ڵ���
        while (_trailer != (p = p->succ))//O(n)
        {
            ListNodePosi(T) q = find(p->data, r, p);//O(n)
            q ? remove(q) : ++r;//ɾ��q��ɾ��p��ԭ��:��ֹpָ��ʧЧ
        }
        return oldSize - _size;//��ɾ��Ԫ������
    }

    int uniquify() //����ȥ�أ�O(n)
    {
        if (_size < 2)//ƽ���б���Ȼ���ظ�
        {
            return 0;
        }

        int oldSize = _size;//��¼ԭ��ģ
        ListNodePosi(T) p = first();
        ListNodePosi(T) q;

        while (_trailer != (q = p->succ))//û�е�β�ڱ��ڵ㣬O(n)
        {
            if (p->data != q->data)//�����������ڽڵ㣬����ת����һ���ڵ�
            {
                p = q;
            }
            else
            {
                remove(q);//��ͬ��ɾ������,O(1)
            }
        }

        return oldSize - _size;//��ɾ��Ԫ������
    }

    void reverse(); //ǰ���ã�ϰ�⣩

    // ����
    void traverse(void(*) (T&)); //����������ʵʩvisit����������ָ�룬ֻ����ֲ����޸ģ�
    template <typename VST> //������
    void traverse(VST&); //����������ʵʩvisit�������������󣬿�ȫ�����޸ģ�

protected:
    void init()//�б���ʱ��ʼ��
    {
        _header = new ListNode<T>;//����ͷ�ڱ��ڵ�
        _trailer = new ListNode<T>;//����β�ڱ��ڵ�

        _header->succ = _trailer;
        _header->pred = NULL;//����

        _trailer->pred = _header;
        _trailer->succ = NULL;//����

        _size = 0;
    }

    int clear()//������нڵ�,O(n)
    {
        int oldSize = _size;
        while (0 < _size)
        {
            remove(_header->succ);
        }

        return oldSize;
    }

    void copyNodes(ListNodePosi(T) p, int n)//�����б�����λ��p���n��
    {
        init();//������β�ڱ��ڵ㲢�ҳ�ʼ��
        while (n--)//������p��n��������Ϊĩ�ڵ����
        {
            insertAsLast(p->data);
            p = p->succ;
        }
    }
    void merge(ListNodePosi(T)&, int, List<T>&, ListNodePosi(T), int);//�鲢
    void mergeSort(ListNodePosi(T)& p, int n);//�Դ�p��ʼ������n���ڵ�鲢����

    void selectionSort(ListNodePosi(T) p, int n)//�Դ�p��ʼ������n���ڵ�ѡ������,��ú�����������O(n^2)
    {
        ListNodePosi(T) head = p->pred;
        ListNodePosi(T) tail = p;
        for (int i = 0; i < n; ++i)//head��tail��ͷ/β�ڱ��ڵ�
        {
            tail = tail->succ;
        }

        while (1 < n)//�Ӵ��������ҳ�����ߣ���������������ǰ��
        {
            //new��delete�����ǳ������ʱ���100������,�����������Ч�ʺܵ�
            //insertB(tail, remove(selectMax(head->succ, n)));//����ǰ���Ԫ�ز���β�ڱ�֮ǰ

            //���������򼴿�
            ListNodePosi(T) pCurMax = selectMax(head->succ, n);//ѡ�������pMax,���뵽β������֤���㷨�ȶ���,O(n)
            ListNodePosi(T) pLastNode = tail->pred;
            T tmpData = pCurMax->data;
            pCurMax->data = pLastNode->data;
            pLastNode->data = tmpData;

            tail = tail->pred;//����������������䷶Χ���ϸ���
            --n;
        }
    }

    //insertSort��������������������ܣ������������е�����
    void insertionSort(ListNodePosi(T) p, int n)//�Դ�p��ʼ������n���ڵ��������
    {
        for (int r = 0; r < n; ++r)//n�ε���,ÿ��O(r+1)
        {
            insertA(search(p->data, r, p), p->data);//��ѯ+����
            p = p->succ;//ת����һ���ڵ�
            remove(p->pred);
        }
    }//����O(1)�ĸ����ռ䣬���ھ͵��㷨

private:
    int _size;//��С
    ListNodePosi(T) _header;//ͷ�ڱ�
    ListNodePosi(T) _trailer;//β�ڱ�
};

#endif