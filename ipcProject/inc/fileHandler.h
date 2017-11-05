#ifndef _FILEHANDLER_H_
#define _FILEHANDLER_H_

/**
 *  @file fileHandler.h
 *  @brief The File Handler module allow to read wright and move file on linux base OS
 *
 *  @details  The File Handler module given set of tools to work whit files on linux base OS.

 *  @author Pavel Korolin (paveln1234@gmail.com)
 *
 *  @bug No known bugs.
 */

/*Define Enum FileHandler_Result */
typedef enum FileHandler_Result
{
    FILE_HANDLER_SUCCESS,
    FILE_HANDLER_FILE_NOTEXIC_ERRROR,
    FILE_HANDLER_BAD_FILE_ERRROR
}FileHandler_Result;

/*Define FileHandler Read Action Function */
typedef void(*FileHandlerReadActionFunction)(char* _line,void* _context);
/*Define FileHandler Wright Action Function */
typedef char*(*FileHandlerWrightActionFunction)(void* _context);

/**
 * @brief The function read File Line By Line and allow to user What to do Whit the data.
 * @param[in] char* _folder - folder the file into.
 * @param[in] char* _fileName - File name of the file to read from him.
 * @param[in] FileHandlerActionFunction _action - File Handler Read Action function.
 * @param[in] void* _context - context for the action function.
 * @return void * .
 */
void  FileHandler_Read(char* _folder, char* _fileName, FileHandlerReadActionFunction _action,void* _context);

/**
 * @brief The function Write To File user Data.
 * @param[in] char* _fileName - File name to wright to him.
 * @param[in] FileHandlerWrightActionFunction _action- File Handler Wright Action function.
 * @param[in] void* _context - context to action function.
 * @return FileHandler_Result.
 */
void  FileHandler_Write(char* _folder,char* _fileName,char* _str);


/**
 * @brief The function Move Files Between Folders.
 * @param[in] char* _fileName - File name to Move.
 * @param[in] char* _FolderFrom - Folder name of the folder that conten the file
 * @param[in] char* _FolderTo - Folder name to Move to her the file.
 * @return FileHandler_Result.
 */
FileHandler_Result FileHandler_MoveFile(char* _fileName,char* _FolderFrom,char* _FolderTo);


#endif /* _FILEHANDLER_H_*/
