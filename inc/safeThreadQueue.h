#ifndef SAFETHREADQUEUE_H_INCLUDED
#define SAFETHREADQUEUE_H_INCLUDED

/**
 *  @file safeThreadQueue.h
 *  @brief Queue is Linear  Sequential Access - First-in-First-out, the safe thread queue allow to work in multiThread inverment.
 *
 *  @details   A  safeTread Message Thread Queue is a First-In-First-Out (FIFO) safe thread queue save any  data type for the user.
                            the safe queue insert in head and remove from tail.
 *
 *  @author Pavel Korolin
 *
 *  @bug No known bugs.
 */

 /*Define Safe Tread Queue struct */
 typedef struct STQueueu_t STQueueu_t;

 /*Define Enum safeTread Queue Result*/
typedef enum STQueueu_Result
{
    SAFE_TREAD_QUEUE_SUCCESS,
	SAFE_TREAD_QUEUE_UNINITIALIZED_ERROR ,   /** Uninitialized queue error     */
	SAFE_TREAD_QUEUE_ALLOCATION_ERROR ,         /** Allocation error 	 		*/
	SAFE_TREAD_QUEUE_UNDERFLOW ,                     /** underflow error 	 		*/
	SAFE_TREAD_QUEUE_OVERFLOW  ,                           /** overflow error 	 		*/
	SAFE_TREAD_QUEUE_ITEM_ERROR                      /** item provided null */
}STQueueu_Result;


/*Define Enum For Error Flag */
typedef enum SafeThreadQueue_ErrorFlag
{
    TRUNCE,  /* write data anyway*/
    RETURN_ERROR  /* wont write data and return SAFE_TREAD_QUEUE_OVERFLOW*/
}SafeThreadQueue_ErrorFlag;
/*Define destroyFuncion - the function  destroy remaining items in queue  */
typedef void(*destroyFuncion)(void* _item);

/**
 * @brief Create new safeTread Message Tread Queue fixed size.
 * @param[in] size_t _size - max slots .
 * @return  in success  safeTreadQueue_t* ,in fail null.
 */
STQueueu_t* SafeThreadQueue_Create(size_t  _numOfSlots);

/**
 * @brief Destroy  safeTread Message Tread Queue
 * @param[in] SafeThreadQueue_t** _pQueue  -safeTread Tread Queue
 * @return STQueueu_Result
 */
STQueueu_Result SafeTreadQueue_Destroy(STQueueu_t*  _sQueue, destroyFuncion _destroyFuncion);
/**
 * @brief Enqueue new message to safeTread Message Tread Queue
 * @param[in] SafeThreadQueue_t*  _pQueue - SafeThreadQueue_t created by   safeTreadQueue_Create
 * @param[in]   void* _item -item to insert.
 * @warning thread will wait until free sapace to item avibale
 * @return STQueueu_Result.
 */
 STQueueu_Result SafeTreadQueue_Enqueue(STQueueu_t* _sQueue, void* _item);
 /**
 * @brief Dequeue message from safeTread Message Tread Queue
 * @param[in] SafeThreadQueue_t*  _pQueue - SafeThreadQueue_t created by   safeTreadQueue_Create
 * @param[in]  void** _item - pointer for return item
 * @return STQueueu_Result
 * @warning thread will wait until item avibale to get
 */
STQueueu_Result SafeTreadQueue_Dequeue(STQueueu_t* _sQueue, void** _item);


 /**
 * @brief the function return number of items have in queue
 * @param[in] SafeThreadQueue_t  _pQueue - SafeThreadQueue_t
 * @return number of items in Queue in error return  0
 */
size_t SafeTreadQueue_NumOfItemsInQueue(STQueueu_t* _sQueue);


#endif /* SAFETHREADQUEUE_H_INCLUDED */
