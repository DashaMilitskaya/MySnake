#include <QPainter>
#include <QTime>
#include <QtMath>
#include <QThread>
#include "snake.h"
#include "mainwindow.h"



Snake::Snake(QWidget *parent) : QWidget(parent) {

    setStyleSheet("background-color: black");

    LeftDir = false;
    RightDir = true;
    UpDir = false;
    DownDir = false;
    NowPlaying = true;
    setFixedSize(B_WIDTH, B_HEIGHT);
    //resize();
    GetImages();
    StartGame();
}

void Snake::GetImages() {

    blok.load(":/resource/images/dot.png");
    blokz.load(":/resource/images/dotz.png");
    blokf.load(":/resource/images/dotf.png");
    head.load(":/resource/images/head.png");
    apple.load(":/resource/images/apple.png");
}

void Snake::StartGame() {

    blocks = 3;

    for (int z = 0; z < blocks; z++) {
        x[z] = 50 - z * 10;
        y[z] = 50;
    }

    SetPosApple();

    timerId = startTimer(TIME_OUT);
}

void Snake::paintEvent(QPaintEvent *e) {

    Q_UNUSED(e);

    ToDraw();
}

void Snake::ToDraw() {

    QPainter qp(this);
int myrand;

    if (NowPlaying) {

        qp.drawImage(AppleX, AppleY, apple);

        for (int z = 0; z < blocks; z++) {
            if (z == 0) {
                qp.drawImage(x[z], y[z], head); 
            }
            else {
                           myrand = qrand();
                            if(((myrand)%3)==1){
                           qp.drawImage(x[z], y[z], blokf);
                            }else{
                                if(((myrand)%3)==2){
                               qp.drawImage(x[z], y[z], blokz);
                                }
                                else
                                {
                                qp.drawImage(x[z], y[z], blok);
                                }
                            }

            }
         }
    }
        else {
       // this->close();
        GameOver(qp);
    }  
}



void Snake::GameOver(QPainter &qp) {

    QString message = "Game over";
    QFont font("Courier", 20, QFont::DemiBold);
    QFontMetrics fm(font);
    int textWidth = fm.width(message);

    qp.setPen(QColor(Qt::white));
    qp.setFont(font);
    int h = height();
    int w = width();

    qp.translate(QPoint(w/2, h/2));
    qp.drawText(-textWidth/2, 0, message);
}


void Snake::CheckApple() {

    if ((qFabs(x[0] - AppleX) < 30) && (qFabs(y[0] - AppleY)< 30)) {

        blocks++;
        SetPosApple();
    }
}

void Snake::MoveSnake() {

    for (int z = blocks; z > 0; z--) {
        x[z] = x[(z - 1)];
        y[z] = y[(z - 1)];
    }

    if (LeftDir) {
        x[0] -= BLOCK_SIZE;
    }

    if (RightDir) {
        x[0] += BLOCK_SIZE;
    }

    if (UpDir) {
        y[0] -= BLOCK_SIZE;
    }

    if (DownDir) {
        y[0] += BLOCK_SIZE;
    }
}

void Snake::CheckPlaying() {

    for (int z = blocks; z > 0; z--) {

        if ((z > 4) && (x[0] == x[z]) && (y[0] == y[z])) {
            NowPlaying = false;
        }
    }

    if (y[0] >= B_HEIGHT) {
        NowPlaying = false;
    }

    if (y[0] < 0) {
        NowPlaying = false;
    }

    if (x[0] >= B_WIDTH) {
        NowPlaying = false;
    }

    if (x[0] < 0) {
        NowPlaying = false;
    }

    if(!NowPlaying) {
        killTimer(timerId);
        //this->deleteLater();
    }
}

void Snake::SetPosApple() {

    QTime time = QTime::currentTime();
    qsrand((uint) time.msec());

    int r = qrand() % RAND_POS;
    AppleX = (r * BLOCK_SIZE);

    r = qrand() % RAND_POS;
    AppleY = (r * BLOCK_SIZE);
}

void Snake::timerEvent(QTimerEvent *e) {

    Q_UNUSED(e);

    if (NowPlaying) {

        CheckApple();
        CheckPlaying();
        MoveSnake();
    }
    //this->doDrawing();
    repaint();
}

void Snake:: keyPressEvent(QKeyEvent *e) {

    int key = e->key();

    if ((key == Qt::Key_Left) && (!RightDir)) {
        LeftDir = true;
        UpDir = false;
        DownDir = false;
    }

    if ((key == Qt::Key_Right) && (!LeftDir)) {
        RightDir = true;
        UpDir = false;
        DownDir = false;
    }

    if ((key == Qt::Key_Up) && (!DownDir)) {
        UpDir = true;
        RightDir = false;
        LeftDir = false;
    }

    if ((key == Qt::Key_Down) && (!UpDir)) {
        DownDir = true;
        RightDir = false;
        LeftDir = false;
    }

    QWidget::keyPressEvent(e);
}
