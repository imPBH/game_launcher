#ifndef VIDEOSWINDOW_H
#define VIDEOSWINDOW_H

#include <QMainWindow>
#include <QtNetwork>
#include "videocard.h"

namespace Ui {
class VideosWindow;
}

class VideosWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit VideosWindow(const QString &gameName, QWidget *parent = nullptr);
    ~VideosWindow();
    void getVideos();

private:
    Ui::VideosWindow *ui;
    QString _gameName;
    void addVideoCardToGrid(VideoCard *videoCard, int row, int col);
    QString _youtubeSearchUrl = "https://www.googleapis.com/youtube/v3/search?key=AIzaSyAFFjvja7v2qVgcDZxdW-3ct86gVPsQ0e0&part=id,snippet&maxResults=4&order=relevance&type=video&q=video game ";
};

#endif // VIDEOSWINDOW_H
