#ifndef SHAKE_H
#define SHAKE_H
#include <QWidget>
#include <QKeyEvent>

#include <QWidget>
#include <QKeyEvent>

class Snake : public QWidget {

  public:
      Snake(QWidget *parent = 0);

  protected:
      void paintEvent(QPaintEvent *);
      void timerEvent(QTimerEvent *);
      void keyPressEvent(QKeyEvent *);

  private:
      QImage blok;
      QImage head;
      QImage apple;
      QImage blokf;
      QImage blokz;

      static const int B_WIDTH = 800;
      static const int B_HEIGHT = 800;
      static const int BLOCK_SIZE = 30;
      static const int TIME_OUT = 200;
      static const int RAND_POS = (B_WIDTH/BLOCK_SIZE)-1;
      static const int ALL_BLOCKS = 711;


      int timerId;
      int blocks;
      int x[ALL_BLOCKS];
      int y[ALL_BLOCKS];

      int AppleX;
      int AppleY;

      bool LeftDir;
      bool RightDir;
      bool UpDir;
      bool DownDir;
      bool NowPlaying;

      void GetImages();
      void StartGame();
      void SetPosApple();
      void CheckApple();
      void CheckPlaying();
      void MoveSnake();
      void ToDraw();
      void GameOver(QPainter &qp);

};

#endif // SHAKE_H
