#include "stdlib.h" /* malloc*/
#include "../inc/list.h"
#include "../inc/list_itr.h"
#include "../inc/stack.h"
#include "../inc/macros.h"
#define MAGICNUMBER 0xBAD22222

struct Stack
{
    List* list;
    size_t m_numOfItems;
    size_t m_magicNumber;
};

Stack* Stack_Create(void)
{
    List* newList;
    Stack* newStack;
    newStack = malloc(sizeof(Stack));
    CHECK_EQUAL_RETURN(NULL,newStack,NULL);

    newList = List_Create();
    if(newList == NULL)
    {
        free(newStack);
        return NULL;
    }

    newStack->list = newList;
    newStack->m_numOfItems = 0;
    newStack->m_magicNumber = MAGICNUMBER;

return newStack;
}


void Stack_Destroy(Stack** _pStack, void (*_elementDestroy)(void* _item))
{

    if(NULL != _pStack &&  NULL != *_pStack && MAGICNUMBER  == (*_pStack)->m_magicNumber )
    {

        List_Destroy(&(*_pStack)->list,_elementDestroy);
        (*_pStack)->m_magicNumber = 0;
        free(*_pStack);
        *_pStack = NULL;
    }
return;
}


Stack_Result Stack_Push(Stack* _stack, void*  _pItem)
{
    CHECK_EQUAL_RETURN(NULL,_stack,STACK_UNINITIALIZED_ERROR);
    CHECK_NOTEQUAL_RETURN(MAGICNUMBER,_stack->m_magicNumber,STACK_UNINITIALIZED_ERROR);
    CHECK_EQUAL_RETURN(NULL,_stack,STACK_NULL_ELEMENT_ERROR);

    if (List_PushHead(_stack->list,_pItem) != LIST_SUCCESS)
    {
        return STACK_ALLOCATION_ERROR;
    }

    ++_stack->m_numOfItems;

return STACK_SUCCESS;
}

Stack_Result Stack_Pop(Stack* _stack, void** _pItem)
{
    ListItr begin;

    CHECK_EQUAL_RETURN(NULL,_stack,STACK_UNINITIALIZED_ERROR);
    CHECK_NOTEQUAL_RETURN(MAGICNUMBER,_stack->m_magicNumber,STACK_UNINITIALIZED_ERROR);
    CHECK_EQUAL_RETURN(NULL,_stack,STACK_NULL_ELEMENT_ERROR);
    CHECK_EQUAL_RETURN(0,_stack->m_numOfItems,STACK_UNDERFLOW);

    begin = ListItr_Begin(_stack->list);
    *_pItem = ListItr_Remove(begin);
    if (NULL == *_pItem)
    {
        return STACK_UNINITIALIZED_ERROR;
    }
    --_stack->m_numOfItems;

return STACK_SUCCESS;
}

Stack_Result Stack_Top(Stack* _stack, void** _pItem)
{
    ListItr begin;

    CHECK_EQUAL_RETURN(NULL,_stack,STACK_UNINITIALIZED_ERROR);
    CHECK_NOTEQUAL_RETURN(MAGICNUMBER,_stack->m_magicNumber,STACK_UNINITIALIZED_ERROR);
    CHECK_EQUAL_RETURN(NULL,_pItem,STACK_NULL_ELEMENT_ERROR);
    CHECK_EQUAL_RETURN(0,_stack->m_numOfItems,STACK_UNDERFLOW);

    begin = ListItr_Begin(_stack->list);
    *_pItem = ListItr_Get(begin);
    if (NULL == *_pItem)
    {
        return STACK_UNINITIALIZED_ERROR;
    }

return STACK_SUCCESS;
}

size_t Stack_Size(Stack* _stack)
{
    CHECK_EQUAL_RETURN(NULL,_stack,0);
    CHECK_NOTEQUAL_RETURN(MAGICNUMBER,_stack->m_magicNumber,0);

return _stack->m_numOfItems;
}
