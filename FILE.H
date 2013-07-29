/** AM 18-Feb-2004 17:12:31 prototypes for custom file functions **/


unsigned long LGetLastFileError(void);
unsigned long LFileOpen(char *pszFileName);
unsigned long LFileRead(void *pBuffer,
			unsigned long ulToRead,
			unsigned long hFileHandle);
void LFileClose(unsigned long hFileHandle);
