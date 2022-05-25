#include "soundthread.h"

soundThread::soundThread(soundType _type)
{
    type = _type;
    connect(this, SIGNAL(pickupSound()), this, SLOT(playPickupSound()));
    connect(this, SIGNAL(boomSound()), this, SLOT(playBoomSound()));
}

void soundThread::run()
{
    qDebug() << "Play Sound";
    if(type == pickup)
    {
        qDebug() << "pick something";
        emit pickupSound();
    }
    if(type == boom)
    {
        qDebug() << "Boom";
        emit boomSound();
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

void soundThread::playBoomSound()
{
    qDebug() << "Boom: slot";
    sound = new QSoundEffect;
    sound->setSource(QUrl("qrc:/sound/res/sound/boom.wav"));
    sound->setVolume(100);
    sound->play();
}

soundThread::~soundThread()
{
    delete sound;
}
