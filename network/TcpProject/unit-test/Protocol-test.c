#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h> /* ADDRSELEN */

#include "Protocol-test.h"
#include "../inc/Protocol.h"
#include "../inc/Net.h"
void SendTo(void* _msg,size_t lenght);

int main()
{

    char buffer[1024]={0};
    int i = 0;
    ServerReceiveMessage_t* newmsg = calloc(1,sizeof(ServerReceiveMessage_t));
	ClientReceiveMessage_t* clientMessage = calloc(1, sizeof(ClientReceiveMessage_t));
	
    i  =  Protocol_EncodeSignUp("pavel","shusha",buffer);
        printf("\n 2 SINGUP   - the lenght of the message %d, the message are %s \n",i , buffer);
	/*	SendTo(buffer,i);*/
	
      Protocol_DecodeServer(buffer,i,newmsg);
      printf("\tRETURNMESAGE - %c -- %s -- %s\n",newmsg->m_MessageType ,newmsg->m_userName,newmsg->m_password);
	memset(buffer,0,1024);
        i = Protocol_EncodeDeleteUser(buffer);
            printf("\n 2 DELETE USER  - the lenght of the message %d, the message are %s\n ",i , buffer);

        Protocol_DecodeServer(buffer,i,newmsg);
        printf("\tRETURNMESAGE - %c -- %s -- %s\n",newmsg->m_MessageType ,newmsg->m_userName,newmsg->m_password);

	memset(buffer,0,1024);
    i = Protocol_EncodeNewGroup("THE A-TEAM RULES\n", buffer);
        printf("\n 3 NEWGROUP  - the lenght of the message %d, the message are %s\n ",i , buffer);
		
		Protocol_DecodeServer(buffer,i,newmsg);
        printf("\tRETURNMESAGE - %c -- %s -- %s\n",newmsg->m_MessageType ,newmsg->m_userName,newmsg->m_password);

	memset(buffer,0,1024);
    i = Protocol_EncodeGetAllGroups(buffer);
        printf("\n 4 GETALLGROUP - the lenght of the message %d, the message are %s\n ",i , buffer);

		Protocol_DecodeServer(buffer,i,newmsg);
        printf("\tRETURNMESAGE - %c -- %s -- %s\n",newmsg->m_MessageType ,newmsg->m_userName,newmsg->m_password);

	memset(buffer,0,1024);
    i = Protocol_EncodeJoinGroup("THE A-TEAM RULES\n",buffer);
        printf("\n 5 JOINGROUP - the lenght of the message %d, the message are %s\n ",i , buffer);

		Protocol_DecodeServer(buffer,i,newmsg);
        printf("\tRETURNMESAGE - %c -- %s -- %s\n",newmsg->m_MessageType ,newmsg->m_userName,newmsg->m_password);

	memset(buffer,0,1024);
    i = Protocol_EncodeLeaveGroup("THE A-TEAM RULES!!!!\n",buffer);
        printf("\n 6 LEAVEGROUP - the lenght of the message %d, the message are %s \n",i , buffer);

		Protocol_DecodeServer(buffer,i,newmsg);
        printf("\tRETURNMESAGE - %c -- %s -- %s\n",newmsg->m_MessageType ,newmsg->m_userName,newmsg->m_password);

	memset(buffer,0,1024);
    i = Protocol_EncodeLogIn("pavel","shusha",buffer);
        printf("\n 7 LOGIN -  the lenght of the message %d, the message are %s\n ",i , buffer);

		Protocol_DecodeServer(buffer,i,newmsg);
        printf("\tRETURNMESAGE - %c -- %s -- %s\n",newmsg->m_MessageType ,newmsg->m_userName,newmsg->m_password);

	memset(buffer,0,1024);
    i = Protocol_EncodeLogOut(buffer);
        printf("\n 8 LOGOUT - the lenght of the message %d, the message are %s \n",i , buffer);
	
		Protocol_DecodeServer(buffer,i,newmsg);
        printf("\tRETURNMESAGE - %c -- %s -- %s\n",newmsg->m_MessageType ,newmsg->m_userName,newmsg->m_password);
	
	memset(buffer,0,1024);
    	
    char ip[16] = "127.0.0.1";
	size_t port = 7254;
	char ipAddress[INET_ADDRSTRLEN];
	sockaddr_in_t servAddr;

	
	/*To Make struct*/
	servAddr.sin_family = AF_INET;
	servAddr.sin_port = htons(port);
	inet_pton(AF_INET, ip, &servAddr.sin_addr);
		
	i =  Protocol_EncodeNewGroup_Response(BackEnd_SUCCESS, servAddr, buffer);
        printf("\n 10 NewGroup - the lenght of the message %d, the message are %s \n",i , buffer);

        Protocol_DecodeClient(buffer,i,clientMessage);
        printf("\tRETURNMESAGE - %c --%c -- %s -- %s\n",clientMessage->m_messageType,clientMessage->m_status ,clientMessage->m_ip,clientMessage->port);
        

	free(clientMessage);
    free(newmsg);
return 1;
}


void SendTo(void* _msg,size_t lenght)
{
        char ip[16] = "127.0.0.1";
        size_t port = 7254;
            struct sockaddr_in client_sIn;
        Socket Nsocket= ConnectSocket(ip,port);
            memset(&client_sIn , 0 , sizeof(client_sIn) );
		    client_sIn.sin_family = AF_INET;
		    client_sIn.sin_addr.s_addr = inet_addr(ip);
	    client_sIn.sin_port = htons(port);

    if(0 > connect(Nsocket, (struct sockaddr *) &client_sIn, sizeof(client_sIn)) )
    {
        DisconnectSocket(Nsocket);

    }
	printf("connected");
        Send(Nsocket,_msg,lenght);

}


