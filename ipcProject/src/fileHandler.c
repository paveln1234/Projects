#include <stdio.h>/*calloc*/
#include <stdlib.h>/*size_t*/
#include <string.h>
#include <errno.h>
#include "fileHandler.h"
#define BUFFER 512
#define FILENAME_LENGHT 256


void  FileHandler_Read(char* _folder, char* _fileName, FileHandlerReadActionFunction _action,void* _context)
{
    FILE* file;
    char c;
    char filename[FILENAME_LENGHT];
    char line[BUFFER];
    int errnum = 0;
    strcpy(filename,_folder);
	strcat(filename,_fileName);
    file= fopen(filename,"r+");

    while(!feof(file) && !ferror(file))
    {
        if(NULL ==  fgets(line,BUFFER,file))
        {
            errnum = errno;
            fprintf(stderr, "Value of errno: %d\n", errno);
            perror("Error printed by perror");
            fprintf(stderr, "Error opening file: %s\n", strerror( errnum ));
        }
        _action(line,_context);
        c = fgetc(file);
    }
return;
}

void  FileHandler_Write(char* _folder,char* _fileName,char* _str)
{
    FILE* fileprint;
    char filename[FILENAME_LENGHT];

    strcpy(filename,_folder);
	strcat(filename,_fileName);

    fileprint= fopen(filename,"a");

    fprintf(fileprint,"%s",_str);
	fclose(fileprint);

return;
}



FileHandler_Result FileHandler_MoveFile(char* _fileName,char* _FolderFrom,char* _FolderTo)
{
	char fromFolder[256];
	char toFolder[256];

	strcpy(fromFolder,_FolderFrom);
	strcat(fromFolder,_fileName);
	strcpy(toFolder,_FolderTo);
	strcat(toFolder,_fileName);

    if(rename(fromFolder,toFolder))
    {
            perror("ERROR in move file from input to in progress folder ");
            return FILE_HANDLER_BAD_FILE_ERRROR;
    }

return FILE_HANDLER_SUCCESS;
}
