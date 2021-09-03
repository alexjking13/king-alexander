#include <stdio.h>
#include <stdlib.h>
#define _CRT_SECURE_NO_WARNINGS


typedef unsigned int u32;

char *ctable = "0123456789ABCDEF";
int BASE = 10;

int rpu(u32 x);
int printu(u32 x);
void prints(char *s);
void printd(int x);
void printo(u32 x);
void printx(u32 x);
int myprintf(char *fmt, ...);


int main (int argc, char *argv[], char *env[])
{
  printf("printf output: argc = %d\n", argc);
  myprintf("myprintf output: argc = %d\n",argc);
  myprintf("char:%c string:%s dec:%d hex:%x oct:%o neg:%d\n", 'A',"this is a test",100, 100, 100, -100);
  return 0;
}
int rpu(u32 x)
{
  char c;
  if (x){
    c = ctable[x % BASE];
    rpu (x/BASE);
    putchar(c);
  }
}
int printu(u32 x)
{
  (x==0)? putchar('0') : rpu(x);
  putchar(' ');
}
void prints(char *s)
{
  while(*s!='\0')
    {
      putchar(*s);
      s++;
    }
}
void printd(int x)
{
  BASE = 10;
    if (x<0)
    {
      putchar('-');
      rpu(-1*x);
    }
    else
     {
	rpu(x);
     }
}
void printx(u32 x)
{
  BASE = 16;
  rpu(x);
}
void printo(u32 x)
{
  BASE =8;
  rpu(x);
}

int myprintf(char *fmt,...)
{
  char *cp = fmt;
  int *ip = (int *)&fmt;
  ip++;
  while(*cp!='\0')
    {
      if(*cp== '%')
	{
	  cp++;
	  switch(*cp)
	    {
	    case 'c':
	      putchar(*ip);
	      break;
	    case 's':
	      prints(*ip);
	      break;
	    case 'u':
	      printu(*ip);
	      break;
	    case 'd':
	      printd(*ip);
	      break;
	    case 'o':
	      printo(*ip);
	      break;
	    case 'x':
	      printx(*ip);
	      break;

	    }
	  ip++;
	}
      else if(*cp == '\n')
	{
	  putchar('\n');
	  putchar('\r');

	}
      else
	{
	  putchar(*cp);
	}

      cp++;
    }

}
