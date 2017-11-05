#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include "ui.h"
#define EMPTEY 100



void SelectFunctio(int _file,size_t _select);


int main()
{
    int clientToServerFifo;
   /* char myfifo[] = FIFO;*/
    size_t sel =1;
    size_t i = 0;
    int file;

    system("clear");
    printf("Program start \n ");
    printf("The program is initialized \n");
    file = open(FIFO,O_WRONLY);
    for(; i < 10 ;++i)
    {
        printf(".");
    }
    printf("\n");
        fflush(stdout);
    do
    {
        printf("\n Please select option \n");
        printf("\n Print One SubSriber Press------------------> 1  \n");
        printf("\n Print One Operator Press-------------------> 2  \n");
        printf("\n Print All SubSriber Press--------------------> 3  \n");
        printf("\n Print All Operator Press---------------------> 4  \n");
        printf("\n To Pause The System Press-----------------> 5  \n");
        printf("\n To Resume The System Press--------------> 6  \n");
        printf("\n To ShotDown The System Press-----------> 7  \n");
        printf("\n To Exit Press------------------------------------> 0  \n");
        scanf("%ld",&sel);
        system("clear");
        SelectFunctio(file,sel);
    }while(sel);

exit(EXIT_SUCCESS);
}

void SelectFunctio(int _file,size_t _select)
{
    size_t number;
    char str[10];
    switch(_select)
    {
        case 0:
                printf("Exiting The Program\n");
                break;
        case 1:
                sprintf(str,"%ld",_select);
                write(_file,str,strlen(str)+1);
                printf("Please insert MSISD of the Subscriber\n");
                scanf("%ld",&number);
                sprintf(str,"%ld",number);
                write(_file,str,strlen(str)+1);
                sleep(1); /*wait until get result*/
                system("clear");
                break;
        case 2:
                sprintf(str,"%ld",_select);
                write(_file,str,strlen(str)+1);
                printf("Please insert Operator MMCMNC of the Subscriber\n");
                scanf("%ld",&number);
                sprintf(str,"%ld",number);
                write(_file,str,strlen(str)+1);
                sleep(1); /*wait until get result*/
                system("clear");
                break;
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
                sprintf(str,"%ld",_select);
                write(_file,str,strlen(str)+1);
                break;
        default:
                    printf("Wrong Selection Please Select Again\n");
                    system("clear");
                    break;
    }

return;
}

