#include <stdlib.h>
#include <stdio.h>
#include "../inc/list.h"
#include "../inc/intern_list.h"
#include"../inc/macros.h"

#define MAGICNUMBER 0xDEADFA11
#define TRUE 1
#define FALSE 0
#define DEALLOCATED 0






static List_Result ListPop(List* _list, void** _pItem, int _isHead);
static List_Result List_Push(List* _list, void* _item, int _isHead);

List* List_Create(void)
{
	List* newlist;

	newlist = calloc(1, sizeof(List));
	CHECK_EQUAL_RETURN(NULL,newlist,NULL);

	(newlist->m_head).m_next = &(newlist->m_tail);
	(newlist->m_tail).m_prev = &(newlist->m_head);

	newlist->m_magicNumber = MAGICNUMBER;

	return newlist;
}

void List_Destroy(List** _pList, void (*_elementDestroy)(void* _item))
{
	Node* temp;

	if(NULL != _pList  &&  NULL != *_pList  && MAGICNUMBER == (*_pList)->m_magicNumber  )
	{
		temp = ((*_pList)->m_head).m_next;

		if(_elementDestroy != NULL)
		{
			while(temp != &((*_pList)->m_tail))
			{
				_elementDestroy(temp->m_item);
				temp = temp->m_next;
				free(temp->m_prev);
			}
		}
		else
		{
			while(temp != &((*_pList)->m_tail))
			{
				temp = temp->m_next;
				free(temp->m_prev);
			}
		}

		(*_pList)->m_magicNumber = 0;
		free(*_pList);
		*_pList = NULL;
	}
return;
}

List_Result List_PushHead(List* _list, void* _item)
{
	return List_Push(_list, _item, 1);
}

List_Result List_PushTail(List* _list, void* _item)
{
	return List_Push(_list, _item, 0);
}

List_Result List_PopHead(List* _list, void** _pItem)
{
	return ListPop(_list, _pItem, 1);
}

List_Result List_PopTail(List* _list, void** _pItem)
{
	return ListPop(_list, _pItem, 0);
}


size_t List_Size(const List* _list)
{
	CHECK_EQUAL_RETURN(NULL,_list,0);

return _list->m_numOfItems;
}

static List_Result ListPop(List* _list, void** _pItem, int _isHead)
{
	Node* temp;

	CHECK_EQUAL_RETURN(NULL,_list,LIST_UNINITIALIZED_ERROR);
	CHECK_NOTEQUAL_RETURN(MAGICNUMBER,_list->m_magicNumber,LIST_UNINITIALIZED_ERROR);
	CHECK_EQUAL_RETURN(NULL,_pItem,LIST_NULL_ELEMENT_ERROR);
	CHECK_EQUAL_RETURN(0,_list->m_numOfItems,LIST_UNDERFLOW);

	temp = (_isHead == TRUE) ? (_list->m_head).m_next : (_list->m_tail).m_prev;

	temp->m_prev->m_next = temp->m_next;
	temp->m_next->m_prev = temp->m_prev;

	*_pItem = temp->m_item;
	free(temp);
	--_list->m_numOfItems;

return LIST_SUCCESS;
}

static List_Result List_Push(List* _list, void* _item, int _isHead)
{
	Node* newNode;
	CHECK_EQUAL_RETURN(NULL,_list,LIST_UNINITIALIZED_ERROR);
	CHECK_NOTEQUAL_RETURN(MAGICNUMBER,_list->m_magicNumber,LIST_UNINITIALIZED_ERROR);
	CHECK_EQUAL_RETURN(NULL,_item,LIST_NULL_ELEMENT_ERROR);


	newNode = (Node*) malloc(sizeof(Node));
	CHECK_EQUAL_RETURN(NULL,newNode,LIST_ALLOCATION_ERROR);

	newNode->m_item = _item;
	newNode->m_next = (_isHead == TRUE) ? _list->m_head.m_next : &(_list->m_tail);
	newNode->m_prev = (_isHead == TRUE) ? &(_list->m_head) : _list->m_tail.m_prev;
	newNode->m_prev->m_next = newNode;
	newNode->m_next->m_prev = newNode;

	++_list->m_numOfItems;

return LIST_SUCCESS;
}
