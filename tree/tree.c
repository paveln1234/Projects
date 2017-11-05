#include<stdio.h>
#include<stdlib.h>
#include "../inc/tree.h"
#define MAGICNUMBER 0xBEEFBEEF
#define REMOVEMAGICNUMBER 0xDEADBEEF

typedef struct Node Node;

static Node* insertToTree(Node* _root,Node* _temp);
static Node* NodeCreate(void* _data);
static Node* PrintTravelPreorder(Node* _root);
static Node* PrintTravelInorder(Node* _root);
static Node* PrintTravelPostOrder(Node* _root);
static void NodeDestroy (Node* _node);
static Node* Destroy(Node* _root);
static Node* FindData(Node* _root,void* _data, void* _reasolt);

struct Node
{
    void* m_data;
    Node* m_left;
    Node* m_right;
};

struct Tree
{
    Node* m_root;
    int m_magicNumber;

};


Tree* TreeCreate(void)
{
    Tree* root;
    root = (Tree*)malloc(sizeof(Tree));
    if(NULL == root)
    {
        return NULL;
    }
    root->m_magicNumber = MAGICNUMBER;
    root->m_root = NULL;
    return root;
}
ADTErr TreeInsert(Tree* _tree,int _data)
{
    if (NULL == _tree || MAGICNUMBER!=_tree->m_magicNumber)
    {
        return ERROR_NULL;
    }
    Node* temp;
    temp = NodeCreate(_data);
    if(NULL == temp)
    {
        return ERROR_MALLOC;
    }
    if(NULL == _tree->m_root)
    {
        _tree->m_root = temp ;
        return ERROR_OK;
    }
    if(_data < _tree->m_root->m_data)
    {
        _tree->m_root->m_left = insertToTree(_tree->m_root->m_left,temp);
    }else
    {
        _tree->m_root->m_right = insertToTree(_tree->m_root->m_right,temp);
    }

return ERROR_OK;
}
int TreeIsDataFound(Tree* _tree,void* _data)
{
    int reasolt = 0;
    if (NULL == _tree || MAGICNUMBER!=_tree->m_magicNumber)
    {
        return 0;
    }
   FindData(_tree->m_root,_data,&(reasolt));
    return reasolt;
}
/*search data in pre order search */
static Node* FindData(Node* _root,int _data, int* _reasolt)
{
    Node* temp = _root;
    if(temp == NULL)
    {
        return _root;
    }
    if (_data == temp->m_data)
    {
         *_reasolt = 1;
        return _root;
    }
    FindData(_root->m_left,_data,_reasolt);
    FindData(_root->m_right,_data,_reasolt);
    return _root;
}

void TreePrint(Tree* _tree, TreeTraverse _traverseMode)
{
    if (NULL == _tree || MAGICNUMBER!=_tree->m_magicNumber)
    {
        return ;
    }

    if(NULL == _tree)
    {
        return;
    }
    switch(_traverseMode)
    {
    case 0:
        PrintTravelPreorder(_tree->m_root);
        break;
    case 1:
        PrintTravelInorder(_tree->m_root);
        break;
    case 2:
        PrintTravelPostOrder(_tree->m_root);
    }

return;
}

static Node* PrintTravelPreorder(Node* _root)
{
    Node* temp = _root;
    if(temp == NULL)
    {
        return _root;
    }
    printf("%d,",temp->m_data);
    PrintTravelPreorder(_root->m_left);
    PrintTravelPreorder(_root->m_right);

    return _root ;
}
static Node* PrintTravelInorder(Node* _root)
{
    Node* temp = _root;
    if(temp == NULL)
    {
        return _root;
    }
    PrintTravelInorder(_root->m_left);
    printf("%d,",temp->m_data);
    PrintTravelInorder(_root->m_right);
    return _root ;
}
static Node* PrintTravelPostOrder(Node* _root)
{
    Node* temp = _root;
    if(temp == NULL)
    {
        return _root;
    }
    PrintTravelPostOrder(_root->m_left);
    PrintTravelPostOrder(_root->m_right);
    printf("%d,",temp->m_data);

    return _root ;
}

/*go on the tree rec and insert new node */
static Node* insertToTree(Node* _root,Node* _temp)
{
    Node* searchNode = _root ;
    if(searchNode == NULL)
    {
        return searchNode = _temp;

    }
    if(searchNode->m_data == _temp->m_data)
    {
        NodeDestroy(_temp);
        return NULL;
    }
    if( _temp->m_data < searchNode->m_data )
    {
        _root->m_left = insertToTree(searchNode->m_left,_temp);
    }else
    {
        _root->m_right = insertToTree(searchNode->m_right,_temp);
    }
    return _root;
}

void TreeDestroy(Tree* _tree)
{
    if (NULL == _tree || MAGICNUMBER!=_tree->m_magicNumber)
    {
        return ;
    }
    if(NULL !=_tree->m_root)
    {
        Destroy(_tree->m_root);
    }
    _tree->m_magicNumber = REMOVEMAGICNUMBER;
    free(_tree);
    return  ;
}

/*destroy the node by post oreder*/
static Node* Destroy(Node* _root)
{
    Node* searchNode = _root ;
    if(_root->m_left == NULL)
    {
        Destroy(_root->m_right);
        return NULL;
    }
    if(_root->m_right == NULL)
    {
        Destroy(_root->m_right);
        return NULL;
    }
    NodeDestroy(searchNode);
return _root;
}

static void NodeDestroy (Node* _node)
{
    free(_node);
    return ;
}

static Node* NodeCreate(void* _data)
{
    Node* temp;
    temp = (Node*)calloc(1,sizeof(Node));
    if(NULL == temp)
    {
        return (NULL);
    }
    temp->m_data =_data;
    return temp;
}
