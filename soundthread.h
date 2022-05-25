#ifndef SOUNDTHREAD_H
#define SOUNDTHREAD_H

#include <QThread>
#include <QSoundEffect>
#include "setting.h"

class soundThread : public QThread
{
    Q_OBJECT
public:
    enum soundType{pickup = 0,boom = 1};

    soundThread(soundType _type = pickup);
    ~soundThread();


    soundType type;
    void setType(soundType _type) { type = _type; }
    QSoundEffect *sound;

protected:
    virtual void run();

public slots:
    void playPickupSound();
    void playBoomSound();

signals:
    void pickupSound();
    void boomSound();
};

extern QSoundEffect* pickSoundptr, *boomSoundptr;

#endif // SOUNDTHREAD_H
