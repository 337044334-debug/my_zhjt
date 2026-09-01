#include "pe15thread.h"
#include <stdint.h>
#include <string.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <QDebug>

Pe15thread::Pe15thread(): paused(false)
{

}

void Pe15thread::pause()
{
    QMutexLocker locker(&mutex);
    paused = true;
}

void Pe15thread::resume()
{
    QMutexLocker locker(&mutex);

    paused = false;

    condition.wakeOne();
}

void Pe15thread::run()
{
    system("touch pe15.txt");
    qDebug()<<"PE15 success start";
    int fd;
    char buf[32];
    int lastValue = 0;
    while (1) { 
        mutex.lock();  
        while (paused)
        {
            condition.wait(&mutex);
        } 
        system("gpioget gpiochip4 15 > pe15.txt");
        fd = open("./pe15.txt",O_RDONLY);
        if(fd < 0)
               {
                   qDebug() << "open failed";
                   sleep(1);
                   continue;
               }

               memset(buf, 0, sizeof(buf));

               int len = read(fd, buf, sizeof(buf) - 1);

               if(len > 0)
               {
                   buf[len] = '\0';

                   int currentValue = atoi(buf);

                   //qDebug() << "PE15 =" << currentValue;

                   if(currentValue == 1 && lastValue == 0)
                   {
                       qDebug() << "login !!";
                       emit pesig();
                   }

                   lastValue = currentValue;
               }

               close(fd);

               sleep(1);
    }
}
