#include "videoswindow.h"
#include "ui_videoswindow.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QLabel>
#include <QNetworkRequest>
#include <QNetworkReply>
#include "youtubevideo.h"
#include "videocard.h"

VideosWindow::VideosWindow(const QString &gameName, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::VideosWindow),
    _gameName(gameName)
{
    ui->setupUi(this);
    setWindowTitle(_gameName + " - Related videos");
    this->getVideos();
}

VideosWindow::~VideosWindow()
{
    delete ui;
}

void VideosWindow::addVideoCardToGrid(VideoCard *videoCard, int row, int col)
{
    ui->gridLayout->addWidget(videoCard, row, col);
}

void VideosWindow::getVideos()
{
    qDebug() << "fetching videos";
    QEventLoop eventLoop;

    QNetworkAccessManager manager;
    connect(&manager, &QNetworkAccessManager::finished, &eventLoop, &QEventLoop::quit);

    QString apiUrl = _youtubeSearchUrl + _gameName;
    QUrl url(apiUrl);
    QNetworkRequest req(url);
    QNetworkReply *reply = manager.get(req);
    eventLoop.exec();

    if (reply->error() == QNetworkReply::NoError) {
        QString strReply = (QString)reply->readAll();
        qDebug() << "Success" <<strReply;

        QByteArray br = strReply.toUtf8();

        QJsonDocument doc = QJsonDocument::fromJson(br);

        QJsonObject obj = doc.object();
        QJsonArray results = obj["items"].toArray();

        int row = 0;
        int col = 0;

        foreach (const QJsonValue & value, results)
        {
            QJsonObject obj = value.toObject();
            QString videoId = obj["id"].toObject()["videoId"].toString();
            QJsonObject snippet = obj["snippet"].toObject();
            QString thumbnail = snippet["thumbnails"].toObject()["medium"].toObject()["url"].toString();
            QString videoTitle = snippet["title"].toString();

            qDebug() << "videoId" << videoId;
            qDebug() << "thumbnail" << thumbnail;
            qDebug() << "videoTitle" << videoTitle;

            YoutubeVideo *youtubeVideo = new YoutubeVideo();
            youtubeVideo->setVideoId(videoId);
            youtubeVideo->setThumbnail(thumbnail);
            youtubeVideo->setTitle(videoTitle);

            VideoCard *videoCard = new VideoCard(this);
            videoCard->setVideo(youtubeVideo);

            addVideoCardToGrid(videoCard, row, col);

            // Update row and column for next card
            col++;
            if (col >= 2) {  // We want 2 columns
                col = 0;
                row++;
            }
        }
        delete reply;
    } else {
        qDebug() << "Failure" << reply->errorString();
        delete reply;
    }
}
