#ifndef TOWEROFHANOI_H
#define TOWEROFHANOI_H

#include "tower.h"
#include "disk.h"
#include "move.h"
#include <QStack>
#include <QMainWindow>
#include <QMessageBox>
#include <QTimer>
#include <QQueue>
#include <QScrollArea>

QT_BEGIN_NAMESPACE
namespace Ui { class TowerOfHanoi; }
QT_END_NAMESPACE

class TowerOfHanoi : public QMainWindow
{
    Q_OBJECT

public:
    TowerOfHanoi(QWidget *parent = nullptr);
    ~TowerOfHanoi();

signals:
    void toMainPageClicked();

private slots:

    void on_pushButtonTower1_clicked();

    void on_pushButtonTower2_clicked();

    void on_pushButtonTower3_clicked();

    void delayedAction(); // слот, який викликається затримкою для виконання наступного ходу в грі

    void on_buttonSolve_clicked();

    void on_buttonRestart_clicked();

    void on_decreaseButton_clicked();

    void on_increaseButton_clicked();

    void on_homeButton_clicked();

    void on_HelpButton_clicked();

private:
    Ui::TowerOfHanoi *ui;
    Tower* towers[3]; // масив веж
    QQueue<Move> schedule; // черга ходів
    QTimer* timer;
    bool autoplay; // флаг автогри
    int amountDiscs; // кількість дисків
    int moveCount; // лічильник ходів
    void on_pushButton_clicked(Tower* p);
    void CalculateAutoplay(int count, int from,  int dest, int aux); // метод для автоматичного вирішення гри
    void paintEvent(QPaintEvent*);
    void checkWinCondition(); // метод для перевірки виграшу в грі
    void updateMoveCount(); // метод для оновлення лічильник ходів
    void setInterfaceStyle();
};

class SolutionDialog : public QDialog {
public:
    SolutionDialog(QWidget *parent = nullptr);

    void setSolutionSteps(const QString &steps); // метод, який відображає список кроків розв'язку

private:
    QLabel *labelSteps; // мітка для відображення кроків
};

#endif // TOWEROFHANOI_H
