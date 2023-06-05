#ifndef TOWER_H
#define TOWER_H

#include <QWidget>

const int MAX_DISKS = 8;
const int MIN_DISKS = 1;

class Disk;

class Tower : public QWidget
{
private:
    bool autoplay;
    int index; // індекс вежі
    int amountDisks; // кількість дисків на вежі
    Disk* stack[MAX_DISKS]; // стек дисків на вежі

protected:
    void paintEvent(QPaintEvent *event) override;

public:
    Tower(int index, int amountDisks, QWidget *parent, bool autoplay);
    ~Tower();
    Disk* topDisk(); // метод, який повертає вказівник на верхній диск на вежі, інакше NULL
    bool putDisk(Disk* disk); // метод, який розміщує диск на вежі. Повертає true, якщо є місце і диск правильного розміру, інакше false
    int getAmountDisks(); // метод, який повертає кількість дисків, розташованих на вежі
};

#endif // TOWER_H
