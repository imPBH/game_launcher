#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gamewindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , loginAttempts(0)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_loginButton_clicked()
{
    QString username = ui->usernameEdit->text();
    QString password = ui->passwordEdit->text();

    if (username == "admin" && password == "password") {
        GameWindow *gameWindow = new GameWindow();
        gameWindow->show();
        this->close();
    } else {
        loginAttempts++;
        checkLoginAttempts();
        QMessageBox::warning(this, "Login Failed", "Incorrect username or password.");
    }
}

void MainWindow::checkLoginAttempts()
{
    if (loginAttempts >= 5) {
        QMessageBox::critical(this, "Maximum Attempts Reached", "You have reached the maximum number of login attempts.");
        QApplication::quit();
    }
}
