#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "snake.h"
#include <QPainter>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->pushButton, SIGNAL (clicked()), this, SLOT (StartGame()));

    QPixmap bkgnd(":/resource/images/back.bmp");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow :: StartGame(){
    Snake* window = new Snake(this);

    window->setWindowTitle("Snake");

    window->raise();
    window->show();
    window->setFocus();
}

void MainWindow::DrawFail(){
    QPainter qpaint(this);
    QString message = "Game over";
    QFont font("TimesNewRoman", 20, QFont::DemiBold);
    QFontMetrics mes(font);
    int textWidth = mes.width(message);

    qpaint.setPen(QColor(Qt::black));
    qpaint.setFont(font);
    int h = height();
    int w = width();

    qpaint.translate(QPoint(900, 900));
    qpaint.drawText(-textWidth/2, 0, message);
}
