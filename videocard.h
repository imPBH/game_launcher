#ifndef VIDEOCARD_H
#define VIDEOCARD_H

#include <QWidget>
#include "youtubevideo.h"
#include <QtNetwork>

namespace Ui {
class VideoCard;
}

class VideoCard : public QWidget
{
    Q_OBJECT

public:
    explicit VideoCard(QWidget *parent = nullptr);
    ~VideoCard();
    void setVideo(YoutubeVideo *video);

private slots:
    void onImageDownloaded(QNetworkReply *reply);

private:
    Ui::VideoCard *ui;
    QNetworkAccessManager *manager;
    QString _title;
    QString _thumbnail;
};

#endif // VIDEOCARD_H
