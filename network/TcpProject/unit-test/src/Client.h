/*
 * Client.h
 *
 *  Created on: Jul 13, 2017
 *      Author: pavel
 */

#ifndef CLIENT_H_
#define CLIENT_H_


#define MESSAGE_LENGTH 1024
#define USERNAME_LENGTH 32
#define PASSWORD_LENGTH 32
#define GROUP_NAME_LENGTH 32
typedef struct Client_t Client_t;

Client_t* Client_Create();


#endif /* CLIENT_H_ */
