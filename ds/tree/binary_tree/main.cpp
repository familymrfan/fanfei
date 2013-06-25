#include "binary_tree.h"
#include <iostream>
using namespace std;

int main() {
    typedef BinaryTree<char> Tree;
	typedef Tree::PNode PNode;
    typedef Tree::Node Node;

    // init tree
    Node a('A'),b('B'),c('C'),d('D'),e('E'),f('F'),g('G');
    a.SetLeft(&b);
    b.SetLeft(&c);
    b.SetRight(&d);
    d.SetLeft(&e);
    d.SetRight(&f);
    e.SetRight(&g);
    /*      A
          |
          B
        |  |
        C  D
          | |
          E F
           |
           G
    */
    Tree t(&a);

    cout<<"InOrder"<<endl;

    t.InOrder();

    cout<<"\nPreOrder"<<endl;

    t.PreOrder();

    cout<<"\nPostOrder"<<endl;

    t.PostOrder();

    cout<<"\nSize"<<endl;

    t.Size();

    cout<<endl;

    cout<<"\nHeight"<<endl;

    t.Height();

    cout<<endl;

    PostOrder<char> po(&t);
    po.Begin();

    while (+po){
        cout<< po() << endl;
        ++po;
    }
    
	system("pause");
	return 0;
}