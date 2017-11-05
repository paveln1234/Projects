#ifndef __LISTitr_H__
#define __LISTitr_H__
/**
 *  @file list_itr.h
 *
 *  @brief internal function to double linkend list
 *
 *  @details Implemented as double linked list using itertator to list items.
 *  Nodes are allocated from heap an store pointer to user proveded element.
 *
 *  @warning none of the function checking if the interators are in ligal Node structor.
 *
 *  @author Author MuhammadZ (muhammadz@experis.co.il)
 *
 *  @bug No known bugs.
 */

#include "../inc/list.h"
typedef void* ListItr;



/**
 * @brief Get itertator to the list's beginning
 *
 * @params _list : list to return begin iterator, pointing at first element
 *                 or at the end if list is empty
 * @return iterator pointing at the list's beginning
 */

ListItr ListItr_Begin(const List* _list);

/**
 * @brief Get itertator to the list end
 *
 * @params _list : list to return end iterator
 * @return an iterator pointing at the list's end
 */
ListItr ListItr_End(const List* _list);

/**
 * @brief retruns none zero if _a and _b iterators refer to same node
 * @params ListItr _a : interator to Node
 * @params ListItr _b : interator to Node
 * @warning might be implemented as a macro
 */
int ListItr_Equals(const ListItr _a, const ListItr _b);

/**
 * @brief Get itertator to the next element from a given iterator\\
 * @params ListItr _itr : interator to Node
 * @return an iterator pointing at the next element
 * @warning if _itr is end iterator it will be returned
 */
ListItr ListItr_Next(ListItr _itr);

/**
 * @brief Get itertator to the previous element
 * @params ListItr _itr : interator to Node
 * @return an iterator pointing at the previous element
 * @warning if _itr is begin iterator it will be returned
 */
ListItr ListItr_Prev(ListItr _itr);

/**
 * @brief Get data from the list node the iterator is pointing to
 *
 * @params _itr : A list iterator
 * @return the data the iterator is pointing at or NULL if pointing to the end
 */
void* ListItr_Get(ListItr _itr);

/**
 * @brief Set data at the node where the iterator is pointing at
 * @params ListItr _itr : A list iterator
 * @params void*_element : data to set
 * @return the data from the node to be changed
 */
void* ListItr_Set(ListItr _itr, void* _element);

/**
 * @brief Inserts a new node before node the iterator is pointing at
 * @params ListItr _itr : A list iterator
 * @params void*_element : data to set
 * @return an iterator pointing at the element inserted or NULL on error
 */
ListItr ListItr_InsertBefore(ListItr _itr, void* _element);

/**
 * @brief Removes the node the iterator is pointing at
 *
 * @params _itr : A list iterator
 * @return the removed data or NULL on error
 */
void* ListItr_Remove(ListItr _itr);

#endif /* __LISTitr_H__ */
