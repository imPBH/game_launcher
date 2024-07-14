#ifndef GAMEDETAILWINDOW_H
#define GAMEDETAILWINDOW_H

#include <QMainWindow>
#include "videogame.h"
#include <QtNetwork>

namespace Ui {
class GameDetailWindow;
}

class GameDetailWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit GameDetailWindow(VideoGame *game, QWidget *parent = nullptr);
    ~GameDetailWindow();

private slots:
    void on_videosButton_clicked();

private:
    Ui::GameDetailWindow *ui;
    VideoGame *_game;
};

#endif // GAMEDETAILWINDOW_H
