#include <stdlib.h>
#include "../inc/intern_list.h"
#include "../inc/list_itr.h"
#include "../inc/macros.h"

ListItr ListItr_Begin(const List* _list)
{
	return (ListItr)(_list->m_head).m_next;
}

ListItr ListItr_End(const List* _list)
{
	return (ListItr) &(_list->m_tail);
}

int ListItr_Equals(const ListItr _a, const ListItr _b)
{
	return (_a == _b);
}

ListItr ListItr_Next(ListItr _itr)
{
	return ((Node*)_itr)->m_next == NULL ? _itr : (ListItr) (((Node*)_itr)->m_next);
}

ListItr ListItr_Prev(ListItr _itr)
{
	return ((Node*)_itr)->m_prev == NULL ? _itr : (ListItr) (((Node*)_itr)->m_prev);
}

void* ListItr_Get(ListItr _itr)
{
	return (((Node*)_itr)->m_item);
}

void* ListItr_Set(ListItr _itr, void* _element)
{
	void* item;

    /*cause function insert items  NULL check requirer*/

	CHECK_EQUAL_RETURN(NULL,_itr,NULL);
	CHECK_EQUAL_RETURN(NULL,_element,NULL);

	CHECK_EQUAL_RETURN(NULL,((Node*)_itr)->m_next,NULL);
	CHECK_EQUAL_RETURN(NULL,((Node*)_itr)->m_prev,NULL);

	item = ((Node*)_itr)->m_item;
	((Node*)_itr)->m_item = _element;

return item;
}

ListItr ListItr_InsertBefore(ListItr _itr, void* _element)
{
	Node* newNode;

	CHECK_EQUAL_RETURN(NULL,_itr,NULL);
	CHECK_EQUAL_RETURN(NULL,_element,NULL);
	CHECK_EQUAL_RETURN(NULL,((Node*)_itr)->m_next,NULL);
	CHECK_EQUAL_RETURN(NULL,((Node*)_itr)->m_prev,NULL);

	newNode = (Node*) malloc(sizeof(Node));
	if(NULL == newNode)
	{
		return NULL;
	}

	newNode->m_item = _element;
	newNode->m_next = (Node*)_itr;
	newNode->m_prev = ((Node*)_itr)->m_prev;
	newNode->m_prev->m_next = newNode;
	newNode->m_next->m_prev = newNode;

return (ListItr) newNode;
}

void* ListItr_Remove(ListItr _itr)
{
	void* item;
	if(NULL == _itr)
	{
		return NULL;
	}

	item = ((Node*)_itr)->m_item;
	((Node*)_itr)->m_next->m_prev = ((Node*)_itr)->m_prev;
	((Node*)_itr)->m_prev->m_next = ((Node*)_itr)->m_next;
	free(_itr);

return item;
}









































































