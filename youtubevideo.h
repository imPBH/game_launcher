#ifndef YOUTUBEVIDEO_H
#define YOUTUBEVIDEO_H

#include <QObject>

class YoutubeVideo
{
public:
    YoutubeVideo();
    void setTitle(QString title);
    void setThumbnail(QString thumbnail);
    void setVideoId(QString video_id);
    QString getTitle();
    QString getThumbnail();
    QString getUrl();

private:
    QString _title;
    QString _thumbnail;
    QString _video_id;
};

#endif // YOUTUBEVIDEO_H
