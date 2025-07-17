// ./include/gameWidget.hpp
#pragma once

#include <QPoint>
#include <QTimer>
#include <QVector>
#include <QWidget>

class GameWidget : public QWidget {
    Q_OBJECT
   public:
    explicit GameWidget(QWidget *parent = nullptr);
    void setSpeed(int ms);
    void setWallCrossing(bool enabled);
    void startGame();

   protected:
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;

   private slots:
    void updateGame();

   private:
    QTimer *timer;
    QVector<QPoint> snake;
    QPoint direction;
    int gridSize;
    bool allowWallCrossing = false;
};