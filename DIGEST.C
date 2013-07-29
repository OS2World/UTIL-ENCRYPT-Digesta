/** DIGEST.C Copyright (c) 2005,2006 Axel Meiss                                 **/
/** may be distributed freely as long as copyright notice is preserved          **/
/** It is provided "as is" without express or implied warranty of any kind      **/



#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define OS2
#define INCL_DOSMODULEMGR
#define INCL_DOSMISC    /* Miscellaneous values */



#include <os2.h>


#include "file.h"

int (*digestinit)(void);
int (*digestupdate)(unsigned char *buffer, unsigned long ulSize);
int (*digestresult)(unsigned char *buffer);
int MakeErrorMessage(unsigned long  errornumber,
                     unsigned char *errortext,
                     unsigned long textlen);


void main (int argc, char *argv[])
{
  long l_FileSize;
  int exit_code;
  int lower_case = 0;
  unsigned long ulFileHandle;
  unsigned long ulErrorCode;
  unsigned char filebuffer[4096];
  unsigned char dllname[16];
  unsigned char output[4096];

  APIRET rc;
  HMODULE hModule;



  char *pszFileName;

  if(argc < 3)
  {
    printf("Usage: %s [case] <method> <file> ", argv[0]);

    printf("%s ",output);
    exit(1);
  }
  memset(dllname,0,sizeof(dllname));
  dllname[0] = 'D';
  strncat(dllname + 1,argv[argc - 2],7);
  strcat(dllname,".DLL");
  strupr(dllname);

  pszFileName = argv[argc - 1];

  if(argc > 3)
  {
    strupr(argv[argc - 3]);
    if(strcmp("CASE",argv[argc - 3]) == 0)
      lower_case = !0;

  }

  rc = DosLoadModule(output,
                     sizeof(output),
                     dllname,
                     &hModule);

  if(rc != 0)
  {
    if(MakeErrorMessage(rc,output,sizeof(output)) != 0)
      fprintf(stderr,"%s Error: %ld\n",dllname, rc);
    else
      fprintf(stderr,"%s %s",dllname, output);
    exit(2);
  }

  rc = DosQueryProcAddr(hModule,
                        0UL,
                        "DIGESTINIT",
                        (PFN *) &digestinit);

  if(rc != 0)
  {
    if(MakeErrorMessage(rc,output,sizeof(output)) != 0)
      fprintf(stderr,"DLL Entry error number = %ld\n", rc);
    else
      fprintf(stderr,"%s %s",dllname, output);
    (void) DosFreeModule(hModule);
    exit(2);
  }

  rc = DosQueryProcAddr(hModule,
                        0UL,
                        "DIGESTUPDATE",
                        (PFN *) &digestupdate);

  if(rc != 0)
  {
    if(MakeErrorMessage(rc,output,sizeof(output)) != 0)
      fprintf(stderr,"DLL Entry error number = %ld\n", rc);
    else
      fprintf(stderr,"%s %s",dllname, output);
    (void) DosFreeModule(hModule);
    exit(2);
  }


  rc = DosQueryProcAddr(hModule,
                        0UL,
                        "DIGESTRESULT",
                        (PFN *) &digestresult);

  if(rc != 0)
  {
    if(MakeErrorMessage(rc,output,sizeof(output)) != 0)
      fprintf(stderr,"DLL Entry error number = %ld\n", rc);
    else
      fprintf(stderr,"%s %s",dllname, output);
    (void) DosFreeModule(hModule);
    exit(2);
  }

  exit_code = 0;
  memset(output,0,sizeof(output));

  if(strcmp(pszFileName,"-") == 0)
  {
    (*digestinit)();

    while((l_FileSize =
           LFileRead(filebuffer,sizeof(filebuffer),0))
           != 0)
    {
      (*digestupdate)(filebuffer,l_FileSize);
    }
    (*digestresult)(output);

    if(lower_case != 0)
      strlwr(output);
    printf("%s", output);
    printf(" %s\n",pszFileName);
  }
  else
  {
    if((ulFileHandle = LFileOpen(pszFileName)) != 0)
    {

      (*digestinit)();

      while((l_FileSize =
             LFileRead(filebuffer,sizeof(filebuffer),ulFileHandle))
             == sizeof(filebuffer))
      {
        (*digestupdate)(filebuffer,sizeof(filebuffer));
      }

      if((ulErrorCode = LGetLastFileError()) == 0)
      {
        (*digestupdate)(filebuffer,l_FileSize);
        (*digestresult)(output);

        if(lower_case != 0)
          strlwr(output);
        printf("%s", output);
        printf(" %s\n",pszFileName);

      }
      else
      {
        if(MakeErrorMessage(ulErrorCode,output,sizeof(output)) != 0)
          fprintf(stderr,"File error: %ld\n", ulErrorCode);
        else
          fprintf(stderr,"%s %s",pszFileName, output);
        exit_code = (int) ulErrorCode;
      }

      LFileClose(ulFileHandle);
    }
    else
    {
      ulErrorCode = LGetLastFileError();
      if(MakeErrorMessage(ulErrorCode,output,sizeof(output)) != 0)
        fprintf(stderr,"File error: %ld\n", ulErrorCode);
      else
        fprintf(stderr,"%s %s",pszFileName, output);
      exit_code = (int) ulErrorCode;

    }
  }
  DosFreeModule(hModule);

  exit(exit_code);
}

int MakeErrorMessage(unsigned long errornumber,
                     unsigned char *errortext,
                     unsigned long textlen)
{
  ULONG   ulMsgLen    = 0;                     /* Length of returned message */
  APIRET  rc          = 0;                     /* Return code */

  /* Create error message with inserts from system message file SAMPLE.MSG */
  
  rc = DosGetMessage(NULL,          /* Message insert pointer array */
                     0,                /* Number of inserts */
                     errortext,         /* Output message */
                     textlen, /* Length of output message area */
                     errornumber,            /* Number of message requested */
                     "OSO001.MSG",     /* Message file (created by MKMSGF) */
                     &ulMsgLen);       /* Length of resulting output message */
  if (rc != 0)
  {
     return 1;
  }

  return 0;

}
