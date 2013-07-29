/** DSHA1.C Copyright (c) 2005 Axel Meiss                                   **/
/** may be distributed freely as long as copyright notice is preserved     **/
/** It is provided "as is" without express or implied warranty of any kind **/



#include "sha1.h"

SHA1Context sha1ctx;


int DIGESTINIT(void)
{
  SHA1Reset(&sha1ctx);
  return 0;
}

int DIGESTUPDATE(unsigned char *buffer, unsigned long ulSize)
{
  SHA1Input(&sha1ctx,
            (const uint8_t *) buffer,
            ulSize);
  return 0;
}

int DIGESTRESULT(unsigned char *output)
{
  int len;
  unsigned char digest[20];
  unsigned char *buffer = output;
  unsigned int iValue;
  char digits[16] =
  {
    '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'
  };


  SHA1Result(&sha1ctx,
             digest);


  for(len = 0;len < sizeof(digest);len++)
  {
    *buffer++ = digits[digest[len] >> 4];
    *buffer++ = digits[digest[len] & 0xf];
  }
  *buffer = '\0';

  return 0;
}
