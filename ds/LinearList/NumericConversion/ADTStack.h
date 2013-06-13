#include <iostream>
#include <cstdlib>

using namespace std;

template <class Type>
class Stack
{
	enum { DEFAULT_SIZE = 100 };
public:
	friend	ostream& operator<< <Type>(ostream& os,Stack<Type>& object);

	Stack(int size = DEFAULT_SIZE) {
		top_ = data_ = (Type*)malloc(size*sizeof(Type));
		size_ = size;
		pre_size_ = 0;
		length_ = 0;
	}	

	~Stack() {
		free(data_);
	}

	void Clear() {
		top_ = data_;
		length_ = 0;
	}

	bool IsEmpty() {
		if(length_ == 0) {
			return true;
		}
		return false;
	}

	int Length() const {
		return length_;
	}

	Type* Top() const {
		if(length_ == 0) {
			return nullptr;
		}
		return top_;
	}

	void Push(Type data) {
		if(++length_>size_) {
			pre_size_ = size_;
			size_ += DEFAULT_SIZE;
			data_ = (Type*)realloc(data_,size_*sizeof(Type));
			top_  = data_ + length_-1;
		} else {
			top_++;
		}
		*top_ = data;
	}

	void Pop() {
		if (length_ == 0) {
			return ;
		}
		length_--;
		top_--;
		if (length_ == 0) {
			top_ = data_;
			return ;
		}
		if (length_ < pre_size_) {
			size_ = pre_size_;
			pre_size_ -= DEFAULT_SIZE;
			if (pre_size_ < 0) {
				pre_size_ = 0;
			}
			data_ = (Type*)realloc(data_,(size_)*sizeof(Type));
			top_ = data_ + length_-1;
		}
	}

	int size_;
protected:
	void Print() {
		Type* it = top_;
		while(top_>data_) {
			cout<< *top_ <<endl;
			top_--;
		}
	}
private:
	
	Type *top_;
	Type *data_;
	int length_;
	
	int pre_size_;
};

template <class Type>
ostream& operator<<(ostream& os,Stack<Type>& object) {
	object.Print();
	return os;
}
