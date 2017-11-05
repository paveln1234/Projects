#ifndef _OPERATOR_H_
#define _OPERATOR_H_

/**
 *  @file operator.h
 *  @brief set get function  for  operator data.
 *
 *  @details  set get function  for   operator data.
 *
 *  @author Pavel Korolin (paveln1234@gmail.com)
 *
 *  @bug No known bugs.
 */

  /*Define struct Operator Data */
typedef struct OperatorData_t OperatorData_t;

/*Define Enum SubScribeData Result */
typedef enum OperatorData_Result
{
    OPERATOR_DATA_SUCCESS,
    OPERATOR_DATA_UNINITIALIZED_ERROR
}OperatorData_Result;

/**
 * @brief The function create and init  Oparator Data.
 * @param[in] size_t _mmcMnc -MMC/MNC number of the Oparator.
 * @param[in] char* _opName -Operator brand name
 * @return in success OperatorData_t* in fail NULL.
 */
OperatorData_t* OperatorData_Creaty(size_t _mmcMnc,  char* _opName);

/**
 * @brief The function destroy given OperatorData_t.
 * @param[in] OperatorData_t* _ opData - OperatorData_t to destroy.
 * @return OperatorData_Result.
 */
OperatorData_Result OperatorData_Destroy(OperatorData_t* _opData);

/**
 * @brief The function Add sec  to in Call from Operator.
 * @param[in] OperatorData_t* _ opData - Operator to add.
 * @param[in] size_t _sec -seconds to add to given Operator;
 * @return OperatorData_Result.
 */
OperatorData_Result OperatorData_AddInCallFromOperator(OperatorData_t* _opData, size_t _sec);

/**
 * @brief The function return  In Call From Operator
 * @param[in] OperatorData_t* _ opData - Operator to add.
 * @param[in] size_t* _retVul -pointer  to return value.
 * @return OperatorData_Result.
 */
OperatorData_Result OperatorData_GetInCallFromOperator(OperatorData_t* _opData, size_t* _retVal);

/**
 * @brief The function Add sec  to out Call to Operator.
 * @param[in] OperatorData_t* _ opData - Operator to add.
 * @param[in] size_t _sec -seconds to add to given Operator;
 * @return OperatorData_Result.
 */
OperatorData_Result OperatorData_AddOutCallToOperator(OperatorData_t* _opData, size_t _sec);

/**
 * @brief The function return  Out Call To Operator
 * @param[in] OperatorData_t* _ opData - Operator to add.
 * @param[in] size_t* _retVul -pointer  to return value.
 * @return OperatorData_Result.
 */
 OperatorData_Result OperatorData_GetOutCallToOperator(OperatorData_t* _opData, size_t* _retVal);

/**
 * @brief The function Add sms  to in from to Operator.
 * @param[in] OperatorData_t* _ opData - Operator to add.
 * @param[in] size_t _sec -seconds to add to given Operator;
 * @return OperatorData_Result.
 */
OperatorData_Result OperatorData_AddInSmsFromOperator(OperatorData_t* _opData);

/**
 * @brief The function return  In Sms From Operator
 * @param[in] OperatorData_t* _ opData - Operator to add.
 * @param[in] size_t* _retVul -pointer  to return value.
 * @return OperatorData_Result.
 */
OperatorData_Result OperatorData_GetInSmsFromOperator(OperatorData_t* _opData, size_t* _retVal);

/**
 * @brief The function Add sms  to out from from Operator.
 * @param[in] OperatorData_t* _ opData - Operator to add.
 * @return OperatorData_Result.
 */
OperatorData_Result OperatorData_AddOutSmsToOperator(OperatorData_t* _opData);

/**
 * @brief The function return  Out Sms To Operator
 * @param[in] OperatorData_t* _ opData - Operator to add.
 * @param[in] size_t* _retVul -pointer  to return value.
 * @return OperatorData_Result.
 */
OperatorData_Result OperatorData_GetOutSmsToOperator(OperatorData_t* _opData, size_t* _retVal);

/**
 * @brief The function convert OperatorData  to str.
  * @param[in] OperatorData_t* _ opData - Operator to  convert.
 * @param[in] char* _buffer -buffer to return str;
 * @return OperatorData_Result.
 */
OperatorData_Result OperatorData_OperatorToStr(OperatorData_t* _opData, char*  _buffer);

/**
 * @brief The function set all filds to 0
 * @param[in] OperatorData_t* _ opData - Operator to reset.
 * @return OperatorData_Result.
 */
 OperatorData_Result OperatorData_OperatorReset(OperatorData_t* _opData);
#endif   /* _OPERATOR_H_*/
