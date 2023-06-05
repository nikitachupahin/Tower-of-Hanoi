#include "towerofhanoi.h"
#include "ui_towerofhanoi.h"
#include "stylehelper.h"
#include <QPainter>

Disk* moving = NULL; // вказівник на поточний пересуваний диск

TowerOfHanoi::TowerOfHanoi(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::TowerOfHanoi)
{
    ui->setupUi(this);
    setInterfaceStyle();
    amountDiscs = 3;

    towers[0] = new Tower(0, amountDiscs, ui->pushButtonTower1, autoplay);
    towers[1] = new Tower(1, 0, ui->pushButtonTower2, autoplay);
    towers[2] = new Tower(2, 0, ui->pushButtonTower3, autoplay);
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(delayedAction()));
    moveCount = 0;
    updateMoveCount();
}

// слот, який викликається затримкою для виконання наступного ходу в грі
void TowerOfHanoi::delayedAction(){
    if(autoplay){
        if(!schedule.empty()){
            Move autom = schedule.dequeue();
            moving = towers[autom.getFrom()]->topDisk();
            towers[autom.getTo()]->putDisk(moving);
            moving = NULL;
            moveCount++;
            updateMoveCount();
            checkWinCondition();
        }else{
            autoplay = false;
            ui->pushButtonTower1->setEnabled(true);
            ui->pushButtonTower2->setEnabled(true);
            ui->pushButtonTower3->setEnabled(true);
            timer->stop();
        }

    }else{
        ui->pushButtonTower1->setEnabled(true);
        ui->pushButtonTower2->setEnabled(true);
        ui->pushButtonTower3->setEnabled(true);
        timer->stop();
    }
}

void TowerOfHanoi::paintEvent(QPaintEvent *){
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);
    QColor baseColor(129, 68, 72);
    QColor borderColor(76, 41, 43);
    p.setPen(borderColor);
    p.setBrush(baseColor);
    p.drawRect(0,355,width(),80);
    p.drawRect(0,345,width(),70);
}

void TowerOfHanoi::checkWinCondition()
{
    if (towers[0]->getAmountDisks() == 0 && towers[1]->getAmountDisks() == 0) {
        QMessageBox::about(this, "Перемога!!!", "Усі диски переміщені на третю вежу!");
    }
}

void TowerOfHanoi::updateMoveCount()
{
    ui->moveCountLabel->setText(QString("<span style=\"font-size:20px;\">Moves : %1</span>").arg(moveCount));
}

void TowerOfHanoi::setInterfaceStyle()
{
    this->setStyleSheet(StyleHelper::getGameWindowStyle());
}

TowerOfHanoi::~TowerOfHanoi()
{
    delete ui;
    for (int i=0;i<3;i++){

        delete towers[i];
    }
    moving = NULL;
    schedule.clear();
}

void TowerOfHanoi::on_pushButton_clicked(Tower* p){
    if(!moving){
        moving = p->topDisk();
    }else{
        if(p->putDisk(moving)){
            moving = NULL;
            moveCount++;
            updateMoveCount();
            checkWinCondition();
        }else{
            moving->On()->putDisk(moving);
            moving = NULL;
        }
    }
}

void TowerOfHanoi::CalculateAutoplay(int count, int from,  int dest, int aux){
    if(count < 1){
        return;
    }else{
        CalculateAutoplay(count-1,from,aux,dest);
        schedule.enqueue(Move(from,dest));
        CalculateAutoplay(count-1,aux,dest,from);
    }
}

void TowerOfHanoi::on_pushButtonTower1_clicked()
{
    on_pushButton_clicked(towers[0]);
}

void TowerOfHanoi::on_pushButtonTower2_clicked()
{
    on_pushButton_clicked(towers[1]);
}

void TowerOfHanoi::on_pushButtonTower3_clicked()
{
    on_pushButton_clicked(towers[2]);
}

void TowerOfHanoi::on_buttonSolve_clicked()
{
    ui->pushButtonTower1->setEnabled(false);
    ui->pushButtonTower2->setEnabled(false);
    ui->pushButtonTower3->setEnabled(false);
    autoplay = true;
    on_buttonRestart_clicked();
    CalculateAutoplay(towers[0]->getAmountDisks(), 0,2,1);
    timer->start(1000);
}


void TowerOfHanoi::on_buttonRestart_clicked()
{
    for (int i=0;i<3;i++){

        delete towers[i];
    }
    if(moving){
        delete moving;
    }
    moving = NULL;
    schedule.clear();

    towers[0] = new Tower(0, amountDiscs, ui->pushButtonTower1, autoplay);
    towers[1] = new Tower(1, 0, ui->pushButtonTower2, autoplay);
    towers[2] = new Tower(2, 0, ui->pushButtonTower3, autoplay);

    moveCount = 0;
    updateMoveCount();
}


void TowerOfHanoi::on_decreaseButton_clicked()
{
    if (amountDiscs > MIN_DISKS) {
        amountDiscs--;
        on_buttonRestart_clicked();
    } else {
        QMessageBox::warning(this, "Помилка", "Досягнуто мінімальної кількості дисків (1).");
    }
}


void TowerOfHanoi::on_increaseButton_clicked()
{
    if (amountDiscs < MAX_DISKS) {
        amountDiscs++;
        on_buttonRestart_clicked();
    } else {
        QMessageBox::warning(this, "Помилка", "Досягнуто максимальної кількості дисків (8).");
    }
}


void TowerOfHanoi::on_homeButton_clicked()
{
    amountDiscs = 3;
    on_buttonRestart_clicked();
    emit toMainPageClicked();
}

void TowerOfHanoi::on_HelpButton_clicked()
{
    on_buttonRestart_clicked();
    CalculateAutoplay(towers[0]->getAmountDisks(), 0,2,1);

    QString solutionSteps;
    int stepNumber = 1;
    while (!schedule.empty()) {
        Move step = schedule.dequeue();
        QString stepText = QString("<span style=\"font-size:15px;\">Крок %1: Перемістити диск із вежі %2 на вежу %3</span><br>").arg(stepNumber).arg(step.getFrom() + 1).arg(step.getTo() + 1);
        solutionSteps += stepText;
        stepNumber++;
    }

    SolutionDialog *dialog = new SolutionDialog(this);
    dialog->setSolutionSteps(solutionSteps);
    dialog->show();
}

SolutionDialog::SolutionDialog(QWidget *parent) : QDialog(parent) {
    setWindowTitle("Ханойская вежа - Рішення");
    setModal(false);

    QVBoxLayout *layout = new QVBoxLayout(this);

    // Створення QScrollArea
    QScrollArea *scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);
    scrollArea->setStyleSheet("background-color: rgb(2, 28, 62);");

    // Створення QLabel для відображення кроків вирішення
    labelSteps = new QLabel(this);
    labelSteps->setAlignment(Qt::AlignTop | Qt::AlignLeft);

    // Встановлення QLabel в QScrollArea
    scrollArea->setWidget(labelSteps);

    // Додавання QScrollArea в макет
    layout->addWidget(scrollArea);
}

void SolutionDialog::setSolutionSteps(const QString &steps) {
    labelSteps->setText(steps);
}
