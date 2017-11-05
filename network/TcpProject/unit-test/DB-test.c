#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "DB-test.h"
#include "Db.h"

void ClearItem(void* _item)
{
    free(item);

}
void ClearKey(void* _item)
{
    1==1;
}
void UserDbTest_Test()
{
    Db_t* usertest = NULL;
    int ret = 1;
    char* item = calloc(10,sizeof(char));
    char* itemret = malloc(10*sizeof(char));

    usertest = Db_Creare(101);
    (NULL !=usertest)?printf("make  database\n"):printf("fail to make  db\n");

    strcpy(item,"shusha");

    ret = Db_Add(usertest,"Pavel",(void*)item);
    (1 ==ret)?printf("add item  database\n"):printf("fail to add item to  db\n");

    ret = Db_Add(usertest,"Pavel",(void*)item);
    (1 ==ret)?printf("add item  database\n"):printf("fail to add item to  db\n");

    ret = Db_GetData(usertest,"Pavel",(void*)&itemret);
    (1 ==ret && !strcmp(item,itemret))?printf("Get item  database\n"):printf("fail to Get item from  db\n");

    ret = Db_GetData(usertest,"Paveddl",(void*)&itemret);
    (1 ==ret && !strcmp(item,itemret))?printf("Get item  database\n"):printf("fail to Get item from  db\n");

    ret = Db_Remove(usertest,"Pavel",(void*)&item);
    (1 ==ret && !strcmp(item,"shusha"))?printf("Remove item  database\n"):printf("fail to Remove item from  db\n");

    ret = Db_Remove(usertest,"Pavel",(void*)&item);
    (1 ==ret)?printf("Remove item  database\n"):printf("fail to Remove item from  db\n");

    strcpy(item,"shusha");
    ret = Db_Add(usertest,"Pavel",(void*)item);
    (1 ==ret)?printf("add item  database\n"):printf("fail to add item to  db\n");

    ret = Db_Add(usertest,"Pavel1",(void*)item);
    (1 ==ret)?printf("add item  database\n"):printf("fail to add item to  db\n");

    ret = Db_Add(usertest,"Pavel2",(void*)item);
    (1 ==ret)?printf("add item  database\n"):printf("fail to add item to  db\n");

    ret = Db_Add(usertest,"Pavel3",(void*)item);
    (1 ==ret)?printf("add item  database\n"):printf("fail to add item to  db\n");

    itemret = calloc(80, sizeof(char));
    printf("itemret size = %ld \n" , strlen(itemret));
    ret = Db_GetAllItems(usertest,itemret,"@@@");
    (1 ==ret)?printf("return val %s\n", itemret):printf("fail to Get all items from  db\n");

    ret = Db_Destroy(usertest,ClearKey,ClearItem);
    (1 ==ret)?printf("destroy  database\n"):printf("fail to destroy  db\n");

    usertest = Db_Creare(101);
    (NULL !=usertest)?printf("make  database\n"):printf("fail to make  db\n");


    ret = Db_Destroy(usertest,ClearKey,ClearItem);
    (1 ==ret)?printf("destroy  database\n"):printf("fail to destroy  db\n");
}
