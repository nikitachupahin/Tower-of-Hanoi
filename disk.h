#ifndef DISK_H
#define DISK_H

#include<QWidget>

const int DISK_HEIGHT = 23;

class Tower;

class Disk: public QWidget
{
private:
    int size; // розмір диска
    Tower* on; // вежа на якій знаходиться диск
    int Size();
    int pos; // позиція диска на вежі, де 0 - це ніжній диск

protected:
    void paintEvent(QPaintEvent *) override;

public:
    void setTowerPos(Tower*d, int p); // Метод встановлення позиції диска на певну башню d і позицію p.
    void Lift();
    Disk(int size, Tower* on, int pos, QWidget* par);
    Tower* On(); // Метод, що повертає покажчик на башню, на якій знаходиться диск
    friend class Tower; // має доступ до приватних членів класу Disk
};

#endif // DISK_H
