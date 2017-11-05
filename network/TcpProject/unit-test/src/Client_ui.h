/*
 * client_ui.h
 *
 *  Created on: Jul 13, 2017
 *      Author: pavel
 */

#ifndef CLIENT_UI_H_
#define CLIENT_UI_H_

typedef struct Client_Ui Client_Ui;

Client_Ui* Ui_Create(const char* _configFileName);

void Ui_Run(Client_Ui* _ui);

void Ui_Destroy(Client_Ui);

#endif /* CLIENT_UI_H_ */
