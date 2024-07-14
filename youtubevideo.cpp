#include "youtubevideo.h"

YoutubeVideo::YoutubeVideo() {}

void YoutubeVideo::setVideoId(QString video_id)
{
    this->_video_id = video_id;
}

void YoutubeVideo::setTitle(QString title)
{
    this->_title = title;
}

void YoutubeVideo::setThumbnail(QString thumbnail)
{
    this->_thumbnail = thumbnail;
}

QString YoutubeVideo::getThumbnail()
{
    return this->_thumbnail;
}

QString YoutubeVideo::getTitle()
{
    return this->_title;
}

QString YoutubeVideo::getUrl()
{
    return "https://www.youtube.com/watch?v=" + this->_video_id;
}
