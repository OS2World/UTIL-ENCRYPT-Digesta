#include <stdio.h>
#include <string.h>


#define TEST1   "abc"
#define TEST2a  "abcdbcdecdefdefgefghfghighijhi"

#define TEST2b  "jkijkljklmklmnlmnomnopnopq"
#define TEST2   TEST2a TEST2b
#define TEST3   "a"
#define TEST4a  "01234567012345670123456701234567"
#define TEST4b  "01234567012345670123456701234567"
    /* an exact multiple of 512 bits */
#define TEST4   TEST4a TEST4b
char *testarray[4] =
{
    TEST1,
    TEST2,
    TEST3,
    TEST4
};


void main(void)
{
  int i;

  FILE *fp;

  fp = fopen("test1.dat","wb");
  fwrite("abc",1,3,fp);
  fclose(fp);
  fp = fopen("test2.dat","wb");
  fwrite(TEST2,1,strlen(TEST2),fp);
  fclose(fp);
  fp = fopen("test3.dat","wb");
  for(i = 0;i < 1000000; i++)
    fwrite(TEST3,1,1,fp);
  fclose(fp);
  fp = fopen("test4.dat","wb");
  for(i = 0;i < 10; i++)
    fwrite(TEST4,1,strlen(TEST4),fp);
  fclose(fp);


}
