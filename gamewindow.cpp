#include "gamewindow.h"
#include "ui_gamewindow.h"
#include "videogame.h"
#include "videogamecard.h"
#include "gamedetailwindow.h"

GameWindow::GameWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GameWindow)
{
    ui->setupUi(this);
    ui->previousButton->setDisabled(true);
    this->getGames();
}

GameWindow::~GameWindow()
{
    delete ui;
}

void GameWindow::addGameCardToGrid(VideoGameCard *gameCard, int row, int col)
{
    connect(gameCard, &VideoGameCard::cardClicked, this, &GameWindow::onGameCardClicked);
    ui->gridLayout->addWidget(gameCard, row, col);
}

void GameWindow::getGames() {
    QEventLoop eventLoop;

    QNetworkAccessManager manager;
    connect(&manager, &QNetworkAccessManager::finished, &eventLoop, &QEventLoop::quit);

    QNetworkRequest req(QUrl(QString(gamesApiUrl+QString::number(page))));
    QNetworkReply *reply = manager.get(req);
    eventLoop.exec();

    if (reply->error() == QNetworkReply::NoError) {
        QString strReply = (QString)reply->readAll();
        QByteArray br = strReply.toUtf8();
        QJsonDocument doc = QJsonDocument::fromJson(br);

        QJsonObject obj = doc.object();
        QJsonArray results = obj["results"].toArray();

        int row = 0;
        int col = 0;

        foreach (const QJsonValue & value, results)
        {
            QJsonObject obj = value.toObject();
            QString name = obj["name"].toString();
            QString background = obj["background_image"].toString();
            double rating = obj["rating"].toDouble();
            QString releaseDate = obj["released"].toString();

            VideoGame *game = new VideoGame();
            game->setName(name);
            game->setBackgroundImage(background);
            game->setRating(rating);
            game->setReleaseDate(releaseDate);

            qDebug() << "name" << name;
            qDebug() << "background_image" << background;
            qDebug() << "rating" << rating;

            VideoGameCard *gameCard = new VideoGameCard(this);
            gameCard->setGame(game);

            addGameCardToGrid(gameCard, row, col);

            // Update row and column for next card
            col++;
            if (col >= 3) {  // We want 3 columns
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

void GameWindow::on_nextButton_clicked() {
    if(page == 1) {
        ui->previousButton->setDisabled(false);
    }
    page++;
    clearGameCards();
    getGames();
}

void GameWindow::on_previousButton_clicked() {
    page--;
    if(page == 1) {
        ui->previousButton->setDisabled(true);
    }
    clearGameCards();
    getGames();
}

void GameWindow::clearGameCards() {
    QLayoutItem *child;
    while ((child = ui->gridLayout->takeAt(0)) != nullptr) {
        delete child->widget();
        delete child;
    }
}

void GameWindow::onGameCardClicked(VideoGame *game) {
    GameDetailWindow *detailWindow = new GameDetailWindow(game, this);
    detailWindow->show();
}
