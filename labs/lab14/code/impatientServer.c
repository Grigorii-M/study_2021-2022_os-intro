/*
 * server.c - реализация сервера
 *
 * чтобы запустить пример, необходимо:
 * 1. запустить программу server на одной консоли;
 * 2. запустить программу client на другой консоли.
 */

#include "common.h"
#include <time.h>

int main()
{
  int readfd; /* дескриптор для чтения из FIFO */
  int n;
  char buff[MAX_BUFF]; /* буфер для чтения данных из FIFO */

  /* баннер */
  printf("FIFO Server...\n");

  /* создаем файл FIFO с открытыми для всех
   * правами доступа на чтение и запись
   */
  if(mknod(FIFO_NAME, S_IFIFO | 0666, 0) < 0)
  {
    fprintf(stderr, "%s: Невозможно создать FIFO (%s)\n",
    __FILE__, strerror(errno));
    exit(-1);
  }
  
  clock_t start_t, end_t;
  double total_t;
  start_t = clock();
  while(1)
  {
    /* откроем FIFO на чтение */
    if((readfd = open(FIFO_NAME, O_RDONLY)) < 0)
    {
      fprintf(stderr, "%s: Невозможно открыть FIFO (%s)\n",
      __FILE__, strerror(errno));
      exit(-2);
    }
  
    /* читаем данные из FIFO и выводим на экран */
    while((n = read(readfd, buff, MAX_BUFF)) > 0)
    {
      if(write(1, buff, n) != n)
      {
        fprintf(stderr, "%s: Ошибка вывода (%s)\n",
        __FILE__, strerror(errno));
        exit(-3);
      }
    }
    
    end_t = clock();
    total_t = (double) (end_t - start_t) / CLOCKS_PER_SEC;
    printf("%f\n", total_t);
    if (total_t >= 0.01)
    {
      break;
    }
  }
 
  close(readfd); /* закроем FIFO */
 
  /* удалим FIFO из системы */
  if(unlink(FIFO_NAME) < 0)
  {
    fprintf(stderr, "%s: Невозможно удалить FIFO (%s)\n",
    __FILE__, strerror(errno));
    exit(-4);
  }

  exit(0);
}
