#include <iostream>
using namespace std;

#include "ADTStack.h"

template<class Type> class BinaryTree;
template<class Type> class BinaryTreeNode;

template<class Type>
class TreeIterator
{
public:
    typedef BinaryTree<Type> Tree;
    typedef BinaryTreeNode<Type> Node;
    typedef BinaryTreeNode<Type>* PNode;
    TreeIterator(Tree *tree):tree_(tree),current_(nullptr) {
    }
    virtual ~TreeIterator() {}
    virtual void Begin() = 0;
    virtual void operator ++() = 0;
    bool operator + () const {
        return current_ != nullptr;
    }
    Type operator () () const {
        if(current_) {
            return current_->GetData();
        }
        return 0;
    }
protected:
    Tree* tree_;
    PNode current_;
private:
    TreeIterator(const TreeIterator&) {}
    TreeIterator& operator == (const TreeIterator&) const;
};

template<class Type> 
struct StkNode
{
    BinaryTreeNode<Type> * node_;
    int pop_times_;
    StkNode(BinaryTreeNode<Type> *node = nullptr):node_(node),pop_times_(0) {}
};

template<class Type> class PostOrder:public TreeIterator<Type>
{
public:
    PostOrder(BinaryTree<Type> *tree):TreeIterator(tree) {

    }
    virtual void Begin() override {
        st.Clear();
        if(tree_->GetRoot() != nullptr) {
            st.Push(StkNode<Type>(tree_->GetRoot()));
        }
        operator ++();
    }
    virtual void operator ++ () override {
        if(st.IsEmpty()) {
            if(current_ == nullptr) {
                cerr<< "Advanced past end"<<endl;
            }
            current_ = nullptr;
            return ;
        }
        StkNode<Type> node;
        for (;;){
            node = st.Top();
            st.Pop();
            if(++node.pop_times_ == 3) {
                current_ = node.node_;
                return ;
            }
            st.Push(node);
            if(node.pop_times_ == 1) {
                if(node.node_->GetLeft() != nullptr) {
                    st.Push(StkNode<Type>(node.node_->GetLeft()) );
                }
            }
            else {
                if(node.node_->GetRight() != nullptr) {
                    st.Push(StkNode<Type>(node.node_->GetRight()) );
                }
            }
        }

    }
private:
    Stack<StkNode<Type>> st;
};

template<class Type>
class BinaryTreeNode
{
friend class BinaryTree<Type>;
public:
    BinaryTreeNode():leftchild_(nullptr),rightchild_(nullptr) {

    }
    BinaryTreeNode(Type data, 
                   BinaryTreeNode<Type> * left = nullptr,
                   BinaryTreeNode<Type> * right = nullptr):data_(data),
                                                           leftchild_(left),
                                                           rightchild_(right) {
    }
    Type GetData() const {
        return data_;
    }
    BinaryTreeNode<Type> * GetLeft() const {
        return leftchild_;
    }
    BinaryTreeNode<Type> * GetRight() const {
        return rightchild_;
    }
    void SetData(const Type& data) {
        data_ = data;
    }
    void SetLeft(BinaryTreeNode<Type>* left) {
        leftchild_ = left;
    }
    void SetRight(BinaryTreeNode<Type>* right) {
        rightchild_ = right;
    }
private:
    BinaryTreeNode<Type> *leftchild_, *rightchild_;
    Type data_;
};

template<class Type> class BinaryTree
{
public:
    typedef BinaryTreeNode<Type> * PNode;
    typedef BinaryTreeNode<Type> Node;
    BinaryTree(PNode root) {
        root_ = root;
    }
    virtual ~BinaryTree() {}

    const PNode GetRoot() const {
        return root_;
    }
    PNode GetLeft(PNode current = root_) {
        return current->GetLeft();
    } 
    PNode GetRight(PNode current = root_) {
        return current->GetRight();
    }
    void InOrder() {
        InOrder(root_);
    }
    void PreOrder() {
        PreOrder(root_);
    }
    void PostOrder() {
        PostOrder(root_);
    }
    void Size() {
        cout<<Size(root_);
    }
    void Height() {
        cout<<Height(root_);
    }
private:
    void InOrder(PNode current) {
        if(current) {
            InOrder(current->leftchild_);
            cout<<current->data_;
            InOrder(current->rightchild_);
        } 
    }
    void PreOrder(PNode current) {
        if(current) {
            cout<<current->data_;
            PreOrder(current->leftchild_);
            PreOrder(current->rightchild_);
        } 
    }
    void PostOrder(PNode current) {
        if(current) {
            PostOrder(current->leftchild_);
            PostOrder(current->rightchild_);
            cout<<current->data_;
        }
    }
    int Size(PNode current) {
        if(!current)
            return 0;
        return 1+Size(current->leftchild_)+Size(current->rightchild_);
    }
    int Height(PNode current) {
        if(!current)
            return 0;
        return 1+ max(Height(current->leftchild_),Height(current->rightchild_));
    }
    PNode root_;
};