#ifndef NODE
#define NODE

class Node
{
protected:
    Node *_next; //next node
    Node *_prev; //prev node
public:
    Node(void);
    virtual ~Node (void);
    Node *next(void);
    Node *prev(void);
    Node *insert(Node*); //insert node after current node
    Node *remove(void); //delete node from list and returns his pointer
    void splice(Node*); //splicing lists
};

#endif // NODE

