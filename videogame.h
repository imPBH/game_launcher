#ifndef VIDEOGAME_H
#define VIDEOGAME_H

#include <QObject>

class VideoGame
{
public:
    VideoGame();
    void setName(QString name);
    void setBackgroundImage(QString background_image);
    void setRating(double rating);
    void setReleaseDate(QString release_date);
    QString getName();
    QString getBackgroundImage();
    double getRating();
    QString getReleaseDate();

private:
    QString _name;
    QString _background_image;
    double _rating;
    QString _release_date;
};

#endif // VIDEOGAME_H
