/** DMD5.C Copyright (c) 2005 Axel Meiss                                   **/
/** may be distributed freely as long as copyright notice is preserved     **/
/** derived from the RSA Data Security, Inc. MD5 Message-Digest Algorithm  **/
/** It is provided "as is" without express or implied warranty of any kind **/


#define PROTOTYPES

#include "global.h"
#include "md5.h"

MD5_CTX md5ctx;


int DIGESTINIT(void)
{
  MD5Init (&md5ctx);
  return 0;
}

int DIGESTUPDATE(unsigned char *buffer, unsigned long ulSize)
{
  MD5Update (&md5ctx, buffer, ulSize);
  return 0;
}

int DIGESTRESULT(unsigned char *output)
{
  int len;
  unsigned char digest[16];
  unsigned char *buffer = output;
  unsigned int iValue;
  char digits[16] =
  {
    '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'
  };

  MD5Final (digest, &md5ctx);

  for(len = 0;len < sizeof(digest);len++)
  {
    *buffer++ = digits[digest[len] >> 4];
    *buffer++ = digits[digest[len] & 0xf];
  }
  *buffer = '\0';

  return 0;
}
