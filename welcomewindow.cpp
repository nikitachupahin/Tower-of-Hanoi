#include "welcomewindow.h"
#include "ui_welcomewindow.h"
#include "stylehelper.h"

WelcomeWindow::WelcomeWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WelcomeWindow)
{
    ui->setupUi(this);
    setFixedSize(800, 600);
    setWindowTitle("Гра 'Ханойская вежа'");
    setInterfaceStyle();
    ui->stackedWidget->insertWidget(1, &gameWindow);
    ui->stackedWidget->insertWidget(2, &aboutWindow);
    connect(&gameWindow, SIGNAL(toMainPageClicked()), this, SLOT(moveToMainPage()));
    connect(&aboutWindow, SIGNAL(toMainPageClicked()), this, SLOT(moveToMainPage()));
}

WelcomeWindow::~WelcomeWindow()
{
    delete ui;
}

void WelcomeWindow::on_playButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}


void WelcomeWindow::on_aboutButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void WelcomeWindow::moveToMainPage()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void WelcomeWindow::setInterfaceStyle()
{
    this->setStyleSheet(StyleHelper::getWelcomeWindowStyle());
}

