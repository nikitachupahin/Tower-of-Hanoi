#include "stylehelper.h"

QString StyleHelper::getWelcomeWindowStyle()
{
    return "QWidget{"
           "font-family: 'Ink Free';"
           "color: rgb(170, 219, 252);"
           "}"
           "QStackedWidget, QMessageBox, QDialog{"
           "background-color: rgb(2, 28, 62);"
           "}"
           "QMessageBox{"
           "font-size: 18px;"
           "}"
           "QPushButton{"
           "border:none;"
           "border-radius: 10px;"
           "font-size: 20px;"
           "background-color: rgb(0, 0, 127);"
           "}"
           "QPushButton#playButton, QPushButton#aboutButton{"
           "min-height: 50px;"
           "border:none;"
           "border-radius: 25px;"
           "font-size: 22px;"
           "}"
           "QPushButton::hover {"
           "color:rgb(255,255,255);"
           "background-color: rgb(80, 80, 230);"
           "}"
           "QPushButton::pressed {"
           "background-color: rgb(23, 23, 110);"
           "}"
           "QLabel#namrLabel_1, QLabel#namrLabel_2{"
           "font-size: 70px;"
           "}"
           "QGroupBox{"
           "border: 1px solid transparent;"
           "}";
}

QString StyleHelper::getGameWindowStyle()
{
    return "QPushButton#pushButtonTower1, QPushButton#pushButtonTower2, QPushButton#pushButtonTower3 {"
           "background-color: transparent;"
           "}";
           "QPushButton#pushButtonTower1:pressed, QPushButton#pushButtonTower2:pressed, QPushButton#pushButtonTower3:pressed {"
           "border-style: inset;"
           "}";
}

QString StyleHelper::getInfoWindowStyle()
{
    return  "QLabel#labelHeader{"
            "font-size: 40px;"
            "}"
            "QLabel#labelText{"
            "font-size: 22px;"
            "}";
}
