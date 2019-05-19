

typedef int Rank; //��
#define DEFAULT_CAPACITY  3 //Ĭ�ϵĳ�ʼ������ʵ��Ӧ���п�����Ϊ����

template <typename T>
class Vector//����ģ����
{
protected:
    Rank _size;
    int _capacity;
    T* _elem; //��ģ��������������

    void copyFrom(T const* A, Rank lo, Rank hi) //������������A[lo, hi)
    {
        _elem = new T[_capacity = 2 * (hi - lo)];
        _size = 0;
        while (lo < hi)
        {
            _elem[_size++] = A[lo++];
        }
    }

    void expand() //�ռ䲻��ʱ����,�ӱ����ݷ�̯ʱ��ɱ�ΪO(1)
    {
        if (_size < _capacity)
        {
            return;
        }

        _capacity = max(_capacity, DEFAULT_CAPACITY);
        T* oldElem = _elem;
        _elem = new T[_capacity <<= 1];
        for (int i = 0; i < _size; ++i)
        {
            _elem[i] = oldElem[i];
        }
        delete[] oldElem;
    }

    void shrink() //װ�����ӹ�Сʱѹ��
    {
        if (_capacity < DEFAULT_CAPACITY << 1)
        {
            return;//����������DEFAULT_CAPACITY����
        }
        if (_size << 2 > _capacity)
        {
            return; //��25%Ϊ��
        }
        T* oldElem = _elem;  _elem = new T[_capacity >>= 1]; //��������
        for (int i = 0; i < _size; i++)
        {
            _elem[i] = oldElem[i]; //����ԭ��������
        }
        delete[] oldElem; //�ͷ�ԭ�ռ�
    }
    bool bubble(Rank lo, Rank hi); //ɨ�轻��
    void bubbleSort(Rank lo, Rank hi); //���������㷨
    Rank max(Rank lo, Rank hi); //ѡȡ���Ԫ��
    void selectionSort(Rank lo, Rank hi); //ѡ�������㷨
    void merge(Rank lo, Rank mi, Rank hi); //�鲢�㷨
    void mergeSort(Rank lo, Rank hi); //�鲢�����㷨
    Rank partition(Rank lo, Rank hi); //��㹹���㷨
    void quickSort(Rank lo, Rank hi); //���������㷨
    void heapSort(Rank lo, Rank hi); //�������Ժ�����ȫ�ѽ��⣩

public:
    // ���캯��
    Vector(int c = DEFAULT_CAPACITY, int s = 0, T v = 0) //����Ϊc����ģΪs������Ԫ�س�ʼΪv
    {
        _elem = new T[_capacity = c];
        for (_size = 0; _size < s; _elem[_size++] = v);
    } //s<=c

    Vector(T const* A, Rank n) { copyFrom(A, 0, n); } //�������帴��
    Vector(T const* A, Rank lo, Rank hi) { copyFrom(A, lo, hi); } //����
    Vector(Vector<T> const& V) { copyFrom(V._elem, 0, V._size); } //�������帴��
    Vector(Vector<T> const& V, Rank lo, Rank hi) { copyFrom(V._elem, lo, hi); } //����

    // ��������
    ~Vector() { delete[] _elem; } //�ͷ��ڲ��ռ�

    // ֻ�����ʽӿ�
    Rank size() const { return _size; } //��ģ
    bool empty() const { return !_size; } //�п�
    int disordered() const; //�ж������Ƿ�������
    Rank find(T const& e) const { return find(e, 0, _size); } //���������������
    Rank find(T const& e, Rank lo, Rank hi) const //���������������
    {
        while ((lo < hi--) && (e != _elem[hi]));//�Ӻ���ǰ��˳�����
        return hi;//��hi < lo������ζ��ʧ�ܣ�����hi������Ԫ�ص���
    }
    Rank search(T const& e) const //���������������
    {
        return (0 >= _size) ? -1 : search(e, 0, _size);
    }
    Rank search(T const& e, Rank lo, Rank hi) const; //���������������


    // ��д���ʽӿ�
    T& operator[] (Rank r) //�����±������������������������ʽ���ø�Ԫ��
    {
        assert(r >= 0 || r <= _size);
        return _elem[r];
    }
    const T& operator[] (Rank r) const //����������ֵ�����ذ汾
    {
        assert(r >= 0 || r <= _size);
        return _elem[r];
    }
    Vector<T> & operator= (Vector<T> const&); //���ظ�ֵ���������Ա�ֱ�ӿ�¡����

    //������remove(r)�ӿڣ�ʵ��remove(lo, hi),����Ϊ�ᵼ�º��߸��Ӷȵ�O(n^2)
    //ÿ�ε���remove(r) = n - hi = O(n),����ʵ��remove(lo, hi) = O(n^2)
    T remove(Rank r) //ɾ����Ϊr��Ԫ��
    {
        T e = _elem[r];//���ݱ�ɾ��Ԫ��
        remove(r, r + 1);//��������ɾ���㷨����Ч�ڶ�����[r, r + 1)��ɾ��
        return e;//���ر�ɾ��Ԫ��
    }
    int remove(Rank lo, Rank hi) //ɾ����������[lo, hi)֮�ڵ�Ԫ��
    {
        if (lo == hi)//����Ч�ʿ��ǣ����������˻����������remove(0, 0)
        {
            return 0;
        }

        while (hi < _size)//[hi, _size)˳��ǰ��hi - lo����Ԫ
        {
            _elem[lo++] = _elem[hi++];
        }
        _size = lo;//���¹�ģ��ֱ�Ӷ���β��[lo, _size = hi)����
        shrink();//���б�Ҫ��������
        return hi - lo;//���ر�ɾ��Ԫ�ص���Ŀ
    }

    Rank insert(Rank r, T const& e) //����Ԫ��
    {
        expand();//����б�Ҫ������
        for (int i = _size; i > r; --i)
        {
            _elem[i] = _elem[i - 1];
        }
        _elem[r] = e;
        ++_size;

        return r;
    }
    Rank insert(T const& e) { return insert(_size, e); } //Ĭ����ΪĩԪ�ز���
    void sort(Rank lo, Rank hi); //��[lo, hi)����
    void sort() { sort(0, _size); } //��������
    void unsort(Rank lo, Rank hi); //��[lo, hi)����
    void unsort() { unsort(0, _size); } //��������

    //����Ԫ��ɾ�����ܹ���֤��ȷ�ԣ������ܵ�ʱ��Ч��ΪO(n^2)
    //whileѭ���ڲ�find + remove�ܵ�ʱ�临�Ӷ�ΪO(n),whileʱ�临�Ӷ�ΪO(n)
    int deduplicate() //����ȥ��
    {
        int oldSize = _size;//����ԭʼ��ģ
        Rank i = 1;//��_elem[1]��ʼ
        while (i < _size)//��ǰ����Ѱ��_elem[i]
        {
            (find(_elem[i], 0, i) < 0)//��ǰ׺��Ѱ����ͬ��
                ? ++i//����ͬ����������
                : remove(i);//����ɾ����ͬ��
        }

        return oldSize - _size;//����ɾ��Ԫ������
    }

    //����ȥ��ʱ�临�Ӷ�ΪO(n)
    int uniquify() //����ȥ��
    {
        Rank i = 0, j = 0;
        while (++j < _size)//��һɨ�裬ֱ��ĩԪ��
        {
            //������ͬ�ߣ����ֲ�ͬԪ��ʱ����ǰ��������ǰ���Ҳ�
            if (_elem[i] != _elem[j])
            {
                _elem[++i] = _elem[j];//O(1)
            }
        }

        _size = ++i;//��ȡβ������Ԫ��
        shrink();
        return j - i;//ɾ��Ԫ�ظ���
    }


    // ����
    void traverse(void(*visit) (T&)) //������ʹ�ú���ָ�룬ֻ����ֲ����޸ģ�
    {
        for (int i = 0; i < _size; ++i)
        {
            visit(_elem[i]);
        }
    }
    template <typename VST>
    void traverse(VST& visit) //������ʹ�ú������󣬿�ȫ�����޸ģ�
    {
        for (int i = 0; i < _size; ++i)
        {
            visit(_elem[i]);
        }
    }

}; //Vector
