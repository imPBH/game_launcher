#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>
#include <QtNetwork>
#include "videogamecard.h"

namespace Ui {
class GameWindow;
}

class GameWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit GameWindow(QWidget *parent = nullptr);
    void getGames();
    void clearGameCards();
    ~GameWindow();

private slots:
    void on_nextButton_clicked();
    void on_previousButton_clicked();
    void onGameCardClicked(VideoGame *game);

private:
    Ui::GameWindow *ui;
    int page = 1;
    QString gamesApiUrl = "https://api.rawg.io/api/games?key=614d93ae3ef040aba8cc293da4554819&page_size=6&page=";
    void addGameCardToGrid(VideoGameCard *gameCard, int row, int col);
};

#endif // GAMEWINDOW_H
