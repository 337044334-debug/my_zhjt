#ifndef PE15THREAD_H
#define PE15THREAD_H

#include <QThread>
#include <QMutex>
#include <QWaitCondition>

class Pe15thread : public QThread
{
    Q_OBJECT
public:
    Pe15thread();
    void pause();//暂停
    void resume();//继续
    void stop();//停止


signals:
    void pesig();

private:
    QMutex mutex;  //互斥锁
    QWaitCondition condition; //等待条件
    bool paused;
    bool stopped;

protected:
    void run() override;
};

#endif // PE15THREAD_H
