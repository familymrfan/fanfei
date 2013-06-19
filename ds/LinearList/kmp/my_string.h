#include <iostream>
using namespace std;

#pragma warning(disable:4996) 

const int maxLen = 128;

class String
{
public:
    String(const String& ob);
    String(const char * init);
    String();
    ~String() {
        delete [] ch_;
    }
    int Length() const {
        return curlen_;
    }

    int operator == (const String& ob) const {
        return strcmp(ch_, ob.ch_) == 0;
    }

    int operator != (const String& ob) const {
        return strcmp(ch_, ob.ch_) != 0;
    }

    int operator!() const {
        return curlen_ == 0;
    }

    String &operator = (const String& ob);
    String &operator += (const String& ob);

    char &operator[](int i);

    int Find(const String & pat) const;
    void Fail();
    int KmpFind(const String & pat) const;

    friend ostream& operator<<(ostream& os, const String& ob);
private:
    int curlen_;
    char *ch_;
    int f[maxLen];
};

String::String(const String& ob) {
    ch_ = new char[maxLen+1];
    if(!ch_) {
        cerr<< "Alloc Error"<<endl;
        exit(1);
    }
    curlen_ = ob.curlen_;
    strcpy(ch_,ob.ch_);
}

String::String(const char* init) {
    ch_ = new char[maxLen+1];
    if(!ch_) {
        cerr<< "Alloc Error"<<endl;
        exit(1);
    }
    curlen_ = strlen(init);
    strcpy(ch_,init);
}

String::String() {
    ch_ = new char[maxLen+1];
    if(!ch_) {
        cerr<< "Alloc Error"<<endl;
        exit(1);
    }
    curlen_ = 0;
    ch_[0] = '\0';
}

String &String::operator =(const String &ob) {
    if(&ob != this) {
        delete [] ch_;
        ch_ = new char[maxLen + 1];
        if(!ch_) {
            cerr<< "Alloc Error" <<endl;
            exit(1);
        }
        curlen_ = ob.curlen_;
        strcpy(ch_,ob.ch_);
    }
    return *this;
}

String &String::operator +=(const String &ob) {
    char * temp = ch_;
    curlen_ += ob.curlen_;
    ch_ = new char[maxLen+1];
    if(!ch_) {
        cerr<< "Alloc Error" <<endl;
        exit(1);
    }
    strcpy(ch_, temp);
    strcat(ch_, ob.ch_);
    delete []temp;
    return *this;
}

char &String::operator [](int i) {
    if(i<0 && i>=curlen_) {
        cerr<< "Out of memory" <<endl;
        exit(1);
    }
    return ch_[i];
}

int String::Find(const String& pat) const {
    char *p = pat.ch_, *s = ch_; int i =0;
    if(*p && *s){
        while(i<=curlen_-pat.curlen_) {
            if(*p++ == *s++) {
                if(! *p) return i;
            } 
            else {
                i++;
                s = ch_ + i;
                p = pat.ch_;
            }
        }
    }
    return -1;
}

void String::Fail() {
    int lengthP = curlen_;
    f[0] = -1;
    for(int j=1;j<lengthP;j++) {
        int i = f[j-1];
        while(ch_[j] != ch_[i+1] && i>=0) i = f[i];
        if(ch_[j] == ch_[i+1]) f[j] = i+1;
        else f[j] = -1;
    }
}

int String::KmpFind(const String& pat) const {
    int posP = 0, posT = 0;
    int lengthP = pat.curlen_;
    int lengthT = curlen_;

    while (posP<lengthP && posT<lengthT) {
        if(pat.ch_[posP] == ch_[posT]) {
            posP++;
            posT++;
        }
        else if (posP == 0){
            posT++;
        }
        else {
            posP = pat.f[posP-1]+1;
        }
    }
    if (posP<lengthP) {
        return -1;
    }
    else {
        return posT - lengthP;
    }


    return 0;
}

ostream& operator<<(ostream& os, const String& ob) {
    os<<ob.ch_;
    return os;
}