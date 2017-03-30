#ifndef TREE_NODE
#define TREE_NODE

#include <iostream>

template<class T>
class SearchTree;

template<class T>
class BraidedSearchTree;

template<class T>
class TreeNode
{
protected:
    TreeNode* _lchild;
    TreeNode* _rchild;
    T val;
public:
    TreeNode(T v)
    {
        val = v;
        _lchild = NULL;
        _rchild = NULL;
    }

    virtual ~TreeNode(void)
    {
        if (_lchild) delete _lchild;
        if (_rchild) delete _rchild;
    }

    friend class SearchTree<T>;       
    friend class BraidedSearchTree<T>; 
};

template<class T>
class SearchTree
{
private:
    TreeNode<T> *root;
    int (*cmp) (T, T); //pointer to function which returns the int type
    TreeNode<T> *_findMin(TreeNode<T> *n)
    {
        if (n  == NULL)
            return NULL;
        while (n->_lchild)
            n = n->_lchild;
        return n;
    }

    void _remove(T val, TreeNode<T> * &n)
    {
        if (n == NULL)
            return;
        int result = (*cmp) (val, n->val);
        if (result < 0)
            _remove(val, n->_lchild);
        else
            if (result > 0)
                _remove (val, n->_rchild);
            else
            {                              // case 1
                if (n->_lchild == NULL)
                {
                    TreeNode<T> *old = n;
                    n = old->_rchild;
                    delete old;
                }
                else
                    if (n->_rchild == NULL)
                    {     // случай 2
                        TreeNode<T> *old = n;
                        n = old->_lchild;
                        delete old;
                    }
                    else
                    {	                          // case 3
                        TreeNode<T> *m = _findMin(n->_rchild);
                        n->val = m->val;
                        _remove(m->val, n->_rchild);
                    }
            }
    }

    void _inorder(TreeNode<T> *n, void (*visit) (T) )
    {
        if (n)
        {
            _inorder (n->_lchild, visit);
            (*visit) (n->val);
            _inorder (n->_rchild, visit);
        }
    }

public:
    SearchTree ( int (*c) (T, T) )
    {
        root = NULL;
        cmp = c;
    }

    ~SearchTree (void)
    {
        if (root) delete root;
    }

    int isEmpty (void)
    {
        return (root == NULL);
    }

    T find(T val)
    {
        TreeNode<T> *n = root;
        while (n)
        {
            int result = (*cmp) (val, n->val);
            if (result < 0)
                n = n->_lchild;
            else
                if (result > 0)
                    n = n->_rchild;
                else
                    return n->val;
        }
        return  NULL;
    }

    T findMin(void)
    {
        TreeNode<T> *n = _findMin (root);
        return (n ? n->val : NULL);
    }

    void inorder ( void (*visit) (T) )
    {
        _inorder(root, visit);
    }

    void insert(T val)
    {
        if (root == NULL)
        {
            root = new TreeNode<T>(val);
            return;
        }
        else
        {
            int result;
            TreeNode<T> *p, *n = root;
            while (n)
            {
                p = n;
                result = (*cmp) (val, p->val);
                if (result < 0)
                    n = p->_lchild;
                else
                    if (result > 0)
                        n = p->_rchild;
                    else
                        return;
            }
            if (result < 0)
                p->_lchild = new TreeNode<T>(val);
            else
                p->_rchild = new TreeNode<T>(val);
        }
    }

    void remove(T val)
    {
        _remove(val, root);
    }

    T removeMin (void)
    {
        T v = findMin();
        remove(v);
        return v;
    }
};

template<class T>
void heapSort (T s[], int n, int(*cmp) (T, T) );

#endif // TREE_NODE

