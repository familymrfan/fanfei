#include <iostream>
#include <cstdlib>

using namespace std;

template <class Type>
class Stack
{
	enum { DEFAULT_SIZE = 100 };
public:
	template <class TypeObj>
	friend	ostream& operator<<(ostream& os,TypeObj& object);

	Stack(int size = DEFAULT_SIZE) {
		top_ = data_ = (Type*)malloc(size*sizeof(Type));
		size_ = size;
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

	Type Top() const {
		return *top_;
	}

	void Push(Type data) {
		if(++length_>size_) {
			data_ = (Type*)realloc(data_,(size_+DEFAULT_SIZE)*sizeof(Type));
		}
		*++top_ = data;
	}

	void Pop(Type data) {
		if(length_ == 0) {
			return ;
		}
		length_--;
		top_--;
		if(length_ < size_/2) {
			data_ = (Type*)realloc(data_,length_*sizeof(Type));
		}
	}

	
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
	int size_;
};

template <class Type>
ostream& operator<<(ostream& os,Type& object) {
	object.Print();
	return os;
}
