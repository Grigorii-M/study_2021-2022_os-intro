---
## Front matter
lang: ru-RU
title: Лабораторная работа №10. Программирование в командном процессоре ОС UNIX. Командные файлы.
author: Matiukhin Grigorii


## Formatting
toc: false
slide_level: 2
theme: metropolis
header-includes: 
 - \metroset{progressbar=frametitle,sectionpage=progressbar,numbering=fraction}
 - '\makeatletter'
 - '\beamer@ignorenonframefalse'
 - '\makeatother'
aspectratio: 43
section-titles: true
---

# Цель работы:

Приобретение практических навыков работы с именованными каналами.

# Выполнение лабораторной работы

Изучите приведённые в тексте программы server.c и client.c. Взяв данные примеры за образец, напишите аналогичные программы, внеся следующие изменения:

##  Работает не 1 клиент, а несколько (например, два).

```c
/*
 * server.c - реализация сервера
 *
 * чтобы запустить пример, необходимо:
 * 1. запустить программу server на одной консоли;
 * 2. запустить программу client на другой консоли.
 */

#include "common.h"

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

  for (int i = 0; i < 2; i++)
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
```

## Клиенты передают текущее время с некоторой периодичностью (например, раз в пять секунд). Используйте функцию sleep() для приостановки работы клиента.

```c
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
```

## Сервер работает не бесконечно, а прекращает работу через некоторое время (например, 30 сек). Используйте функцию clock() для определения времени работы сервера.

```c
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
```

# Вывод

В ходе работы я приобрел практические навыки работы с именованными каналами.
