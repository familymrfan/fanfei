#include <iostream>

const int DefaultSize = 100;
template <class Type>
class Array {
public:
	Array(int size = DefaultSize);
	Array(const Array<Type>& x);
	~Array() {delete []elements_;}
	Array<Type> & operator = (const Array<Type>& A);
	Type& operator[](int i);
	Type* operator*() const { return elements_;}
	int Length() const {return size_;}
	void ReSize(int size);
private:
	Type * elements_;
	int size_;
	void Alloc();
};

template <class Type> void Array<Type>::Alloc() {
	elements_ = new Type[size_];
	if(elements_ == 0) { 
		std::cerr<< "memory alloc error"<<std::endl;
		size_ = 0;
		return ;
	}
}

template <class Type> Array<Type>::Array(int size) {
	if (size <= 0) { 
		std::cerr<< "invalid array size"<<std::endl;
		size_= 0;
		return ;
	}
	size_ = size;
	Alloc();
}

template <class Type> Array<Type>::Array(const Array<Type> &x) {
	int n = x.size_;
	size_ = n;
	elements_ = new Type[n];
	
	if (elements_ == 0) {
	    std::cerr<< "memory alloc errir"<<std::endl;
	    size_ = 0;
	    return ;
	}
	
	Type* srcptr = x.elements_;
	Type* destptr= elements_;
	
	while(n--) *destptr++ = * srcptr++;
}

template <class Type> Type& Array<Type>::operator[](int i) {
	if (i<0 || i>size_-1 ) {
	    std::cerr<< "index out of range"<<std::endl;
	}
	
	return elements_[i];
}
 
template <class Type> void Array<Type>::ReSize(int size) {
	if (size<=0) std::cerr<< "invalid array size" <<std::endl;
	if(size != size_) {
	    Type* newarray = new Type[size];
	    if(newarray == 0) {
		std::cerr<< "memory alloc error"<<std::endl;
		return ;
	    }
	    
	    int n = (size <= size_) ? size : size_;
	    Type* srcptr = newarray;
	    Type* destptr= elements_;
	
	    while(n--) *destptr++ = *srcptr++;
	    delete []elements_;
	    elements_ = newarray;
	    size_ = size;  
	}
}


int main() {
    Array<int> array;
    for(int i=0;i<200;i++) {
	array[i] = i;
    }
    
    for(int i=0;i<10;i++) {
	std::cout<< array[i] << std::endl;
    }
    return 0;
}