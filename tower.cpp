#include "tower.h"
#include "disk.h"
#include <QWidget>
#include <QPainter>

Tower::Tower(int index, int amountDisks, QWidget *parent, bool autoplay):
    index(index),
    amountDisks(amountDisks),
    autoplay(autoplay)
{
    this->setParent(parent);

    for(int i=0;i < amountDisks;i++){
        Disk* disk = new Disk(amountDisks - i,this,i, parent);
        stack[i] = disk;
    }

    setEnabled(true);
    show();
    raise();
}

void Tower::paintEvent(QPaintEvent *event){

    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);

    QColor poleColor(91, 106, 174);
    QColor edgePoleColor(0, 0, 0);
    p.setPen(edgePoleColor);
    p.setBrush(poleColor);
    p.drawRoundedRect(120,90,20,260-(amountDisks*DISK_HEIGHT),10,8);
    raise();

}

// метод, який повертає вказівник на верхній диск на вежі, інакше NULL
Disk* Tower::topDisk(){
    Disk *d = NULL;
    if(amountDisks > 0){
        d = stack[--amountDisks];
        stack[amountDisks]=NULL;
        if(!autoplay) {
            d->Lift();
        }
    }
    return d;
}

// метод, який розміщує диск на вежі. Повертає true, якщо є місце і диск правильного розміру, інакше false
bool Tower::putDisk(Disk* disk){
    if(amountDisks == 0){
        stack[0] = disk;
        amountDisks++;
        disk->setTowerPos(this,0);
        raise();
        return true;
    }else{
        if(stack[amountDisks-1]->Size() > disk->Size()){
            stack[amountDisks] = disk;
            amountDisks++;
            disk->setTowerPos(this,amountDisks-1);
            raise();
            return true;
        }else{
            return false;
        }
    }

}

// метод, який повертає кількість дисків, розташованих на вежі
int Tower::getAmountDisks(){
    return amountDisks;
}

Tower::~Tower(){
    setParent(NULL);
    for (int i=0;i<amountDisks;i++){
        delete stack[i];
    }
}
