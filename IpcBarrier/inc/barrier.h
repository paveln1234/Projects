#ifndef BARRIER_H_INCLUDED
#define BARRIER_H_INCLUDED

/**
 *  @file barrier.h
 *  @brief This file implements the "barrier" synchronization construct.
 *
 *  @details   This file implements the "barrier" synchronization construct.
 * 			    A barrier causes threads to wait until a set of threads has
 * 				all "reached" the barrier. The number of threads required is
 * 				set when the barrier is initialized, and cannot be changed
 * 				except by reinitializing.
 *
 *  @author Pavel Korolin
 *
 *  @bug No known bugs.
 */

#define THREAD_SP_NUM 4;
 /*Define Barrier_t struct */
 typedef struct Barrier_t Barrier_t;

 /*DefineActiont Function */
typedef void (*actionFunc)(void* _context);

/**
 * @brief Create new Barrier.
 * @param[in] size_t _capacity - capacity of the barrier (number of thread)
 * @return  in success  Barrier_t* ,in fail null.
 */
Barrier_t* Barrier_Create(size_t _capacity);

/**
 * @brief  Destroy provided barrier
 * @param[in] Barrier_t* _barrier - barrier to destroy
 * @return void.
 */
void Barrier_Destroy(Barrier_t* _barrier);


/**
 * @brief  collect thread until init size of barrier
 * @param[in] Barrier_t* _barrier - barrier to wait on it.
 * @return in success 0, in fail return -1 special thread 1 .
 */
int Barrier_Wait(Barrier_t* _barrier ,actionFunc _action, void* _context);


#endif /* BARRIER_H_INCLUDED*/
