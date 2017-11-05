#include <stdio.h>
#include <stdlib.h>
#include "subscriber.h"

#define MAGICNUMBER 0xDEADFFFF
#define RESET 0
/*Define sttruct subScribe Data  */
struct SubScribeData_t
{
	size_t m_magicNumber;
	size_t m_msisdn;
	size_t m_outgoingCallsWithinOp;
	size_t m_incomingCallsWithinOp;
	size_t m_outgoingCallsOutsideOp;
	size_t m_incomingCallsOutsideOp;
	size_t m_outgoingSMSWithinOp;
	size_t m_incomingSMSWithinOp;
	size_t m_outgoingSMSOutsideOp;
	size_t m_incomingSMSOutsideOp;
	float m_downloaded;
	float m_uploaded;
};

/**********************************************************/
SubScribeData_t* SubScribe_Creaty(size_t _msisdn)
{
	SubScribeData_t* newSubsriber;

	newSubsriber = calloc(1,sizeof(SubScribeData_t));
	if(NULL == newSubsriber)
	{
		return NULL;
	}
	newSubsriber->m_msisdn = _msisdn;
	newSubsriber->m_magicNumber = MAGICNUMBER;

return newSubsriber;
}

/**********************************************************/
SubScribeData_Result SubScribe_Destroy(SubScribeData_t* _sub)
{
	if(NULL == _sub || MAGICNUMBER != _sub->m_magicNumber)
	{
		return SUBSCRIBE_DATA_UNINITIALIZED_ERROR;
	}
	_sub->m_magicNumber = 0;
	free(_sub);

return SUBSCRIBE_DATA_SUCCESS;
}

/**********************************************************/
SubScribeData_Result SubScribe_AddOutCallWightOperator(SubScribeData_t* _sub,size_t _sec)
{
	if(NULL == _sub || MAGICNUMBER != _sub->m_magicNumber)
	{
		return SUBSCRIBE_DATA_UNINITIALIZED_ERROR;
	}
	_sub->m_outgoingCallsWithinOp += _sec;

return SUBSCRIBE_DATA_SUCCESS;
}
/**********************************************************/
SubScribeData_Result SubScribe_GetOutCallWightOperator(SubScribeData_t* _sub,size_t* _retVul)
{
	if(NULL == _sub || MAGICNUMBER != _sub->m_magicNumber || NULL == _retVul)
	{
		return SUBSCRIBE_DATA_UNINITIALIZED_ERROR;
	}
	*_retVul = _sub->m_outgoingCallsWithinOp;

return SUBSCRIBE_DATA_SUCCESS;
}

/**********************************************************/
SubScribeData_Result SubScribe_AddInCallWightOperator(SubScribeData_t* _sub,size_t _sec)
{
	if(NULL == _sub || MAGICNUMBER != _sub->m_magicNumber)
	{
		return SUBSCRIBE_DATA_UNINITIALIZED_ERROR;
	}
	_sub->m_incomingCallsWithinOp += _sec;

return SUBSCRIBE_DATA_SUCCESS;
}

/**********************************************************/
SubScribeData_Result SubScribe_GetInCallWightOperator(SubScribeData_t* _sub,size_t* _retVul)
{
	if(NULL == _sub || MAGICNUMBER != _sub->m_magicNumber || NULL == _retVul)
	{
		return SUBSCRIBE_DATA_UNINITIALIZED_ERROR;
	}
	*_retVul = _sub->m_incomingCallsWithinOp;

return SUBSCRIBE_DATA_SUCCESS;
}

/**********************************************************/
SubScribeData_Result SubScribe_AddOutCallOutsideOperator(SubScribeData_t* _sub,size_t _sec)
{
	if(NULL == _sub || MAGICNUMBER != _sub->m_magicNumber)
	{
		return SUBSCRIBE_DATA_UNINITIALIZED_ERROR;
	}
	_sub->m_outgoingCallsOutsideOp += _sec;

return SUBSCRIBE_DATA_SUCCESS;
}

/**********************************************************/
 SubScribeData_Result SubScribe_GetOutCallOutsideOperator(SubScribeData_t* _sub,size_t* _retVul)
 {
 	if(NULL == _sub || MAGICNUMBER != _sub->m_magicNumber || NULL == _retVul)
	{
		return SUBSCRIBE_DATA_UNINITIALIZED_ERROR;
	}
	*_retVul = _sub->m_outgoingCallsOutsideOp;

return SUBSCRIBE_DATA_SUCCESS;
 }

 /**********************************************************/
SubScribeData_Result SubScribe_AddInCallOutsideOperator(SubScribeData_t* _sub,size_t _sec)
{
	if(NULL == _sub || MAGICNUMBER != _sub->m_magicNumber)
	{
		return SUBSCRIBE_DATA_UNINITIALIZED_ERROR;
	}
	_sub->m_incomingCallsOutsideOp += _sec;

return SUBSCRIBE_DATA_SUCCESS;
}

 /**********************************************************/
 SubScribeData_Result SubScribe_GetInCallOutsideOperator(SubScribeData_t* _sub,size_t* _retVul)
 {
 	if(NULL == _sub || MAGICNUMBER != _sub->m_magicNumber || NULL == _retVul)
	{
		return SUBSCRIBE_DATA_UNINITIALIZED_ERROR;
	}
	*_retVul = _sub->m_incomingCallsOutsideOp;

return SUBSCRIBE_DATA_SUCCESS;
 }

 /**********************************************************/
SubScribeData_Result SubScribe_AddOutSmsWightOperator(SubScribeData_t* _sub)
{
	if(NULL == _sub || MAGICNUMBER != _sub->m_magicNumber)
	{
		return SUBSCRIBE_DATA_UNINITIALIZED_ERROR;
	}
	_sub->m_outgoingSMSWithinOp++;

return SUBSCRIBE_DATA_SUCCESS;
}


 /**********************************************************/
SubScribeData_Result SubScribe_GetOutSmsWightOperator(SubScribeData_t* _sub,size_t* _retVul)
{
	if(NULL == _sub || MAGICNUMBER != _sub->m_magicNumber || NULL == _retVul)
	{
		return SUBSCRIBE_DATA_UNINITIALIZED_ERROR;
	}
	*_retVul = _sub->m_outgoingSMSWithinOp;

return SUBSCRIBE_DATA_SUCCESS;
}

 /**********************************************************/
SubScribeData_Result SubScribe_AddInSmsWightOperator(SubScribeData_t* _sub)
{
	if(NULL == _sub || MAGICNUMBER != _sub->m_magicNumber)
	{
		return SUBSCRIBE_DATA_UNINITIALIZED_ERROR;
	}
	_sub->m_incomingSMSWithinOp++;

return SUBSCRIBE_DATA_SUCCESS;
}

/**********************************************************/
SubScribeData_Result SubScribe_GetInSmsWightOperator(SubScribeData_t* _sub,size_t* _retVul)
{
	if(NULL == _sub || MAGICNUMBER != _sub->m_magicNumber || NULL == _retVul)
	{
		return SUBSCRIBE_DATA_UNINITIALIZED_ERROR;
	}
	*_retVul = _sub->m_incomingSMSWithinOp;

return SUBSCRIBE_DATA_SUCCESS;
}

/**********************************************************/
SubScribeData_Result SubScribe_AddOutSmsOutsideOperator(SubScribeData_t* _sub)
{
	if(NULL == _sub || MAGICNUMBER != _sub->m_magicNumber)
	{
		return SUBSCRIBE_DATA_UNINITIALIZED_ERROR;
	}
	_sub->m_outgoingSMSOutsideOp ++;

return SUBSCRIBE_DATA_SUCCESS;
}

/**********************************************************/
SubScribeData_Result SubScribe_GetOutSmsOutsideOperator(SubScribeData_t* _sub,size_t* _retVul)
{
	if(NULL == _sub || MAGICNUMBER != _sub->m_magicNumber || NULL == _retVul)
	{
		return SUBSCRIBE_DATA_UNINITIALIZED_ERROR;
	}
	*_retVul = _sub->m_outgoingSMSOutsideOp;

return SUBSCRIBE_DATA_SUCCESS;
}

/**********************************************************/
SubScribeData_Result SubScribe_AddInSmsOutsideOperator(SubScribeData_t* _sub)
{
	if(NULL == _sub || MAGICNUMBER != _sub->m_magicNumber)
	{
		return SUBSCRIBE_DATA_UNINITIALIZED_ERROR;
	}
	_sub->m_incomingSMSOutsideOp ++;

return SUBSCRIBE_DATA_SUCCESS;
}

/**********************************************************/
SubScribeData_Result SubScribe_GetInSmsOutsideOperator(SubScribeData_t* _sub,size_t* _retVul)
{
	if(NULL == _sub || MAGICNUMBER != _sub->m_magicNumber || NULL == _retVul)
	{
		return SUBSCRIBE_DATA_UNINITIALIZED_ERROR;
	}
	*_retVul = _sub->m_incomingSMSOutsideOp;

return SUBSCRIBE_DATA_SUCCESS;
}

/**********************************************************/
SubScribeData_Result SubScribe_AddDownload(SubScribeData_t* _sub,float _mb)
{
	if(NULL == _sub || MAGICNUMBER != _sub->m_magicNumber)
	{
		return SUBSCRIBE_DATA_UNINITIALIZED_ERROR;
	}
	_sub->m_downloaded+= _mb;

return SUBSCRIBE_DATA_SUCCESS;
}

/**********************************************************/
SubScribeData_Result SubScribe_GetDownload(SubScribeData_t* _sub,float* _retVul)
{
	if(NULL == _sub || MAGICNUMBER != _sub->m_magicNumber || NULL == _retVul)
	{
		return SUBSCRIBE_DATA_UNINITIALIZED_ERROR;
	}
	*_retVul = _sub->m_downloaded;

return SUBSCRIBE_DATA_SUCCESS;
}

/**********************************************************/
SubScribeData_Result SubScribe_AddUpload(SubScribeData_t* _sub,float _mb)
{
	if(NULL == _sub || MAGICNUMBER != _sub->m_magicNumber)
	{
		return SUBSCRIBE_DATA_UNINITIALIZED_ERROR;
	}
	_sub->m_uploaded += _mb;

return SUBSCRIBE_DATA_SUCCESS;
}
/**********************************************************/
SubScribeData_Result SubScribe_GetUpload(SubScribeData_t* _sub,float* _retVul)
{
	if(NULL == _sub || MAGICNUMBER != _sub->m_magicNumber || NULL == _retVul)
	{
		return SUBSCRIBE_DATA_UNINITIALIZED_ERROR;
	}
	*_retVul = _sub->m_uploaded;

return SUBSCRIBE_DATA_SUCCESS;
}

/**********************************************************/
SubScribeData_Result SubScribe_SubSribeToSrc(SubScribeData_t* _sub,char* _buffer)
{
	if(NULL == _sub || MAGICNUMBER != _sub->m_magicNumber)
	{
		return SUBSCRIBE_DATA_UNINITIALIZED_ERROR;
	}

	sprintf(_buffer, "MSISDN: %ld ,Outgoing calls within operator: %ld , Incoming calls within operator: %ld , Outgoing calls outside operator: %ld , Incoming calls outside operator: %ld, Outgoing SMS within operator: %ld , Incoming SMS within operator: %ld , Outgoing SMS outside operator: %ld , Incoming SMS outside operator: %ld , MB downloaded: %2.2f ,MB uploaded: %2.2f \n", _sub->m_msisdn,_sub->m_outgoingCallsWithinOp, _sub->m_incomingCallsWithinOp, _sub->m_outgoingCallsOutsideOp, _sub->m_incomingCallsOutsideOp, _sub->m_outgoingSMSWithinOp, _sub->m_incomingSMSWithinOp, _sub->m_outgoingSMSOutsideOp, _sub->m_incomingSMSOutsideOp, _sub->m_downloaded,_sub->m_uploaded);

return SUBSCRIBE_DATA_SUCCESS;
}

/**********************************************************/
SubScribeData_Result SubScribe_SubSribeReset(SubScribeData_t* _sub)
{
	if(NULL == _sub || MAGICNUMBER != _sub->m_magicNumber)
	{
		return SUBSCRIBE_DATA_UNINITIALIZED_ERROR;
	}

	_sub->m_msisdn = RESET;
	_sub->m_outgoingCallsWithinOp = RESET;
	_sub->m_incomingCallsWithinOp = RESET;
	_sub->m_outgoingCallsOutsideOp = RESET;
	_sub->m_incomingCallsOutsideOp = RESET;
	_sub->m_outgoingSMSWithinOp = RESET;
	_sub->m_incomingSMSWithinOp = RESET;
	_sub->m_outgoingSMSOutsideOp = RESET;
	_sub->m_incomingSMSOutsideOp = RESET;
	_sub->m_downloaded = RESET;
	_sub->m_uploaded= RESET;

return SUBSCRIBE_DATA_SUCCESS;
}
