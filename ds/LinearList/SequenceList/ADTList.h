#ifndef ADTList_H
#define ADTList_H

#include "stdlib.h"
#include <iostream>

template <class Type> 
class ADTList 
{
public:
	enum { DEFAULT_SIZE = 100 };
	ADTList(int size = DEFAULT_SIZE);
	~ADTList();
	bool IsEmpty();
	void Clear();
	bool GetValue(int seat,Type &val);
	bool Insert(int seat, Type val);
	void Print();
	bool Delete(int seat);
private:
	int size_;
	int length_;
	Type *data_;
};

template <class Type>
ADTList<Type>::ADTList(int size):
	data_(nullptr),
	size_(0),
	length_(0)
{
	data_ = (Type *)malloc(size*sizeof(Type));
	if (!data_) {
		return ;
	} else {
		memset(data_,0,size*sizeof(Type));
		size_ = size;
	}
}

template <class Type>
ADTList<Type>::~ADTList() {
	free(data_);
}

template <class Type>
bool ADTList<Type>::IsEmpty() {
	return length_ == 0;
}

template <class Type>
void ADTList<Type>::Clear() {
	memset(data_,0,length_ * sizeof(Type));
	length_ = 0;
}

template <class Type>
bool ADTList<Type>::GetValue(int seat,Type &val) {
	if(seat < 0 || seat >= length_) {
		return false;
	} 
	val = *(data_ + seat);
	return true;
}

template <class Type>
bool ADTList<Type>::Insert(int seat,Type val) {
	if(seat < 0 || seat > length_) {
		return false;
	}
	if(++length_ > size_) {
		data_ = (Type *)realloc(data_,length_*sizeof(Type));
	}
	if(seat == length_ - 1) {
		data_[seat] = val;
		return true;
	}
	for(int i=length_;i>seat;i--) {
		data_[i] = data_[i-1];
	}
	data_[seat] = val;
	return true;
}

template <class Type>
void ADTList<Type>::Print() {
	for(int i=0; i<length_ ;i++) {
		std::cout<< data_[i] << std::endl;
	}
}

template <class Type>
bool ADTList<Type>::Delete(int seat) {
	if(seat < 0 || seat >= length_) {
		return false;
	}
	length_--;
	if(length_ > size_ - DEFAULT_SIZE/2) {
		data_ = (Type*)realloc(data_,(length_+1)*sizeof(Type));
	}
	if(seat == length_) {
		return true;
	}	
	for(int i=seat;i<length_;i++) {
		data_[i] = data_[i+1];
	}
	return true;
}
#endif
		
	
