#ifndef _REPORTER_H_
#define _REPORTER_H_


/**
 *  @file reporter.h
 *  @brief Thr Reporter is Output module for reports "cdr to cfg" system
 *
 *  @details  The Reporter module is charge to make report by UI module request.
 *            The Report OutPut for SubScribe Will be one line at next format separated by ",":
                IMSI
                Outgoing	voice	calls	duration	to	a	subscriber	within	the	mobile	operator
                Incoming	voice	calls	duration	to	a	subscriber	within	the	mobile	operator
                Outgoing	voice	calls	duration	to	a	subscriber	outside	the	mobile	operator
                Incoming	voice	calls	duration	to	a	subscriber	outside	the	mobile	operator
                SMS	messages	sent	within	the	mobile	operator
                SMS	messages	received	within	the	mobile	operator
                SMS	messages	sent	outside	the	mobile	operator
                SMS	messages	received	outside	the	mobile	operator
                MB	downloaded
                MB	uploaded

            The Report OutPut for Operator Will be one line at next format separated by ",":
                Operator MMC/MNC
                Operator brand name
                Incoming voice calls
                Outgoing voice calls
                Incoming SMS Messages
                Outgoing SMS Messages

            in out put to file for Operator's or SubScriber's will be add hader in the next format separated by ",":
                Report Created in:
                Date: YYYY/MM/DD
                Time: HH:MM:SS
 *
 *  @author Pavel Korolin (paveln1234@gmail.com)
 *
 *  @bug No known bugs.
 */

  /*Define Struct Reporter_t */
typedef struct Reporter_t Reporter_t;


 /*Define Enum Reporter_Result */
typedef enum Reporter_Result
{
    REPORTER_SUCCESS,
    REPORTER_ERROR
}Reporter_Result;

/*Define Enum ReportType */
typedef enum Reporter_Report_Type
{
    Reporter_Report_Type_OneSubScribe, /*print on screen*/
    Reporter_Report_Type_OneOperator, /*print on screen*/
    Reporter_Report_Type_AllSubScribes,/*print to out put file*/
    Reporter_Report_Type_AllOperators /*print to out put file*/
}Reporter_Report_Type;

/*Define Struct  ReportMessage */
typedef struct ReportMessage
{
    Reporter_Report_Type m_reportType;
    size_t m_data;
}ReportMessage;


/**
 * @brief The function create and init Reporter.
 * @param[in] STQueueu_t* _uiToReporterQueue - safe thread queue to receive messages from the Ui.
 * @param[in] DataManager_t* _dataManager - Data Manager to make report from.
 * @return in success Reporter_t* in fail NULL.
 */
Reporter_t*  Reporter_Creaty(STQueueu_t* _uiToReporterQueue,void* _dataManager);

/**
 * @brief The function destroy Reporter_t
 * @param[in] Reporter_t* _reporter - Reporter to destroy.
 * @return Reporter_Result.
 */
Reporter_Result  Reporter_Destroy(Reporter_t* _reporter);

/**
 * @brief The function run Reporter
 * @param[in] Reporter_t* _reporter - Reporter Manager to run.
 * @return Reporter_Result.
 */
Reporter_Result Reporter_Run(Reporter_t* _reporter);


#endif /* _REPORTER_H_*/
