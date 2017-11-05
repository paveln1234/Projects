#ifndef _TREE_H_
#define _TREE_H_

/*
* FILENAME :        tree.c
*
* DESCRIPTION :
*       the file manage binary tree
*
* AUTHOR :    Pavel Korolin        START DATE :    2 march 17
*/

typedef struct Tree Tree;

typedef enum Tree_ResultCode {
	TREE_SUCCESS,
	TREE_NOT_INITIALIZED,
	TREE_ALLOCATION_FAILED,
	TREE_NOT_FOUND
} Tree_ResultCode;



typedef enum Tree_Traverse
{
    PRE_ORDER,
    IN_ORDER,
    POST_ORDER
}Tree_Traverse;


/* the function create new tree
*   input -void
*   return  - pointer to new tree if success , NULL if failed*/
Tree* Tree_Create();

/* the function destroyed the tree and release memory
*   input -
*       Tree* - pointer to tree
*   return  - void*/
void Tree_Destroy(Tree* _tree);

/* the function insert data to tree.
*   input -
*       Tree* - pointer to tree
*       int - the data/
*   return  - if success TREE_SUCCESS
*          ERROR_NULL if the tree NULL
*          TREE_ALLOCATION_FAILED if failed create new node */
Tree_ResultCode Tree_Insert(Tree* _tree,int _data);

/*This function delete a leaf of tree
*   input -
*       Tree* - pointer to tree
*       int - the data/
*		void* -pointer to where the data removes
*   return  - if success TREE_SUCCESS
*          ERROR_NULL if the tree NULL
*		   TREE_NOT_FOUND if the data not Found in tree
*/

Tree_ResultCode Tree_Remove(Tree* _tree , int _data,void* _pNode);

/* the function search if data is in the tree
*   input -
*       Tree* - pointer to tree
*       int - the data to search
*   return  - if success return True/False.
*           if NULL will return 0*/
int Tree_IsDataFound(Tree* _tree,int _data);



/* the Function print the tree
*   input -
*       Tree* - pointer to tree
*       TreeTraverse - way to print
*   return  - void  */
void Tree_Print(Tree* _tree, Tree_Traverse _traverseMode);



#endif /* _TREE_H_ */
