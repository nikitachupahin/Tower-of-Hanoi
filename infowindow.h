#ifndef INFOWINDOW_H
#define INFOWINDOW_H

#include <QWidget>

namespace Ui {
class InfoWindow;
}

class InfoWindow : public QWidget
{
    Q_OBJECT

public:
    explicit InfoWindow(QWidget *parent = nullptr);
    ~InfoWindow();

private:
    Ui::InfoWindow *ui;
    void setStyle();

private slots:
    void on_homeButton_clicked();

signals:
    void toMainPageClicked();
};

#endif // INFOWINDOW_H
