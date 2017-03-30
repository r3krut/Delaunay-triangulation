#ifndef BRAIDED_NODE
#define BRAIDED_NODE

#include "tree_node.h"
#include "node.h"

using namespace std;

//BraidedNode
template<class T>
class BraidedNode : public TreeNode<T>, public Node
{
public:
    BraidedNode (T val) : TreeNode<T>(val)
    {

    }

    BraidedNode<T>* rchild (void)
    {
        return (BraidedNode<T> *)this->_rchild;
    }

    BraidedNode<T>* lchild (void)
    {
        return (BraidedNode<T>*)this->_lchild;
    }

    BraidedNode<T>* next (void)
    {
        return (BraidedNode<T> *)_next;
    }

    BraidedNode<T>* prev (void)
    {
        return (BraidedNode<T> *)_prev;
    }

    friend class BraidedSearchTree<T>;
};

template<class T>
class BraidedSearchTree
{
private:
    BraidedNode<T> *root;    // head node

    BraidedNode<T> *win;     // current window

    int (*cmp) (T, T);        // compare function

    void _remove(T val, TreeNode<T>* &n)
    {
        int result = (*cmp) (val, n->val);
        if (result < 0)
            _remove(val, n->_lchild);
        else
            if (result > 0)
                _remove(val, n->_rchild);
            else
            {                         // case 1
                if (n->_lchild == NULL)
                {
                    BraidedNode<T> *old = (BraidedNode<T>*)n;
                    if (win == old)
                        win = old->prev();
                    n = old->rchild();
                    old->Node::remove();
                    delete old;
                }
                else
                    if (n->_rchild == NULL)
                    { // case 2
                        BraidedNode<T> *old = (BraidedNode<T>*)n;
                        if (win == old)
                            win = old->prev();
                        n = old->lchild();
                        old->Node::remove();
                        delete old;
                    }
                    else
                    {                       // case 3
                        BraidedNode<T> *m = ( (BraidedNode<T>*)n)->next();
                        n->val = m->val;
                        _remove(m->val, n->_rchild);
                    }
            }
    }

public:
    BraidedSearchTree(int (*c) (T, T) )
    {
        cmp = c;
        win = root = new BraidedNode<T> (NULL);
    }

    ~BraidedSearchTree (void)
    {
        delete root;
    }

    T next (void)
    {
        win = win->next();
        return win->val;
    }

    T prev(void)
    {
        win = win->prev();
        return win->val;
    }

    T val (void)
    {
        return win->val;
    }

    void inorder (void (*visit) (T) )
    {
        BraidedNode<T> *n = root->next();
        while (n != root)
        {
            (*visit)(n->val);
            n = n->next();
        }
    }

    bool isFirst (void)
    {
        return (win == root->next() ) && (root != root->next ());
    }

    bool isLast (void)
    {
        return (win == root->prev() ) && (root != root->next() );
    }

    bool isHead (void)
    {
        return  (win == root);
    }

    bool isEmpty ()
    {
        return (root == root->next() );
    }

    T find(T val)
    {
        BraidedNode<T> *n = root->rchild();
        while (n)
        {
            int result = (*cmp) (val, n->val);
            if (result < 0)
                n = n->lchild();
            else
                if (result > 0)
                    n = n->rchild();
                else
                {
                    win = n;
                    return n->val;
                }
        }
        return NULL;
    }

    T findMin(void)
    {
        win = root->next();
        return win -> val;
    }

    T insert(T val)
    {
        int result = 1;
        BraidedNode<T> *p = root;
        BraidedNode<T> *n = root->rchild();
        while (n)
        {
            p = n;
            result = (*cmp) (val, p->val);
            if (result < 0)
                n = p->lchild();
            else
                if (result > 0)
                    n = p->rchild();
                else
                    return NULL;
        }
        win = new BraidedNode<T>(val);
        if (result < 0)
        {
            p->_lchild = win;
            p->prev()->Node::insert(win);
        }
        else
        {
            p->_rchild = win;
            p->Node::insert(win);
        }
        return val;
    }

    void remove(void)
    {
        if (win != root)
            _remove(win -> val, root -> _rchild);
    }

    T removeMin(void)
    {
        T val = root->next()->val;
        if (root != root->next() )
            _remove(val, root->_rchild);
        return val;
    }
};

#endif // BRAIDED_NODE
