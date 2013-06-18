#include <iostream>
using namespace std;

typedef struct
{
	float coef; //系数
	int expn;	//指数
}DataType;

struct Node;
typedef struct Node *PNode;
struct Node
{
	DataType info;
	PNode link;
};

typedef struct Node *LinkList;
typedef LinkList polynomial;

int cmp(DataType a, DataType b) {
    int flag;
    if (a.expn<b.expn) flag = -1;
    else if (a.expn==b.expn) flag = 0;
    else flag = 1;
    return flag;
}

void CreatePolyn(polynomial &p, int m) {
    polynomial r,s;
    p = new struct Node;
    r = p;
    for (int i=0;i<m;i++) {
        s = new struct Node;
        cout<<"输入系数和指数(指数由大到小):";
        cin>>s->info.coef>>s->info.expn;
        r->link = s;
        r = s;
    }
    r->link = nullptr;
}

polynomial AddPolyn(polynomial &pa, polynomial &pb) {
    polynomial newp = nullptr,p = nullptr,q = nullptr,endp = nullptr,prep = nullptr;
    float sum;
    p = pa->link;
    q = pb->link;
    while(p && q) {
        switch(cmp(p->info, q->info)) {
            case -1:
                if(newp == nullptr) {
                    prep = newp = q;
                    q = q->link;
                    endp = newp->link = p;
                }else {
                    if(p == endp) {
                        polynomial temp = q->link;
                        prep->link = q;
                        q->link = p;
                        prep = q;
                        q = temp;
                    } else {
                        endp->link = p;
                        prep = endp;
                        endp = p;
                        q = q->link;
                    }
                }
                break;
            case 0:
                sum = p->info.coef+q->info.coef;
                if(sum == 0) {
                    if(newp != nullptr){
                        endp = endp->link;
                        prep->link = endp;
                    }
                    p = p->link;
                    q = q->link;
                } else {
                    if(newp == nullptr) {
                        endp = prep = newp = p;
                    }
                    if(p == endp) {
                        p->info.coef = sum;
                        q = q->link;
                    }else {
                        q->info.coef = sum;
                        p = p->link;
                    }
                }
                break;
            case 1:
                if(newp == nullptr) {
                    prep = newp = p;
                    p = p->link;
                    endp = newp->link = q;
                }else {
                    if(q == endp) {
                        polynomial temp = p->link;
                        prep->link = p;
                        p->link = q;
                        prep = p;
                        p = temp;
                    } else {
                        endp->link = q;
                        prep = endp;
                        endp = q;
                        p = p->link;
                    }
                }
                break;
        } // switch
    } // while
    return newp;
}

void PrintPolyn(polynomial p){
    while(p){
        //输出系数和指数
        cout<<p->info.coef<<"("<<p->info.expn<<")";
        p=p->link;
    }
    cout<<endl;
}

int main() {
    int m,n;
    polynomial p,q;
    cout<<"请输入多项式pa的项数：";
    cin>>m;
    CreatePolyn(p,m);
    cout<<"请输入多项式pb的项数：";
    cin>>n;
    CreatePolyn(q,n);
    PrintPolyn(p->link);
    PrintPolyn(q->link);
    PrintPolyn(AddPolyn(p,q));
    system("pause");
    return 0;
}