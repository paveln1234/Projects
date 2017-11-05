#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

#include "systemManger.h"

int main()
{
SystemManger_t* manager;

manager = SystemManager_Load();
SystemManager_Run(manager);

printf("finisgh program");

return EXIT_SUCCESS;
}
