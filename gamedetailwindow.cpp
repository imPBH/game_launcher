#include "gamedetailwindow.h"
#include "ui_gamedetailwindow.h"
#include "videoswindow.h"

GameDetailWindow::GameDetailWindow(VideoGame *game, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GameDetailWindow),
    _game(game)
{
    ui->setupUi(this);
    setWindowTitle(_game->getName() + " - Details");
    ui->gameName->setText(_game->getName());
    ui->gameRating->setText(QString::number(_game->getRating()));
    ui->gameReleaseDate->setText(_game->getReleaseDate());

    QUrl imageUrl(_game->getBackgroundImage());
    QNetworkRequest request(imageUrl);
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    connect(manager, &QNetworkAccessManager::finished, this, [this](QNetworkReply *reply) {
        if (reply->error() == QNetworkReply::NoError) {
            QByteArray imageData = reply->readAll();
            QPixmap pixmap;
            pixmap.loadFromData(imageData);
            ui->gameBackground->setPixmap(pixmap);
        } else {
            qDebug() << "Error downloading image:" << reply->errorString();
        }
        reply->deleteLater();
    });
    manager->get(request);
}

GameDetailWindow::~GameDetailWindow()
{
    delete ui;
}

void GameDetailWindow::on_videosButton_clicked()
{
    VideosWindow *videosWindow = new VideosWindow(_game->getName(), this);
    videosWindow->show();
}
