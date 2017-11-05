#include <stdio.h>/*sprintf*/
#include <stdlib.h>/*size_t*/
#include <string.h>/*string*/
#include <unistd.h>/*for sleep*/
#define DEFULTOUTPUTCDRFOLDER "../../input/"
#define DEFULTINTERVAL 1
#define MYOPERATOR "Pavel Communication Ltd"
#define MYMMC "42422"
#define OPARAOT_LENGHT 64
#define IMIEDEFULT "7253167"
#define CALLDATE "16/12/2002"
#define CALLTIME "05:28:42"
#define MAX 2000000
#define MIN 1000000
#define NUMOFLINES 8000000
#define NUMOFFILES 8
#define MAKEIMSI(num)  num =(rand() % (MAX + 1 -MIN)) + MIN
#define DEFULTCDRFORMAT "txt"
/*cdr header
 imsi [15]|MSISDN[15]|IMIE[15]| OPARATORNAME[64]| MCC/MNC |CALLTYPE|CALLDATE|CALLTIME|DURATION|UPLOAD|Party	MSISDN	|Party	Operator-
 */
typedef struct CDR
{
    char m_imsi[16];
    char m_msisdn[16];
    char m_imei[16];
    char m_operatorName[64];
    char m_mccmnc[10];
    char m_callType[6];
    char m_callDate[12];
    char m_callTime[10];
    char m_duration[6];
    char m_download[5];
    char m_upload[5];
    char m_comMsisdn[16];
    char m_comPartyMccmnc[10];
}CDR;

/***************internal set function to cdr************************/
void CdrCreator_SetImsi(char* _buffer);
void CdrCreator_SetMsisdn(char* _buffer);
void CdrCreator_defualtInit(CDR* _cdr);
void CdrCreator_SetCallParty(CDR* _cdr);
void CdrCreator_CallTypeANDDerivatives(CDR* _cdr);
void CdrCreator_SetSmsParty(CDR* _cdr);
void CdrCreator_SetGPRS(CDR*_cdr);
void CdrCreator_SetOperator(CDR* _cdr);
void CdrCreator_CdrToLine(CDR* _cdr,char* _line);
void CdrCreator_run(char* _path,size_t _intervalInSec);

int main()
{
    char path[] = DEFULTOUTPUTCDRFOLDER;
    size_t intervalInSec = DEFULTINTERVAL;
    printf("Start Cdr Creat\n");
    CdrCreator_run(path,intervalInSec);
    printf("Done Cdr Creat\n");
    return 0;
}

/***************************/
void CdrCreator_run(char* _path,size_t _intervalInSec)
{
    CDR* cdr;
    char line[512];
    char fileName[50];
    int numberOfFiles = NUMOFFILES;
    int i = 0;
    int j = 0;
    int numberOfLinesInFIle = NUMOFLINES;
    FILE* fp;
    cdr = calloc(1,sizeof(CDR));
    for(i =0 ; i <numberOfFiles ; ++i)
    {
        sprintf(fileName,"%s/%d.%s",_path,i,DEFULTCDRFORMAT);
        fp = fopen(fileName,"w");
        for(j=0; j < numberOfLinesInFIle; ++j)
        {
            CdrCreator_defualtInit(cdr);
            CdrCreator_SetImsi(cdr->m_imsi);
            CdrCreator_SetMsisdn(cdr->m_msisdn);
            CdrCreator_CallTypeANDDerivatives(cdr);

            CdrCreator_CdrToLine(cdr,line);
            fprintf(fp,"%s",line);
        }
        fclose(fp);
    sleep(_intervalInSec);
    }
    free(cdr);

}

/***************************/
void CdrCreator_defualtInit(CDR* _cdr)
{
    strcpy(_cdr->m_imei ,IMIEDEFULT);
    strcpy(_cdr->m_callDate,CALLDATE);
    strcpy(_cdr->m_callTime,CALLTIME);
    strcpy(_cdr->m_operatorName,MYOPERATOR);
    strcpy(_cdr->m_mccmnc,MYMMC);

return;
}
/***************************/
void CdrCreator_SetImsi(char* _buffer)
{
    int imsi;

    MAKEIMSI(imsi);
    sprintf(_buffer,"%d",imsi);
 return;
}

void CdrCreator_SetMsisdn(char* _buffer)
{
    int msisdn;

    MAKEIMSI(msisdn);
    sprintf(_buffer,"%d",msisdn);
 return;
}
/***************************/
void CdrCreator_CallTypeANDDerivatives(CDR* _cdr)
{
    int num;
    num = rand()%5;
    switch(num)
    {
        case 0:
                    strcpy(_cdr->m_callType,"MOC");
                    CdrCreator_SetCallParty(_cdr);
                    break;
        case 1:
                    strcpy(_cdr->m_callType,"MTC");
                    CdrCreator_SetCallParty(_cdr);
                    break;
        case 2:
                    strcpy(_cdr->m_callType,"SMS-MO");
                    CdrCreator_SetSmsParty(_cdr);
                    break;
        case 3:
                    strcpy(_cdr->m_callType,"SMS-MT");
                    CdrCreator_SetSmsParty(_cdr);
                    break;
        default:
                    strcpy(_cdr->m_callType,"GPRS");
                    CdrCreator_SetGPRS(_cdr);
    }
return;
}
/***************************/
void CdrCreator_SetCallParty(CDR* _cdr)
{
    sprintf(_cdr->m_duration,"%d",rand()%60+1);
    CdrCreator_SetImsi(_cdr->m_comMsisdn);
    CdrCreator_SetOperator(_cdr);
    strcpy(_cdr->m_download," ");
    strcpy(_cdr->m_upload," ");

return;
}
/***************************/
void CdrCreator_SetSmsParty(CDR* _cdr)
{
    CdrCreator_SetOperator(_cdr);
    CdrCreator_SetImsi(_cdr->m_comMsisdn);
    strcpy(_cdr->m_duration," ");
    strcpy(_cdr->m_download," ");
    strcpy(_cdr->m_upload," ");

return;
}

void CdrCreator_SetGPRS(CDR*_cdr)
{
    float num = 10;

    sprintf(_cdr->m_upload,"%2.2f",((float)rand()/(float)(RAND_MAX)) * num);
    sprintf(_cdr->m_download,"%2.2f",((float)rand()/(float)(RAND_MAX)) * num);
    strcpy(_cdr->m_comPartyMccmnc,MYMMC);

return;
}

/***************************/
void CdrCreator_SetOperator(CDR* _cdr)
{
    int num;
    num = rand()%5;
    switch(num)
    {
        case 0:
                    strcpy(_cdr->m_comPartyMccmnc,"41205");
                    break;
        case 1:
                    strcpy(_cdr->m_comPartyMccmnc,"41206");
                    break;
        case 2:
                    strcpy(_cdr->m_comPartyMccmnc,"41207");
                    break;
        case 3:
                    strcpy(_cdr->m_comPartyMccmnc,"41208");
                    break;
        default:
                    strcpy(_cdr->m_comPartyMccmnc,MYMMC);
    }

return;
}

/***************************/
void CdrCreator_CdrToLine(CDR* _cdr,char* _line)
{
    sprintf(_line,"%s|%s|%s|%s|%s|%s| 16/12/2002 |%s|%s|%s|%s|%s |%s\n",_cdr->m_imsi,_cdr->m_msisdn,_cdr->m_imei,_cdr->m_operatorName,_cdr->m_mccmnc,_cdr->m_callType,_cdr->m_callTime,_cdr->m_duration,_cdr->m_download,_cdr->m_upload,_cdr->m_comMsisdn,_cdr->m_comPartyMccmnc);

return;
}
