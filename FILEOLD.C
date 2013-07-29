/** FILEOLD.C - Copyright (c) 2005 Axel Meiss                              **/
/** file access routines for handling "normal" files (2 GB)                **/
/** may be distributed freely as long as copyright notice is preserved     **/
/** It is provided "as is" without express or implied warranty of any kind **/

#define OS2
#define INCL_DOSFILEMGR
#include <os2.h>


/** error variable **/
static ULONG FErrorCode = 0;


void LSetLastFileError(unsigned long ErrorCode)
{
  FErrorCode = ErrorCode;
}

unsigned long LGetLastFileError(void)
{
  return FErrorCode;
}



unsigned long LFileOpen(char *pszFileName)
{
  APIRET rc;
  HFILE hFileHandle = (HFILE) 0;
  ULONG ulAction;
  ULONG ulFileAttribute = FILE_NORMAL;
  ULONG ulOpenFlags =    OPEN_ACTION_FAIL_IF_NEW
                       | OPEN_ACTION_OPEN_IF_EXISTS;

  ULONG ulOpenMode  =    OPEN_FLAGS_SEQUENTIAL
                       | OPEN_SHARE_DENYWRITE
                       | OPEN_ACCESS_READONLY
                       /**| 0x10000000;     OPEN_SHARE_DENYLEGACY **/
                       ;

  rc = DosOpen(pszFileName,
                &hFileHandle,
                &ulAction,
                0UL,
                ulFileAttribute,
                ulOpenFlags,
                ulOpenMode,
                (PEAOP2)NULL);

  if(rc != 0)
    LSetLastFileError(rc);

  return (unsigned long) hFileHandle;
}

unsigned long LFileRead(void *pBuffer,
                        unsigned long ulToRead,
                        unsigned long hFileHandle)
{
  APIRET rc;
  ULONG  ulNumberRead;

  rc = DosRead((HFILE) hFileHandle,
                       pBuffer,
                       ulToRead,
                       &ulNumberRead);
  if(rc != 0)
    LSetLastFileError(rc);

  return ulNumberRead;

}


void LFileClose(unsigned long hFileHandle)
{
  APIRET rc;

  rc = DosClose((HFILE) hFileHandle);

  return;
}
