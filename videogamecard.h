#ifndef VIDEOGAMECARD_H
#define VIDEOGAMECARD_H

#include <QWidget>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include "videogame.h"

namespace Ui {
class VideoGameCard;
}

class VideoGameCard : public QWidget
{
    Q_OBJECT

public:
    explicit VideoGameCard(QWidget *parent = nullptr);
    ~VideoGameCard();

    void setGame(VideoGame *game);

signals:
    void cardClicked(VideoGame *game);

protected:
    void mousePressEvent(QMouseEvent *event) override;

private slots:
    void onImageDownloaded(QNetworkReply *reply);

private:
    Ui::VideoGameCard *ui;
    QNetworkAccessManager *manager;
    QString _name;
    double _rating;
    QString _background_image;
    VideoGame *_game;
};

#endif // VIDEOGAMECARD_H
