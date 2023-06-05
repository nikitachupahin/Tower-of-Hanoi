#ifndef WELCOMEWINDOW_H
#define WELCOMEWINDOW_H

#include <QWidget>
#include "infowindow.h"
#include "towerofhanoi.h"

namespace Ui {
class WelcomeWindow;
}

class WelcomeWindow : public QWidget
{
    Q_OBJECT

public:
    explicit WelcomeWindow(QWidget *parent = nullptr);
    ~WelcomeWindow();

private slots:
    void on_playButton_clicked();
    void on_aboutButton_clicked();
    void moveToMainPage();

private:
    Ui::WelcomeWindow *ui;
    InfoWindow aboutWindow;
    TowerOfHanoi gameWindow;
    void setInterfaceStyle();
};

#endif // WELCOMEWINDOW_H
