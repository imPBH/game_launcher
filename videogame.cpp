#include "videogame.h"

VideoGame::VideoGame() {}

void VideoGame::setName(QString name) {
    this->_name = name;
}

void VideoGame::setBackgroundImage(QString background_image) {
    this->_background_image = background_image;
}

void VideoGame::setRating(double rating) {
    this->_rating = rating;
}

QString VideoGame::getName() {
    return this->_name;
}

QString VideoGame::getBackgroundImage() {
    return this->_background_image;
}

double VideoGame::getRating() {
    return this->_rating;
}

QString VideoGame::getReleaseDate() {
    return this->_release_date;
}

void VideoGame::setReleaseDate(QString release_date) {
    this->_release_date = release_date;
}
