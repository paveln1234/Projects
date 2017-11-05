#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "operator.h"

#define MAGICNUMBER 0xDEADFFFF
#define RESET 0
#define OPNAME  64

/*Define struct Operator Data  */
struct OperatorData_t
{
	size_t m_magicNumber;
	size_t m_mmcMnc;
	char m_opBrandName[OPNAME];
	size_t m_outgoingCallsToOp;
	size_t m_incomingCallsFromOp;
	size_t m_outgoingSMSToOp;
	size_t m_incomingSMSFromOp;
};

/**********************************************************/
OperatorData_t* OperatorData_Creaty(size_t _mmcMnc,  char* _opName)
{
    OperatorData_t* newOp;

    if( NULL == _opName)
    {
        return NULL;
    }

    newOp = calloc(1,sizeof(OperatorData_t));
    if(NULL == newOp)
    {
        return NULL;
    }

    newOp->m_mmcMnc = _mmcMnc;
    strcpy(newOp->m_opBrandName,_opName);
    newOp->m_magicNumber = MAGICNUMBER;

return newOp;
}
/**********************************************************/
OperatorData_Result OperatorData_Destroy(OperatorData_t* _opData)
{
    if(NULL == _opData || MAGICNUMBER != _opData->m_magicNumber)
    {
        return OPERATOR_DATA_UNINITIALIZED_ERROR;
    }
    _opData->m_magicNumber = 0;
    free(_opData);

return OPERATOR_DATA_SUCCESS;
}

/**********************************************************/
OperatorData_Result OperatorData_AddInCallFromOperator(OperatorData_t* _opData, size_t _sec)
{
    if(NULL == _opData || MAGICNUMBER != _opData->m_magicNumber)
    {
        return OPERATOR_DATA_UNINITIALIZED_ERROR;
    }
    _opData->m_incomingCallsFromOp += _sec;

return OPERATOR_DATA_SUCCESS;
}

/**********************************************************/
OperatorData_Result OperatorData_GetInCallFromOperator(OperatorData_t* _opData, size_t* _retVal)
{
    if(NULL == _opData || MAGICNUMBER != _opData->m_magicNumber || NULL == _retVal)
    {
        return OPERATOR_DATA_UNINITIALIZED_ERROR;
    }
    *_retVal = _opData->m_incomingCallsFromOp;

return OPERATOR_DATA_SUCCESS;
}

/**********************************************************/
OperatorData_Result OperatorData_AddOutCallToOperator(OperatorData_t* _opData, size_t _sec)
{
    if(NULL == _opData || MAGICNUMBER != _opData->m_magicNumber)
    {
        return OPERATOR_DATA_UNINITIALIZED_ERROR;
    }
    _opData->m_outgoingCallsToOp += _sec;

return OPERATOR_DATA_SUCCESS;
}

/**********************************************************/
 OperatorData_Result OperatorData_GetOutCallToOperator(OperatorData_t* _opData, size_t* _retVal)
 {
    if(NULL == _opData || MAGICNUMBER != _opData->m_magicNumber || NULL == _retVal)
    {
        return OPERATOR_DATA_UNINITIALIZED_ERROR;
    }
    *_retVal = _opData->m_outgoingCallsToOp;

return OPERATOR_DATA_SUCCESS;
 }

 /**********************************************************/
OperatorData_Result OperatorData_AddInSmsFromOperator(OperatorData_t* _opData)
{
    if(NULL == _opData || MAGICNUMBER != _opData->m_magicNumber)
    {
        return OPERATOR_DATA_UNINITIALIZED_ERROR;
    }
    _opData->m_incomingSMSFromOp++;

return OPERATOR_DATA_SUCCESS;
}

/**********************************************************/
OperatorData_Result OperatorData_GetInSmsFromOperator(OperatorData_t* _opData, size_t* _retVal)
{
    if(NULL == _opData || MAGICNUMBER != _opData->m_magicNumber || NULL == _retVal)
    {
        return OPERATOR_DATA_UNINITIALIZED_ERROR;
    }
    *_retVal = _opData->m_incomingSMSFromOp;

return OPERATOR_DATA_SUCCESS;
}

/**********************************************************/
OperatorData_Result OperatorData_AddOutSmsToOperator(OperatorData_t* _opData)
{
    if(NULL == _opData || MAGICNUMBER != _opData->m_magicNumber)
    {
        return OPERATOR_DATA_UNINITIALIZED_ERROR;
    }
    _opData->m_outgoingSMSToOp++;

return OPERATOR_DATA_SUCCESS;
}

/**********************************************************/
OperatorData_Result OperatorData_GetOutSmsToOperator(OperatorData_t* _opData, size_t* _retVal)
{
    if(NULL == _opData || MAGICNUMBER != _opData->m_magicNumber || NULL == _retVal)
    {
        return OPERATOR_DATA_UNINITIALIZED_ERROR;
    }
    *_retVal = _opData->m_outgoingSMSToOp;

return OPERATOR_DATA_SUCCESS;
}

/**********************************************************/
OperatorData_Result OperatorData_OperatorToStr(OperatorData_t* _opData, char*  _buffer)
{
    if(NULL == _opData || MAGICNUMBER != _opData->m_magicNumber || NULL == _buffer)
    {
        return OPERATOR_DATA_UNINITIALIZED_ERROR;
    }
	sprintf(_buffer, "Operator Code: %ld ,Total SMS From: %ld , Total SMS To: %ld ,Total Voice From: %ld , Total Voice To: %ld \n",_opData->m_mmcMnc,_opData->m_incomingSMSFromOp,_opData->m_outgoingSMSToOp,_opData->m_incomingCallsFromOp,_opData->m_outgoingCallsToOp);

return OPERATOR_DATA_SUCCESS;
}

/**********************************************************/
 OperatorData_Result OperatorData_OperatorReset(OperatorData_t* _opData)
 {
         if(NULL == _opData || MAGICNUMBER != _opData->m_magicNumber)
    {
        return OPERATOR_DATA_UNINITIALIZED_ERROR;
    }
    _opData->m_incomingCallsFromOp = RESET;
    _opData->m_incomingSMSFromOp = RESET;
    _opData->m_outgoingCallsToOp = RESET;
    _opData->m_outgoingSMSToOp = RESET;

return OPERATOR_DATA_SUCCESS;
 }
