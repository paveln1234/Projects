#ifndef OPARETORDS_H_INCLUDED
#define OPARETORDS_H_INCLUDED

/**
 *  @file operatorDs.h
 *  @brief operator Data structer is manager data structe .
 *
 *  @details  operator Data structer module are charge to manage input data from data manager, like set, get and Update.

 *  @author Pavel Korolin (paveln1234@gmail.com)
 *
 *  @bug No known bugs.
 */

 /*Define report function*/
typedef void(*Operator_ReportFuncition)(char* _subSriber);

/*Define structure OperatorDs_t */
typedef struct OperatorDs_t OperatorDs_t;

/*Define Enum operatorDs_Result */
typedef enum operatorDs_Result
{
    OPERATOR_DS_SUCCESS,
    OPERATOR_DS_UNINITIALIZED_ERROR,
    OPERATOR_DS_ERRROR
}operatorDs_Result;

/*Define Enum OperatorDs_FiledToUpdate */
typedef enum OperatorDs_FiledToUpdate
{
	OPERATOR_INCOMING_CAll_FROM_OPERATOR,
	OPERATOR_OUTGOING_CALL_TO_OPERATOR,
	OPERATOR_INCOMING_SMS_FROM_OPERATOR,
	OPERATOR_OUTGOING_SMS_TO_OPERATOR
}OperatorDs_FiledToUpdate;

/*Define Enum SubScribeDs Report Type */
typedef enum OperatorDs_ReportType
{
    OperatorDs_ReportType_OneOperator,
    OperatorDs_ReportType_AllOperators /*print to out put file*/
}OperatorDs_ReportType;

/**
 * @brief The function create and init operatorDs.
* @param[in] size_t _numberOfOperators - number of Operator - size of data structer.
 * @return in success OperatorDs_t* in fail NULL.
 */
OperatorDs_t* OperatorDs_Creaty(size_t _numberOfOperators);

/**
 * @brief The function Destroy operatorDs.
 * @param[in] OperatorDs_t* _operatorDs - operator Data structer to Destroy.
 * @return operatorDs_Result.
 */
operatorDs_Result OperatorDs_Destroy(OperatorDs_t* _operatorDs);

/**
 * @brief The function set  Data To the Data Struct that the operatorDS charge on him.
 * @param[in] OperatorDs_t* _operatorDs - Operator Data Manager to Set in him.
 * @param[in] size_t _mmcMnc - Operator MMCMNC number.
 * @param[in] char* _OpBranName - Operator Brand Name.
 * @param[in] OperatorDs_FiledToUpdate _filedToUpdate - Defines which field to set.
 * @param[in] size_t _data- data to set.
 * @return operatorDs_Result.
 */
operatorDs_Result OperatorDs_Set(OperatorDs_t* _operatorDs,size_t _mmcMnc,char* _OpBrandName,OperatorDs_FiledToUpdate _filedToUpdate, size_t _data);

/**
 * @brief The function Create Report by user request and make action whit it whit function provided by the user.
 * @param[in] OperatorDs_t* _operatorDs- Operator Ds  to make report from.
 * @param[in] size_t m_mmcMnc - MMCMNC number of the Operator.
 * @param[in] OperatorDs_ReportType _type - Report Type
 * @param[in] Operator_ReportFuncition _action - user action function.
 * @return operatorDs_Result.
 */
operatorDs_Result OperatorDs_Report(OperatorDs_t* _operatorDs,size_t m_mmcMnc, OperatorDs_ReportType _type, Operator_ReportFuncition _action);

#endif  /* OPARETORDS_H_INCLUDED*/
