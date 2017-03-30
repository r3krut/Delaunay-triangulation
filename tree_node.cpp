#include "tree_node.h"

template<class T>
void heapSort (T s[], int n, int(*cmp) (T, T) )
{
    SearchTree<T> t(cmp);
    for (int i = 0; i < n; i++)
        t.insert(s[i]);
    for (int i = 0; i < n; i++)
        s[i] = t.removeMin();
}
