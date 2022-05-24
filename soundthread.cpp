#include "soundthread.h"

soundThread::soundThread(soundType _type)
{
    type = _type;
    connect(this, SIGNAL(pickupSound()), this, SLOT(playPickupSound()));
}

void soundThread::run()
{
    qDebug() << "Play Sound";
    if(type == pickup)
    {
        qDebug() << "pick something";
        emit pickupSound();
    }
}

void soundThread::playPickupSound()
{
    qDebug() << "pick something: slot";
    sound = new QSoundEffect;
    sound->setSource(QUrl("qrc:/sound/res/sound/pickupprop.wav"));
    sound->setVolume(100);
    sound->play();
}

soundThread::~soundThread()
{
    delete sound;
}
