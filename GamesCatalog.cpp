#include "gamescatalog.h"
#include "ui_gamescatalog.h"

GamesCatalog::GamesCatalog(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GamesCatalog)
{
    ui->setupUi(this);
    // TODO: Setup the game list and pagination
}

GamesCatalog::~GamesCatalog()
{
    delete ui;
}
