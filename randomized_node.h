#ifndef RANDOMIZED_NODE
#define RANDOMIZED_NODE

#include <braided_node.h>
#include <iostream>
#include <cmath>
#include <cstdlib>

template<class T>
class RandomizedSearchTree;

template<class T>
class RandomizedNode : public BraidedNode<T>
{
protected :
    RandomizedNode *_parent;

    double _priority;

    void rotateRight(void)
    {
        RandomizedNode<T> *y = this;
        RandomizedNode<T> *x = y->lchild();
        RandomizedNode<T> *p = y->parent();
        y->_lchild = x->rchild();
        if (y->lchild() != NULL)
            y->lchild()->_parent = y;
        if (p->rchild() == y)
            p->_rchild = x;
        else
            p->_lchild = x;
        x->_parent = p;
        x->_rchild = y;
        y->_parent = x;
    }

    void rotateLeft(void)
    {
        RandomizedNode<T> *x = this;
        RandomizedNode<T> *y = x->rchild();
        RandomizedNode<T> *p = x->parent();
        x->_rchild = y->lchild();
        if (x->rchild() != NULL)
            x->rchild()->_parent = x;
        if (p->lchild() == x)
            p->_lchild = y;
        else
            p->_rchild = y;
        y->_parent = p;
        y->_lchild = x;
        x->_parent = y;
    }

    void bubbleUp(void)
    {
        RandomizedNode<T> *p = parent();
        if (priority() < p->priority() )
        {
            if (p->lchild() == this)
                p->rotateRight();
            else
                p->rotateLeft();
            bubbleUp();
        }
    }

    void bubbleDown(void)
    {
        float lcPriority = lchild() ? lchild()->priority () : 2.0;
        float rcPriority = rchild() ? rchild()->priority () : 2.0;
        float minPriority = (lcPriority < rcPriority) ? lcPriority : rcPriority;
        if (priority () <= minPriority)
            return;
        if (lcPriority < rcPriority)
            rotateRight();
        else
            rotateLeft();
        bubbleDown();
    }

public :
    RandomizedNode(T v, int seed = -1) : BraidedNode<T>(v)
    {
        if (seed != -1)
            srand(seed);
        _priority = (rand() % 32767) / 32767.0;
        _parent = NULL;
    }

    RandomizedNode<T>* rchild(void)
    {
        return (RandomizedNode<T>*)this->_rchild;
    }

    RandomizedNode<T>* lchild(void)
    {
        return (RandomizedNode<T>*)this->_lchild;
    }

    RandomizedNode<T>* next(void)
    {
        return (RandomizedNode<T>*)this->_next;
    }

    RandomizedNode<T>* prev(void)
    {
        return (RandomizedNode<T>*)this->_prev;
    }

    RandomizedNode<T>* parent(void)
    {
        return (RandomizedNode<T>* )_parent;
    }

    double priority(void)
    {
        return _priority;
    }

    friend class RandomizedSearchTree<T>;
};

template<class T>
class RandomizedSearchTree
{
private :
    RandomizedNode<T> *root;       // head node
    RandomizedNode<T> *win;        // window

    int (*cmp) (T, T);	             // compare function

    void _remove(RandomizedNode<T> *n)
    {
        n->_priority = 1.5;
        n->bubbleDown();
        RandomizedNode<T> *p = n->parent();
        if (p->lchild() == n)
            p->_lchild = NULL;
        else
            p->_rchild = NULL;
        if (win == n)
            win = n->prev();
        n->Node::remove();
        delete n;
    }

public :
    RandomizedSearchTree(int (*c) (T, T), int seed = -1) : cmp(c)
    {
        win = root = new RandomizedNode<T> (NULL, seed);
        root->_priority = -1.0;
    }

    ~RandomizedSearchTree (void)
    {
        delete root;
    }

    T next(void)
    {
        win = win->next();
        return win->val;
    }

    T prev (void)
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
        RandomizedNode<T> *n = root->next();
        while (n != root)
        {
            (*visit) (n->val);
            n = n->next();
        }
    }

    bool isFirst (void)
    {
        return (win == root->next() ) && (root != root->next ( ) );
    }

    bool isLast (void)
    {
        return (win == root->prev() ) && (root != root->next() );
    }

    bool isHead (void)
    {
        return (win == root);
    }

    bool isEmpty (void)
    {
      return (root == root->next() );
    }

    T find (T val)
    {
        RandomizedNode<T> *n = root->rchild();
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

    T findMin (void)
    {
        win = root->next();
        return win->val;
    }

    T locate (T val)
    {
        RandomizedNode<T> *b = root;
        RandomizedNode<T> *n = root->rchild();
        while (n)
        {
            int result = (*cmp) (val, n->val);
            if (result < 0)
                n = n->lchild();
            else
                if (result > 0)
                {
                    b = n;
                    n = n->rchild();
                }
                else
                {
                    win = n;
                    return win->val;
                }
        }
        win = b;
        return win->val;
    }

    T insert(T val)
    {
                                              // case 1
        int result = 1;
        RandomizedNode<T> *p = root;
        RandomizedNode<T> *n = root->rchild();
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
        win = new RandomizedNode<T>(val);
        win->_parent = p;
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
                                              //  case 2
        win->bubbleUp();
        return val;
    }

    void remove(void)
    {
        if (win != root)
            _remove(win);
    }

    T removeMin(void)
    {
        T val = root->next()->val;
        if (root != root->next() )
            _remove(root->next());
        return val;
    }

    T remove (T val)
    {
        T v = find (val);
        if (v)
        {
            remove();
            return v;
        }
        return NULL;
    }
};

#endif // RANDOMIZED_NODE

