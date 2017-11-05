#ifndef _INTERN_LIST_H_
#define _INTERN_LIST_H_
#include <stdlib.h>/* size_t*/
#include <pthread.h>
typedef struct Node Node;

struct Node
{
    void* m_item;
    Node* m_next;
    Node* m_prev;
};

struct List
{
    size_t m_magicNumber;
    Node m_head;
    Node m_tail;
    size_t m_numOfItems;
};



#endif /* _INTERN_LIST_H_*/
