#ifndef _SUBSCRIBEDS_H_
#define _SUBSCRIBEDS_H_


/**
 *  @file subscribeDs.h
 *  @brief Subscribe Data structer is manager data structe of sub sribe.
 *
 *  @details  operator Data structer module are charge to manage input data from data manager, like set, get and Update.

 *  @author Pavel Korolin (paveln1234@gmail.com)
 *
 *  @bug No known bugs.
 */

 /*Define report function*/
typedef void(*SubScribe_ReportFuncition)(char* _subSriber);

/*Define structure subScribeDs_t */
typedef struct SubScribeDs_t SubScribeDs_t;

/*Define Enum SubScribeDs_FiledToUpdate */
typedef enum SubScribeDs_FiledToUpdate
{
	OUT_CALL_WITHIN_OPERATOR = 0,
	IN_CALL_WITHIN_OPERATOR,
	OUT_CALL_OUTSIDE_OPERATOR,
	IN_CALL_OUTSIDE_OPERATOR,
	OUT_SMS_WITHIN_OPERATOR,
	IN_SMS_WITHIN_OPERATOR,
	OUT_SMS_OUTSIDE_OPERATOR,
	IN_SMS_OUTSIDE_OPERATOR,
	MB_DOWNLOADED,
	MB_UPLOADED
}SubScribeDs_FiledToUpdate;

/*Define union DataType_u */
typedef union DataType_u
{
    size_t sec;
    float data;
}DataType_u;

/*Define Enum SubScribeDs Result */
typedef enum SubScribeDs_Result
{
    SUBSCRIBE_DS_SUCCESS,
    SUBSCRIBE_DS_UNINITIALIZED_ERROR,
    SUBSCRIBE_DS_ERRROR
}SubScribeDs_Result;

/*Define Enum SubScribeDs Report Type */
typedef enum SubScribeDs_ReportType
{
    SubScribeDs_ReportType_OneSubScribe,
    SubScribeDs_ReportType_AllSubScribes/*print to out put file*/
}SubScribeDs_ReportType;

/**
 * @brief The function create and init subScribeDs_t.
 * @param[in] size_t _numberOfSubsribers - number of Subsribers - size of data structer.
 * @return in success SubScribeDs_t* in fail NULL.
 */
SubScribeDs_t* subScribeDs_Creaty( size_t _numberOfSubsribers);

/**
 * @brief The function destroy subScribeDs_t.
 * @param[in] SubScribeDs_t* _subScribeDs - SubScribe Data structer to Destroy.
 * @return SubScribeDs_Result.
 */
SubScribeDs_Result subScribeDs_Destroy(SubScribeDs_t* _subScribeDs);

/**
 * @brief The function set Data for  SubScriber - new subSriber will creaty if subScriber not found in the data structer
 * @param[in] SubScribeDs_t* _subScribeDs - SubScribe Ds  set in to him.
 * @param[in] size_t m_msisdn - msisdn of the subSriber to update
 * @param[in] SubScribeDs_FiledToUpdate _filed - filed to up date.
 * @param[in] DataType_u _data - data to up date .
 * @return SubScribeDs_Result.
 */
SubScribeDs_Result subScribeDs_Set(SubScribeDs_t* _subScribeDs, size_t m_msisdn,SubScribeDs_FiledToUpdate _filed,DataType_u* _data);

/**
 * @brief The function Create Report by user request and make action whit it whit function provided by the user.
 * @param[in] SubScribeDs_t* _subScribeDs - SubScribe Ds  to make report from.
 * @param[in] size_t _msisdn - Msisdn number of the user fro one subScribe report.
 * @param[in] SubScribeDs_ReportType _type - Report Type
 * @param[in] SubScribe_ReportFuncition _action - user action function.
 * @return SubScribeDs_Result.
 */
SubScribeDs_Result subScribeDs_Report(SubScribeDs_t* _subScribeDs,size_t _msisdn, SubScribeDs_ReportType _type, SubScribe_ReportFuncition _action);
#endif /* _SUBSCRIBEDS_H_*/
