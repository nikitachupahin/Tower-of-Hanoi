#include "tower.h"
#include "disk.h"
#include <QPainter>


Disk::Disk(int size, Tower* tower,int pos, QWidget* par) :
    size(size),
    on(tower),
    pos(pos)
{
    this->setParent(par);
    show();
}

// Метод, що повертає покажчик на башню, на якій знаходиться диск
Tower *Disk::On(){
    return on;
}

void Disk::Lift(){
    pos=12;
    repaint();
}

// Метод встановлення позиції диска на певну башню d і позицію p.
void Disk::setTowerPos(Tower*d, int p){

    if(On() != d){
        on = d;
        setParent(d->parentWidget());
        show();
    }
    pos = p;
    repaint();
}

int Disk::Size(){
    return size;
}

void Disk::paintEvent(QPaintEvent *){

    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);
    QColor edgeDiskColor(0, 0, 0);
    p.setPen(edgeDiskColor);

    int width = (size*3)+60;

    QColor colors[] = {QColor(0,0,255),QColor(255,0,0),QColor(255,255,0),  QColor(0,255,255), QColor(160,32,240), QColor(52, 76, 18), QColor(190,96,74), QColor(0,255,0) };
    QColor diskTop = colors[size-1];
    QColor diskShadow = diskTop.darker(200);
    p.setBrush(diskShadow);
    p.drawEllipse(QPointF(130,(100 + 260 - 5)-DISK_HEIGHT*(pos+1)),width,25);

    p.setBrush(diskTop);
    p.drawEllipse(QPointF(130,(100 + 250 - 5)-DISK_HEIGHT*(pos+1)),width,25);

    QColor baseColor(100,100,100);
    p.setBrush(edgeDiskColor);
    p.drawEllipse(QPointF(130,(100 + 250 - 5)-DISK_HEIGHT*(pos+1)),width/4,8);
}
