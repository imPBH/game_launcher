#include "videogamecard.h"
#include "ui_videogamecard.h"
#include <QPixmap>
#include <QImageReader>
#include <QMouseEvent>

VideoGameCard::VideoGameCard(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::VideoGameCard)
    , manager(new QNetworkAccessManager(this))
{
    ui->setupUi(this);
    QImageReader::setAllocationLimit(0); // remove image size limit
    connect(manager, &QNetworkAccessManager::finished, this, &VideoGameCard::onImageDownloaded);
}

VideoGameCard::~VideoGameCard()
{
    delete ui;
}

void VideoGameCard::setGame(VideoGame *game) {
    this->_game = game;
    this->_name = game->getName();
    this->_rating = game->getRating();
    this->_background_image = game->getBackgroundImage();

    ui->gameName->setText(this->_name);
    ui->gameRating->setText(QString::number(this->_rating));

    QUrl imageUrl(_background_image);
    QNetworkRequest request(imageUrl);
    manager->get(request);
}

void VideoGameCard::onImageDownloaded(QNetworkReply *reply)
{
    if (reply->error() == QNetworkReply::NoError) {
        QByteArray imageData = reply->readAll();
        QPixmap pixmap;
        pixmap.loadFromData(imageData);
        ui->gameBackground->setPixmap(pixmap);
    } else {
        qDebug() << "Error downloading image:" << reply->errorString();
    }
    reply->deleteLater();
}

void VideoGameCard::mousePressEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    emit cardClicked(_game);
}
