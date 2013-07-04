#include <iostream>
using namespace std;

template<class Type> 
class MinPQ
{
public:
    virtual bool Insert(const Type& ) = 0;
    virtual bool RemoveMin(Type&) = 0;
};

template<class Type> 
class MinHeap : public MinPQ<Type>
{
    friend ostream& operator<< <Type>(ostream& os, const MinHeap<Type>& heap);
public:
    MinHeap(int maxSize);
    MinHeap(Type arr[], int n);
    ~MinHeap() { delete []heap_;}

    const MinHeap<Type> &operator=(const MinHeap& heap);
    bool Insert(const Type& x);
    bool RemoveMin(Type& x);
    int IsEmpty() const {
        return current_size_ == 0;
    }
    int IsFull() const {
        return current_size_ == max_size_; 
    }
    void Clear() {
        current_size_ = 0;
    }
private:
    enum { kDefaultSize = 10 };
    Type *heap_;
    int current_size_;
    int max_size_;
    void FilterDown(const int start, const int end_heap);
    void FilterUp(const int start);
};

template<class Type> MinHeap<Type>::MinHeap(int max_size) {
    max_size_ = kDefaultSize < max_size ? max_size_ : kDefaultSize;
    heap_ = new Type[max_size_];
    current_size_ = 0;
}

template<class Type> MinHeap<Type>::MinHeap(Type arr[], int n) {
    max_size_ = kDefaultSize < n ? n : kDefaultSize;
    heap_ = new Type[max_size_];
    int i = 0;
    while(i<n && i<max_size_) {
        heap_[i] = arr[i];
        i++;
    }
    current_size_ = n;
    int current_pos = (n-2)/2;
    while(current_pos >= 0) {
        FilterDown(current_pos, n-1);
        current_pos--;
    }
}

template<class Type> void MinHeap<Type>::FilterDown(const int start, const int end_heap) {
    int i = start,j = 2 * i + 1;
    Type temp = heap_[i];
    while(j <= end_heap) {
        if( j < end_heap && heap_[j] > heap_[j+1] ) j++;
        if( temp <= heap_[j] )
            break;
        else {
            heap_[i] = heap_[j];
            i = j;
            j = 2 * i + 1;
        }
    }
    heap_[i] = temp;
}

template <class Type> void MinHeap<Type>::FilterUp(const int start) {
    int j = start, i = (j - 1)/2;
    Type temp = heap_[j];
    while(j > 0) {
        if (heap_[i] <= temp ) break;
        else {
            heap_[j] = heap_[i];
            j = i;
            i = (j - 1)/2;
        }
        heap_[j] = temp;
    }
}

template <class Type> bool MinHeap<Type>::Insert(const Type& x) {
    if(current_size_ == max_size_) {
        return false;
    }

    heap_[current_size_] = x;
    FilterUp(current_size_);
    current_size_ ++;
    return true;
}

template <class Type> bool MinHeap<Type>::RemoveMin(Type& x) {
    if(current_size_ == 0) {
        return false;
    } 
    x = heap_[0];
    heap_[0] = heap_[current_size_ - 1];
    current_size_--;
    FilterDown(0, current_size_-1);
    return true;
}


template <class Type>
ostream& operator<<(ostream& os, const MinHeap<Type>& heap) {
    for(int i=0; i< heap.current_size_;i++) {
        os<<heap.heap_[i]<<endl;
    }
    return os; 
}

int main() {
    int a[] = {7,4,6,2,1};
    MinHeap<int> heap(a, 5);
    cout<<heap<<endl;
    heap.Insert(5);
    cout<<heap<<endl;
    system("pause");
	return 0;
}