/*
 * client.c - реализация клиента
 *
 * чтобы запустить пример, необходимо:
 * 1. запустить программу server на одной консоли;
 * 2. запустить программу client на другой консоли.
 */

#include "common.h"
#include <time.h>

#define MESSAGE "Hello Server!!!\n"

int main()
{
  int writefd; /* дескриптор для записи в FIFO */
  int msglen;

  /* баннер */
  printf("FIFO Client...\n");

  /* получим доступ к FIFO */
  if((writefd = open(FIFO_NAME, O_WRONLY)) < 0)
  {
    fprintf(stderr, "%s: Невозможно открыть FIFO (%s)\n",
    __FILE__, strerror(errno));
    exit(-1);
  }
  
  for (int i = 0; i < 3; i++)
  {
    time_t mytime = time(NULL);
    char * time_str = ctime(&mytime);
    time_str[strlen(time_str)-1] = '\0';
    strcat(time_str, "\n");
    /* передадим сообщение серверу */
    msglen = strlen(time_str);
    if(write(writefd, time_str, msglen) != msglen)
    {
      fprintf(stderr, "%s: Ошибка записи в FIFO (%s)\n",
      __FILE__, strerror(errno));
      exit(-2);
    }
    sleep(5);
  }

  /* закроем доступ к FIFO */
  close(writefd);
 
  exit(0);
}
