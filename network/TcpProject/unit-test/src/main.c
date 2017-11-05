/*
 ============================================================================
 Name        : ClientSide.c
 Author      : Pavel Kolrolin
 Version     : 1
 Copyright   : MIT
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "Client_ui.h"
int main(void) {
	Client_Ui* ui = Ui_Create("config.ini");
	Ui_Run(ui);
	return EXIT_SUCCESS;
}
