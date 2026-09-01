#ifndef PE15THREAD_H
#define PE15THREAD_H

#include <QThread>

class Pe15thread : public QThread
{
    Q_OBJECT
public:
    Pe15thread();
    virtual void run();

signals:
    void pesig();
};

#endif // PE15THREAD_H
