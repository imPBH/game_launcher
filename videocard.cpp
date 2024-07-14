#include "videocard.h"
#include "ui_videocard.h"
#include <QImageReader>

VideoCard::VideoCard(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::VideoCard)
    , manager(new QNetworkAccessManager(this))
{
    ui->setupUi(this);
    QImageReader::setAllocationLimit(0); // remove image size limit
    connect(manager, &QNetworkAccessManager::finished, this, &VideoCard::onImageDownloaded);
}

VideoCard::~VideoCard()
{
    delete ui;
}

void VideoCard::setVideo(YoutubeVideo *video)
{
    this->_thumbnail = video->getThumbnail();
    this->_title = "<a href='" + video->getUrl() + "'>" + video->getTitle() + "</a>";
    qDebug() << "html title" << this->_title;

    ui->title->setText(this->_title);
    ui->title->setOpenExternalLinks(true);

    QUrl thumbnailUrl(this->_thumbnail);
    QNetworkRequest request(thumbnailUrl);
    manager->get(request);
}

void VideoCard::onImageDownloaded(QNetworkReply *reply)
{
    if (reply->error() == QNetworkReply::NoError) {
        QByteArray imageData = reply->readAll();
        QPixmap pixmap;
        pixmap.loadFromData(imageData);
        ui->thumbnail->setPixmap(pixmap);
    } else {
        qDebug() << "Error downloading image:" << reply->errorString();
    }
    reply->deleteLater();
}
