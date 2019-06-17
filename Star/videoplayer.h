#ifndef VIDEOPLAYER_H
#define VIDEOPLAYER_H

#include <QQuickPaintedItem>
#include <QPainter>
#include <QPaintEvent>
#include <QTimer>
#include "videodecode.h"

class VideoPlayer : public QQuickPaintedItem
{
    Q_OBJECT
    Q_PROPERTY(int vwidth READ vwidth WRITE setVwidth NOTIFY vwidthChanged)
    Q_PROPERTY(int vheight READ vheight WRITE setVheight NOTIFY vheightChanged)
public:
    explicit VideoPlayer();
    ~VideoPlayer();

    int vwidth() const;
    void setVwidth(int value);

    int vheight() const;
    void setVheight(int value);

    Q_INVOKABLE void startPlay(QString path);
    Q_INVOKABLE void pause();
    Q_INVOKABLE void play();
    Q_INVOKABLE void stop(bool wait, int mwidth, int mheight);

    Q_INVOKABLE void sliderMoved(int position);

    void getTotalTime(qint64 duration);
    Q_INVOKABLE QString showTotalTime();   //视频时长

    void getCurrentTime();
    Q_INVOKABLE QString showCurrentTime();

    void snedNoResouce();

protected:
    void paint(QPainter *painter);

public slots:
    void oneFrame(QImage img);

signals:
    void vwidthChanged();
    void vheightChanged();
    void sigShowTotalTime();
    void sigShowCurrentTime();
    void sigSliderTotalValue(qint64 value);
    void sigSliderValue(qint64 currentvalue);
    void noResource();
    void updateFrame();

private:
    QImage frame;
    VideoDecode *decoder;
    int mWidth;
    int mHeight;
    qint64 mDuration;
    qint64 mCurrentTime;
    QTimer *mTimer;
    bool noResurce;
};

#endif // VIDEOPLAYER_H
