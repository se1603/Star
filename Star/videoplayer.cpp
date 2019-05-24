#include "videoplayer.h"

VideoPlayer::VideoPlayer()
{
    //初始化SDL
    if (SDL_Init(SDL_INIT_AUDIO)) {
        fprintf(stderr,"Could not initialize SDL - %s. \n", SDL_GetError());
        //        exit(1);
    }

    //初始化FFmpeg
    av_register_all();
    avformat_network_init();   //支持打开网络文件

    decoder = new VideoDecode(this);
    connect(decoder,&VideoDecode::getOneFrame,this,&VideoPlayer::oneFrame);

    mTimer = new QTimer;  //获取当前视频播放的时间
    connect(mTimer,&QTimer::timeout,this,&VideoPlayer::getCurrentTime);
}

VideoPlayer::~VideoPlayer()
{
    decoder->deleteLater();
}

int VideoPlayer::vheight() const
{
    return mHeight;
}

void VideoPlayer::setVheight(int value)
{
    mHeight = value;
}

void VideoPlayer::startPlay(QString path)
{

    decoder->startPlay(path);
    mTimer->start();
}

void VideoPlayer::pause()
{
    decoder->pause();
}

void VideoPlayer::play()
{
    decoder->play();
}

void VideoPlayer::stop()
{
    decoder->stop(true);
}

void VideoPlayer::sliderMoved(int position)
{
    decoder->seek((qint64)position * 1000000);
}

void VideoPlayer::getTotalTime(qint64 duration)
{
    mDuration = duration;
    emit sigShowTotalTime();
}

void VideoPlayer::paint(QPainter *painter)
{
    painter->setBrush(Qt::black);
    painter->drawRect(0,0,mWidth,mHeight);

    if(frame.size().width() <= 0) return;

    QImage img = frame.scaled(mWidth,mHeight,Qt::KeepAspectRatio);

    int x = mWidth - img.width();
    int y = mHeight - img.height();

    x /= 2;
    y /= 2;

    painter->drawImage(QPoint(x,y),img);
}

void VideoPlayer::oneFrame(QImage img)
{
    frame = img;
    update();
}

QString VideoPlayer::showTotalTime()
{
    qint64 sec = mDuration / 1000000; //微秒化成秒

    emit sigSliderTotalValue(sec);

    int hour = sec / 3600;
    int minutes = sec / 60 - hour * 60;
    int seconds = sec % 60;

    QString hStr = QString("00%1").arg(hour);
    QString mStr = QString("00%1").arg(minutes);
    QString sStr = QString("00%1").arg(seconds);

    QString str = QString("%1:%2:%3").arg(hStr.right(2)).arg(mStr.right(2)).arg(sStr.right(2));

    return str;
}

void VideoPlayer::getCurrentTime()
{
    qint64 sec = decoder->getCurrentTime();
    mCurrentTime = sec;

    emit sigSliderValue(sec);
    emit sigShowCurrentTime();
}

QString VideoPlayer::showCurrentTime()
{

    int hour = mCurrentTime / 3600;
    int minutes = mCurrentTime / 60 - hour * 60;
    int seconds = mCurrentTime % 60;

    QString hStr = QString("00%1").arg(hour);
    QString mStr = QString("00%1").arg(minutes);
    QString sStr = QString("00%1").arg(seconds);

    QString str = QString("%1:%2:%3").arg(hStr.right(2)).arg(mStr.right(2)).arg(sStr.right(2));

    return str;
}

int VideoPlayer::vwidth() const
{
    return mWidth;
}

void VideoPlayer::setVwidth(int value)
{
    mWidth = value;
}

