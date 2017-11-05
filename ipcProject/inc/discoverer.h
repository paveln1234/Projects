#ifndef _DISCOVERER_H_
#define _DISCOVERER_H_


/**
 *  @file discoverer.h
 *  @brief The Discoverer module charge to find if there have any files in a given directory.
 *
 *  @details  The Discoverer search if new files add to directory that the user config to him to search in at.
 *            The Discoverer send every new file name throw given queue.
 *
 *  @author Pavel Korolin (paveln1234@gmail.com)
 *
 *  @bug No known bugs.
 */

/*Define structure Discoverer_t */
typedef struct Discoverer_t Discoverer_t;

/*Define Enum Discoverer_Result */
typedef enum Discoverer_Result
{
    DISCOVERER_SUCCESS,
    DISCOVERER_UNINITIALIZED_ERROR,
    DISCOVERER_ERRROR
}Discoverer_Result;


/**
 * @brief The function create and init Discoverer.
 * @param[in] void* m_cdrManager- pointer to cdr Manager neaded for insert to him the files.
 * @param[in] char* _inputFolderPath - path to input folder for search in her to cdr
 * @param[in] size_t _intervalTime - sleep time between searching for new files
 * @return in success Discoverer_t* in fail NULL.
 */
Discoverer_t* Discoverer_Creaty(void* _cdrManager,char* _inputFolderPath,char* _inprogressFolderPath,size_t _intervalTime);

/**
 * @brief The function destroy Discoverer_t
 * @param[in] Discoverer_t* _discoverer - Discoverer to Destroy.
 * @return Discoverer_Result.
 */
Discoverer_Result Discoverer_Destroy(Discoverer_t* _disoverer);

/**
 * @brief The function Run Discoverer module.
 * @param[in] Discoverer_t* _discoverer - Discoverer to Run.
 * @return Discoverer_Result.
 */
Discoverer_Result Discoverer_Run(Discoverer_t* _disoverer);

/**
 * @brief The function Pause Discoverer module.
 * @param[in] Discoverer_t* _discoverer - Discoverer to Pause.
 * @return Discoverer_Result.
 */
Discoverer_Result Discoverer_Pause(Discoverer_t* _disoverer);

/**
 * @brief The function Resume Discoverer module.
 * @param[in] Discoverer_t* _discoverer - Discoverer to Resume.
 * @return Discoverer_Result.
 */
Discoverer_Result Discoverer_Resume(Discoverer_t* _disoverer);


#endif /* _DISCOVERER_H_*/
