#include "infowindow.h"
#include "ui_infowindow.h"
#include "stylehelper.h"

InfoWindow::InfoWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::InfoWindow)
{
    ui->setupUi(this);
    setStyle();
}

InfoWindow::~InfoWindow()
{
    delete ui;
}

void InfoWindow::setStyle()
{
    this->setStyleSheet(StyleHelper::getInfoWindowStyle());
}

void InfoWindow::on_homeButton_clicked()
{
    emit toMainPageClicked();
}

