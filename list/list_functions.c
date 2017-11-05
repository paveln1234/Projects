#include <stdlib.h>
#include "../inc/list.h"
#include "../inc/intern_list.h"
#include "../inc/list_itr.h"
#include "../inc/macros.h"
#include "../inc/list_functions.h"
#define TRUE 1
#define FALSE 0


/* internal function*/
static void swap (ListItr _item, ListItr _item2);
static void InsertBefore(Node* _inserted, Node* _dest);


ListItr ListItr_FindFirst(ListItr _begin, ListItr _end, PredicateFunction _predicate, void* _context)
{
    CHECK_EQUAL_RETURN(NULL,_begin,NULL);
    CHECK_EQUAL_RETURN(NULL,_end,NULL);
    CHECK_EQUAL_RETURN(NULL,_predicate,NULL);

	while(_begin != _end)
	{
		if(_predicate(ListItr_Get(_begin), _context) )
		{
			return _begin;
		}
		_begin = ListItr_Next(_begin);
	}

return _end;
}

size_t ListItr_CountIf(ListItr _begin, ListItr _end, PredicateFunction _predicate, void* _context)
{
	size_t nElements = 0;

    CHECK_EQUAL_RETURN(NULL,_begin,FALSE);
    CHECK_EQUAL_RETURN(NULL,_end,FALSE);
    CHECK_EQUAL_RETURN(NULL,_predicate,FALSE);

	while(_begin != _end)
	{

		if(_predicate(ListItr_Get(_begin), _context))
		{
			++nElements;
		}
		_begin = ListItr_Next(_begin);
	}

	return nElements;
}

ListItr ListItr_ForEach(ListItr _begin, ListItr _end, ListActionFunction _action, void* _context)
{
    CHECK_EQUAL_RETURN(NULL,_begin,NULL);
    CHECK_EQUAL_RETURN(NULL,_end,NULL);
    CHECK_EQUAL_RETURN(NULL,_action,NULL);

	while(_begin != _end && _action(ListItr_Get(_begin), _context) )
	{
		_begin = ListItr_Next(_begin);
	}

return _begin;
}

void ListItr_Sort(ListItr _begin, ListItr _end, LessFunction _less)
{
	ListItr  nextItr;
	ListItr  tempBegin = _begin;
	int swaps = 1;

    CHECK_EQUAL_VOID_RETURN(NULL,_begin);
    CHECK_EQUAL_VOID_RETURN(NULL,_end);
    CHECK_EQUAL_VOID_RETURN(NULL,_less);

	while(swaps)
	{
		swaps = 0;
		while((nextItr = ListItr_Next(_begin)) != _end)
		{
			;
			if(_less(ListItr_Get(_begin), ListItr_Get(nextItr)))
			{
				swap(_begin,nextItr);
				++swaps;
			}
			_begin = nextItr;
		}
		_begin = tempBegin;
	}

return;
}

ListItr ListItr_Splice(ListItr _dest, ListItr _begin, ListItr _end)
{
	CHECK_EQUAL_RETURN(NULL,_begin,NULL);
    CHECK_EQUAL_RETURN(NULL,_end,NULL);
    CHECK_EQUAL_RETURN(NULL,_dest,NULL);

	((Node*)_begin)->m_prev->m_next = _end;
	((Node*)_end)->m_prev = ((Node*)_begin)->m_prev;

return (ListItr) _dest;
}


ListItr ListItr_Merge(ListItr _destBegin, ListItr _firstBegin, ListItr _firstEnd, ListItr _secondBegin, ListItr _secondEnd, LessFunction _less)
{
	CHECK_EQUAL_RETURN(NULL,_destBegin,NULL);
	CHECK_EQUAL_RETURN(NULL,_firstBegin,NULL);
	CHECK_EQUAL_RETURN(NULL,_firstEnd,NULL);
	CHECK_EQUAL_RETURN(NULL,_secondBegin,NULL);
	CHECK_EQUAL_RETURN(NULL,_secondEnd,NULL);

	if(_less != NULL)
	{
		while(_firstBegin != _firstEnd && _secondBegin != _secondEnd)
		{
			if(_less(_firstBegin, _secondBegin))
			{
				InsertBefore(_firstBegin, _destBegin);
			}
			else
			{
				InsertBefore(_secondBegin, _destBegin);
			}

			_firstBegin = ListItr_Next(_firstBegin);
			_secondBegin =ListItr_Next(_secondBegin);
		}
	}

	while(_firstBegin != _firstEnd)
	{
		InsertBefore(_firstBegin, _destBegin);
		_firstBegin = ListItr_Next(_firstBegin);
	}

	while(_secondBegin != _secondEnd)
	{
		InsertBefore(_secondBegin, _destBegin);
		_secondBegin =ListItr_Next(_secondBegin);
	}

return _destBegin;
}

List* ListItr_Cut(ListItr _begin, ListItr _end)
{
	List* newList;
	void*  temp;
	ListItr  newEnd;

	CHECK_EQUAL_RETURN(NULL,_begin,NULL);
	CHECK_EQUAL_RETURN(NULL,_end,NULL);

	newList = List_Create();
	CHECK_EQUAL_RETURN(NULL,newList,NULL);
	newEnd = ListItr_End(newList);

	while(_begin != _end)
	{
		temp = ListItr_Remove(_begin);
		ListItr_InsertBefore(newEnd,temp);
		_begin = ListItr_Next(_begin);
	}

return newList;
}

List* ListItr_Unique(ListItr _begin, ListItr _end, EqualsFunction _equals)
{
	List* newList;
	void*  temp;
	ListItr  nextItr,newEnd;

	CHECK_EQUAL_RETURN(NULL,_begin,NULL);
	CHECK_EQUAL_RETURN(NULL,_end,NULL);
	CHECK_EQUAL_RETURN(NULL,_equals,NULL);

	newList= List_Create();
	CHECK_EQUAL_RETURN(NULL,newList,NULL);
	newEnd = ListItr_End(newList);

	while((nextItr = ListItr_Next(_begin) )!= _end)
	{

		if(_equals(ListItr_Get(_begin), ListItr_Get(nextItr)))
		{
			temp = ListItr_Remove(_begin);
			ListItr_InsertBefore(newEnd,temp);
		}
		_begin = nextItr;
	}

return newList;
}

static void InsertBefore(Node* _inserted, Node* _dest)
{
	_inserted->m_next = _dest;
	_inserted->m_prev = _dest->m_prev;
	_inserted->m_next->m_prev = _inserted;
	_inserted->m_prev->m_next = _inserted;
}


static void swap (ListItr _item, ListItr _item2)
{
	void* temp ;
	temp = ListItr_Get(_item);
	ListItr_Set(_item,ListItr_Get(_item2));
	ListItr_Set(_item2,temp);

return;
}
